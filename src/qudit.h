#ifndef QUDIT_H
#define QUDIT_H

#include "complex.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct {
    Complex* amplitudes;
    int n_states;
} Qudit;

void qudit_init(Qudit* qd, Complex* ampls, int n_ampls);
int qudit_measure(Qudit* qd, double obs);
void qudit_reset(Qudit* qd, Complex* ampls, int n_ampls);

#endif QUDIT_H