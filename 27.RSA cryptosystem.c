#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int mod_inverse(int a, int m) {
    int m0 = m, x0 = 0, x1 = 1, q, t;
    while (a > 1) {
        q = a / m;
        t = m; m = a % m; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    return (x1 < 0) ? x1 + m0 : x1;
}
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p = 61, q = 53; 
    int n = p * q; 
    int phi = (p - 1) * (q - 1); 
    int e = 17; 
    int d = mod_inverse(e, phi); 

    char plaintext[] = "HELLO";
    int len = sizeof(plaintext) - 1; 
    int ciphertext[len],i;

    for ( i = 0; i < len; i++) {
        int m = plaintext[i] - 'A'; 
        ciphertext[i] = mod_exp(m, e, n); 
        printf("Plaintext: %c, Ciphertext: %d\n", plaintext[i], ciphertext[i]);
    }
    printf("\nDecrypted message:\n");
    for (i = 0; i < len; i++) {
        int decrypted = mod_exp(ciphertext[i], d, n); 
        printf("Ciphertext: %d, Decrypted: %c\n", ciphertext[i], decrypted + 'A');
    }

    return 0;
}

