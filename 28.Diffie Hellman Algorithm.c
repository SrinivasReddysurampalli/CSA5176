#include <stdio.h>
long long mod_exp(long long base, long long exp, long long modValue) {
    long long result = 1;
    base = base % modValue;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modValue;
        }
        exp = exp >> 1; 
        base = (base * base) % modValue; 
    }
    return result;
}
int main() {
    long long q = 23; 
    long long a = 5;
    long long x_a = 6; 
    long long A = mod_exp(a, x_a, q);
    long long x_b = 15; 
    long long B = mod_exp(a, x_b, q); 

    long long K_a = mod_exp(B, x_a, q); 
    long long K_b = mod_exp(A, x_b, q); 

    printf("Alice's public value A: %lld\n", A);
    printf("Bob's public value B: %lld\n", B);
    printf("Shared secret key (Alice): %lld\n", K_a);
    printf("Shared secret key (Bob): %lld\n", K_b);

    return 0;
}

