#ifndef REGISTER_H
#define REGISTER_H

#include "stdio.h"
#include "stdlib.h"
#include "complex.h"
#include "qudit.h"

typedef struct {
    Qudit **qudits;
    int n_qudits;
} QuantumRegister;

Complex *tensor_product(Complex *a0, int size0, Complex *a1, int size1, int *result_size);
Complex *qr_tensor_product(QuantumRegister *qr, int *result_size);
int *qr_measure(QuantumRegister *qr, double observation);

#endif REGISTER_H