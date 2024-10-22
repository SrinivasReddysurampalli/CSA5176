#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct {
    long p;
    long q;
    long g;
    long x;
    long y;
} DSA;

typedef struct {
    long n;
    long e;
    long d;
} RSA;

long generate_random_k(long q) {
    return rand() % (q - 1) + 1;
}

void dsa_sign(DSA *dsa, const char *message, long *r, long *s) {
    long k = generate_random_k(dsa->q);
    *r = (long)(pow(dsa->g, k)) % dsa->p % dsa->q;
    long k_inv = 1;  // In a complete implementation, calculate the modular inverse of k
    *s = (k_inv * (strlen(message) + dsa->x * (*r))) % dsa->q;
}

void rsa_sign(RSA *rsa, const char *message, long *signature) {
    *signature = (strlen(message) * rsa->d) % rsa->n;
}

int main() {
    srand(time(NULL));

    DSA dsa = {23, 11, 5, 6, 18};
    long r1, s1, r2, s2;

    const char *message = "Hello, World!";
    dsa_sign(&dsa, message, &r1, &s1);
    dsa_sign(&dsa, message, &r2, &s2);

    printf("DSA Signatures:\n");
    printf("Signature 1: (r: %ld, s: %ld)\n", r1, s1);
    printf("Signature 2: (r: %ld, s: %ld)\n", r2, s2);

    RSA rsa = {3233, 17, 2753};
    long rsa_signature;

    rsa_sign(&rsa, message, &rsa_signature);

    printf("RSA Signature:\n");
    printf("Signature: %ld\n", rsa_signature);

    return 0;
}

