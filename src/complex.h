#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_init(double real, double imag);
Complex complex_add(Complex a, Complex b);
Complex complex_subtract(Complex a, Complex b);
Complex complex_multiply(Complex a, Complex b);
Complex complex_divide(Complex a, Complex b);
double complex_magnitude(Complex c);
Complex complex_conjugate(Complex c);

#endif COMPLEX_H