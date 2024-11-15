#include "true_rand.h"
#include "stdio.h"

double true_rand() {
    unsigned char random_bytes[8];
    // Use CryptGenRandom to fill the buffer with random bytes
    HCRYPTPROV hCryptProv;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        fprintf(stderr, "src/true_rand.c : true_rand() :: ERROR ::: Windows.h CryptAcquireContext failed\n");
        return -1.0; // Return an error value
    }
    if (!CryptGenRandom(hCryptProv, sizeof(random_bytes), random_bytes)) {
        fprintf(stderr, "src/true_rand.c : true_rand() :: ERROR ::: Windows.h CryptGenRandom failed\n");
        CryptReleaseContext(hCryptProv, 0);
        return -1.0; // Return an error value
    }
    // Convert the 8 random bytes to a 64-bit integer
    unsigned long long rand_int = 0;
    for (int i = 0; i < 8; i++) {
        rand_int = (rand_int << 8) | random_bytes[i];
    }
    // Normalize to a floating-point number in the range [0, 1)
    double result = (double)rand_int / ((1ULL << 64) - 1);
    // Clean up the context
    CryptReleaseContext(hCryptProv, 0);
    return result;
}
