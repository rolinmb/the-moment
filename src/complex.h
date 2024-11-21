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

static inline double complex_magnitude(Complex c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

static inline Complex complex_conjugate(Complex c) {
    Complex result;
    result.real = c.real;
    result.imag = -c.imag;
    return result;
}

#endif COMPLEX_H