/*
@author: Samuel Chamalé
@description: Program that prints a message from each thread in the parallel region.
@date: 08-11-2024
@compilation: gcc -fopenmp -o hello_omp.exe hello_omp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int nthreads = 10; // Default number of threads

    // If the number of threads is provided from the command line, we use it
    if (argc > 1) {
        nthreads = atoi(argv[1]);
    }

    // Stablish the number of threads
    omp_set_num_threads(nthreads);

    // Parallelize the section where we print from each thread
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d!\n", thread_id, total_threads);
    }

    return 0;
}
