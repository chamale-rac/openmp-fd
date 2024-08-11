/*
@author: Samuel Chamalé
@description: Program that prints a message from each thread in the parallel region.
@date: 08-11-2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int nthreads;

    // Verify if the number of threads (age) has been provided from the command line
    if (argc > 1) {
        nthreads = atoi(argv[1]);
    } else {
        printf("Please provide your age as param.\n");
        return 1;
    }

    // Stablish the number of threads
    omp_set_num_threads(nthreads);

    // Parallelize the section where we print from each thread
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        if (thread_id % 2 == 0) {
            printf("Saludos del hilo %d\n", thread_id);
        } else {
            printf("Feliz cumpleaños número %d!\n", total_threads);
        }
    }

    return 0;
}
