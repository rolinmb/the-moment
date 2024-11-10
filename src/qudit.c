#include "qudit.h"

void qudit_init(Qudit* qd, double* ampls, int n_ampls) {
    qd->amplitudes = (double*)malloc(sizeof(double) * n_ampls);
    qd->n_states = n_ampls;
    for (int i = 0; i < n_ampls; i++) {
        qd->amplitudes[i] = ampls[i];
    }
    double total_prob = 0.0;
    for (int i = 0; i < qd->n_states; i++) {
        total_prob += pow(fabs(qd->amplitudes[i]), 2);
    }
    if ((fabs(total_prob) - 1.0) > 1e-6) {
        fprintf(stderr, "src/qudit.c : qudit_init() :: ERROR ::: Qudit outcome probabilities do not sum to 1: %f\n", total_prob);
	exit(EXIT_FAILURE);
    }
}

int qudit_measure(Qudit* qudit, double obs) {
    double cumulative_prob = 0.0;
    for (int i = 0; i < qudit->n_states; i++) {
        double prob = pow(fabs(qudit->amplitudes[i]), 2);
        cumulative_prob += prob;
        if (obs < cumulative_prob) {
            return i;
        }
    }
    return -1; // Should not reach here if obs is in range [0, 1)
}

void qudit_reset(Qudit* qudit, double* amplitudes, int num_amplitudes) {
    qudit->amplitudes = (double*)realloc(qudit->amplitudes, sizeof(double) * num_amplitudes);
    qudit->n_states = num_amplitudes;
    for (int i = 0; i < num_amplitudes; i++) {
        qudit->amplitudes[i] = amplitudes[i];
    }
    double total_prob = 0.0;
    for (int i = 0; i < qudit->n_states; i++) {
        total_prob += pow(fabs(qudit->amplitudes[i]), 2);
    }
    if (fabs(total_prob - 1.0) > 1e-10) {
        fprintf(stderr, "src/qudit.c : qudit_reset() :: ERROR ::: Qudit outcome probabilities do not sum to 1: %f\n", total_prob);
        exit(EXIT_FAILURE);
    }
}