#include "stdio.h"
#include "stdlib.h"
#include "true_rand.h"
#include "complex.h"
#include "qudit.h"

int main() {
    Complex amplitudes[] = {
        {0.577350269, 0.0}, // Real part: 0.577350269, Imaginary part: 0.0
        {0.0, 0.577350269}, // Real part: 0.0, Imaginary part: 0.577350269
        {-0.577350269, 0.0} // Real part: -0.577350269, Imaginary part: 0.0
    };
    int n_amplitudes = sizeof(amplitudes) / sizeof(amplitudes[0]);
    Qudit qd;
    qudit_init(&qd, amplitudes, n_amplitudes);
    double obs = true_rand();
    if (obs == -1.0) {
        fprintf(stderr, "src/main.c : main() :: ERROR ::: true_rand failed\n");
        return 1;
    }
    printf("src/main.c : main() :: Random observation: %f\n", obs);
    int result = qudit_measure(&qd, obs);
    if (result != -1) {
        printf("src/main.c : main() :: Measurement result: Qudit state %d\n", result);
    } else {
        fprintf(stderr, "src/main.c : main() :: ERROR ::: Invalid result\n");
    }
    return 0;
}