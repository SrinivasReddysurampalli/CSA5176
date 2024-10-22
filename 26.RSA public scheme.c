#include <stdio.h>
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
    int p = 61, q = 53, n = p * q, phi = (p - 1) * (q - 1);
    int e2 = 7, d2 = mod_inverse(e2, phi); 

    int message = 42;
    int encrypted = mod_exp(message, e2, n);
    int decrypted = mod_exp(encrypted, d2, n);

    printf("Message: %d, Encrypted: %d, Decrypted: %d\n", message, encrypted, decrypted);
    if (gcd(e2, phi) == 1) 
        printf("Reusing modulus n makes the system vulnerable.\n");

    return 0;
}

