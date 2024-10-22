#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}
int modular_inverse(int e, int phi_n) {
    int x, y;
    int gcd = extended_gcd(e, phi_n, &x, &y);
    if (gcd != 1) {
        printf("No modular inverse exists.\n");
        return -1;
    }
    return (x % phi_n + phi_n) % phi_n;
}

int main() {
    int n = 3599;
    int e = 31;    

    int M = 59;    
    int p = gcd(M, n);
    if (p == 1 || p == n) {
        printf("No useful common factor found.\n");
        return 1;
    }
    int q = n / p;
    printf("Found prime factors: p = %d, q = %d\n", p, q);

    int phi_n = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi_n);
    int d = modular_inverse(e, phi_n);
    if (d != -1) {
        printf("The private key (d) is: %d\n", d);
    }

    return 0;
}

