#include "register.h"

Complex *tensor_product(Complex *a0, int size0, Complex *a1, int size1, int *result_size) {
    *result_size = size0 * size1;
    Complex *result = (Complex *)malloc((*result_size) * sizeof(Complex));
    if (!result) {
        fprintf(stderr, "ERROR: Memory allocation failed in src/register.c tensor_product()\n");
        exit(1);
    }
    for (int i = 0; i < size0; i++) {
        for (int j = 0; j < size1; j++) {
            result[i * size1 + j] = complex_mul(a0[i], a1[j]);
        }
    }
    return result;
}

Complex *qr_tensor_product(QuantumRegister *qr, int *result_size) {
    if (qr->n_qudits == 0) {
        fprintf(stderr, "ERROR: No Qudits in Quantum Register used in src/regiser.c qr_tensor_product()\n");
        return NULL;
    }
    Complex *joint_amplitudes = qr->qudits[0]->amplitudes;
    int joint_size = qr->qudits[0]->n_states;
    for (int i = 1; i < qr->n_qudits; i++) {
        joint_amplitudes = tensor_product(
            joint_amplitudes, joint_size,
            qr->qudits[i]->amplitudes, qr->qudits[i]->n_states,
            &joint_size
        );
    }
    result_size = joint_size;
    return joint_amplitudes;
}

int *qr_measure(QuantumRegister *qr, double observation) {
    int result_size;
    Complex *joint_amplitudes = qr_tensor_product(qr, &result_size);
    if (!joint_amplitudes) {
        fprintf(stderr, "ERROR : Failed to compute joint state in src/register.c qr_measre()\n");
        return NULL;
    }
    Qudit joint_qudit;
    qudit_init(&joint_qudit, joint_amplitudes, result_size);
    int joint_measurement = qudit_measure(&joint_qudit, observation);
    int num_qudits = qr->n_qudits;
    int *results = (int *)malloc(num_qudits * sizeof(int));
    if (!results) {
        fprintf(stderr, "ERROR: Memory allocation failed in src/register.c qr_measure()\n");
        free(joint_amplitudes);
        return NULL;
    }
    int base = qr->qudits[0]->n_states;
    for (int i = num_qudits - 1; i >= 0; i--) {
        results[i] = joint_measurement % base;
        joint_measurement /= base;
    }
    free(joint_amplitudes);
    return results;
}