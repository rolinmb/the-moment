#include "stdio.h"
#include "stdlib.h"
#include "true_rand.h"
#include "complex.h"
#include "qudit.h"

#define N_ITERS 100000

int main() {
    Complex amplitudes[] = { // Qudit with 4 possible states of equal (25%) probability
        {0.5, 0.0}, // Real: 0.5,   Imag: 0.0  for state 0
        {0.0, 0.5}, // Real: 0.0,   Imag: 0.5  for state 1
        {-0.5, 0.0},// Real: -0.5,  Imag: 0.0  for state 2
        {0.0, -0.5} // Real: 0.0,   Imag: -0.5 for state 3
    };
    int n_amplitudes = sizeof(amplitudes) / sizeof(amplitudes[0]);
    int *counts = (int *)malloc(n_amplitudes * sizeof(int));
    Qudit qd;
    qudit_init(&qd, amplitudes, n_amplitudes);
    for (int i = 0; i < n_amplitudes; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < N_ITERS; i++) {
        double obs = true_rand();
        if (obs == -1.0) {
            fprintf(stderr, "src/main.c : main() :: ERROR ::: true_rand failed\n");
            free(counts);
            return 1;
        }
        int result = qudit_measure(&qd, obs);
        if (result != -1) {
            counts[result]++;
        } else {
            fprintf(stderr, "src/main.c : main() :: ERROR ::: Invalid result\n");
        }
    }
    printf("src/main.c : main() :: Measurement Results After %d Iterations:\n", N_ITERS);
    for (int i = 0; i < n_amplitudes; i++) {
        printf("\t-> State %d observed %d times (%.2f%%)\n", i, counts[i], (counts[i] * 100.0) / N_ITERS);
    }
    free(counts);
    return 0;
}