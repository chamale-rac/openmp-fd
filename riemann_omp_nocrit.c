/*
@author: Samuel Chamalé
@description: Program that calculates the integral of a function using the trapezoidal rule (parallel noncritic version).
@date: 08-11-2024
@compilation: gcc -fopenmp -o riemann_omp_nocrit.exe riemann_omp_nocrit.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Definition of the functions to integrate
double f1(double x) {
    return x * x;
}

double f2(double x) {
    return 2 * x * x * x;
}

double f3(double x) {
    return sin(x);
}

// Global array to store the partial results
double *results;

// Function that implements the trapzoidal rule (parallel version) noncritical
double trapezoides(double (*f)(double), double a, double b, int n, int threads) {
    double h = (b - a) / n;

    // Initialize the array to store the partial results
    results = (double*) malloc(threads * sizeof(double));

    // Parallelize this section
    #pragma omp parallel num_threads(threads)
    {
        int id = omp_get_thread_num();
        int n_local = n / threads;
        double a_local = a + id * n_local * h;
        double b_local = a_local + n_local * h;
        double local_result = (f(a_local) + f(b_local)) / 2.0;

        for (int i = 1; i < n_local; i++) {
            double xi = a_local + i * h;
            local_result += f(xi);
        }

        local_result *= h;
        results[id] = local_result; // Save the local result in the array
    }

    // Sum the partial results
    double global_result = 0.0;
    for (int i = 0; i < threads; i++) {
        global_result += results[i];
    }

    // Free the memory
    free(results);

    return global_result;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <a> <b> <threads>\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int threads = atoi(argv[3]);
    int n = 1000000;

    double result1 = trapezoides(f1, a, b, n, threads);
    double result2 = trapezoides(f2, a, b, n, threads);
    double result3 = trapezoides(f3, a, b, n, threads);

    printf("Con n = %d trapezoides y %d threads, la aproximación de la integral de %f a %f es:\n", n, threads, a, b);
    printf("Integral de x^2: %f\n", result1);
    printf("Integral de 2x^3: %f\n", result2);
    printf("Integral de sin(x): %f\n", result3);

    return 0;
}
