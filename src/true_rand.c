#include "true_rand.h"
#include "stdio.h"
#include "limits.h"

double true_rand() {
    unsigned char random_bytes[8];
    HCRYPTPROV hCryptProv; // Use CryptGenRandom to fill the buffer with random bytes
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        fprintf(stderr, "src/true_rand.c : true_rand() :: ERROR ::: Windows.h CryptAcquireContext failed\n");
        return -1.0;
    }
    if (!CryptGenRandom(hCryptProv, sizeof(random_bytes), random_bytes)) {
        fprintf(stderr, "src/true_rand.c : true_rand() :: ERROR ::: Windows.h CryptGenRandom failed\n");
        CryptReleaseContext(hCryptProv, 0);
        return -1.0;
    }
    // Convert the 8 random bytes to a 64-bit integer
    unsigned long long rand_int = 0;
    for (int i = 0; i < 8; i++) {
        rand_int = (rand_int << 8) | random_bytes[i];
    }
    // Normalize to a floating-point number in the range [0, 1]
    double result = (double)rand_int / (double)ULLONG_MAX;
    CryptReleaseContext(hCryptProv, 0); // Cleanup Windows.h crypto context
    return result;
}

/*

// optimization suggestion from ChatGPT (uses caching of random numbers)
static double random_cache[64];
static int cache_index = 64;

double true_rand() {
    if (cache_index >= 64) {
        HCRYPTPROV hCryptProv;
        if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
            fprintf(stderr, "ERROR: CryptAcquireContext failed\n");
            return -1.0;
        }
        if (!CryptGenRandom(hCryptProv, sizeof(random_cache), (BYTE*)random_cache)) {
            fprintf(stderr, "ERROR: CryptGenRandom failed\n");
            CryptReleaseContext(hCryptProv, 0);
            return -1.0;
        }
        CryptReleaseContext(hCryptProv, 0);
        cache_index = 0;
    }
    return random_cache[cache_index++] / (double)ULLONG_MAX;
}

*/