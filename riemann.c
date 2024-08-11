/*
@author: Samuel Chamalé
@description: Program that calculates the integral of a function using the trapezoidal rule.
@date: 08-11-2024
@compilation: gcc -o riemann.exe riemann.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// Function that implements the trapzoidal rule
double trapezoides(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double integral = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        integral += f(xi);
    }
    integral *= h;
    return integral;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <a> <b>\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 1000000;

    double result1 = trapezoides(f1, a, b, n);
    double result2 = trapezoides(f2, a, b, n);
    double result3 = trapezoides(f3, a, b, n);

    printf("Con n = %d trapezoides, nuestra aproximación de la integral de %f a %f es:\n", n, a, b);
    printf("Integral de x^2: %f\n", result1);
    printf("Integral de 2x^3: %f\n", result2);
    printf("Integral de sin(x): %f\n", result3);

    return 0;
}
