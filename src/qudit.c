#include "qudit.h"

void qudit_init(Qudit* qd, Complex* ampls, int n_ampls) {
    qd->amplitudes = (Complex*)malloc(sizeof(Complex) * n_ampls);
    qd->n_states = n_ampls;
    for (int i = 0; i < n_ampls; i++) {
        qd->amplitudes[i] = ampls[i];
    }

    double total_prob = 0.0;
    for (int i = 0; i < qd->n_states; i++) {
        total_prob += complex_magnitude(qd->amplitudes[i]) * complex_magnitude(qd->amplitudes[i]);
    }

    if ((fabs(total_prob) - 1.0) > 1e-6) {
        fprintf(stderr, "ERROR: Qudit outcome probabilities do not sum to 1: %f\n", total_prob);
        exit(EXIT_FAILURE);
    }
}


int qudit_measure(Qudit* qudit, double obs) {
    double cumulative_prob = 0.0;
    for (int i = 0; i < qudit->n_states; i++) {
        double prob = complex_magnitude(qudit->amplitudes[i]) * complex_magnitude(qudit->amplitudes[i]);
        cumulative_prob += prob;
        if (obs < cumulative_prob) {
            return i;
        }
    }
    return -1; // Should not reach here if obs is in range [0, 1]
}

void qudit_reset(Qudit* qudit, Complex* amplitudes, int num_amplitudes) {
    qudit->amplitudes = (Complex*)realloc(qudit->amplitudes, sizeof(Complex) * num_amplitudes);
    qudit->n_states = num_amplitudes;
    for (int i = 0; i < num_amplitudes; i++) {
        qudit->amplitudes[i] = amplitudes[i];
    }

    double total_prob = 0.0;
    for (int i = 0; i < qudit->n_states; i++) {
        total_prob += complex_magnitude(qudit->amplitudes[i]) * complex_magnitude(qudit->amplitudes[i]);
    }

    if (fabs(total_prob - 1.0) > 1e-10) {
        fprintf(stderr, "ERROR: Qudit outcome probabilities do not sum to 1: %f\n", total_prob);
        exit(EXIT_FAILURE);
    }
}
