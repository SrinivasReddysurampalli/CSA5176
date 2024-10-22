#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

uint8_t key = 0xFD;  
uint8_t iv = 0xAA;

uint8_t S_BOX[4][4] = {
    {0x3, 0xF, 0xE, 0x0},
    {0x4, 0x1, 0xA, 0x2},
    {0xD, 0xC, 0x6, 0x5},
    {0x9, 0xB, 0x7, 0x8}
};

uint8_t xor(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key) {
    uint8_t substituted = S_BOX[(plaintext >> 4) & 0x3][plaintext & 0x3];
    return xor(substituted, key);
}

uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key) {
    uint8_t xor_result = xor(ciphertext, key);
    int i, j;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (S_BOX[i][j] == (xor_result & 0xF)) {
                return (i << 4) | j;
            }
        }
    }
    return 0;
}

void cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, int len) {
    uint8_t previous_block = iv;
    int i;
    for (i = 0; i < len; ++i) {
        uint8_t xor_result = xor(plaintext[i], previous_block);
        ciphertext[i] = sdes_encrypt(xor_result, key);
        previous_block = ciphertext[i];
    }
}

void cbc_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, int len) {
    uint8_t previous_block = iv;
    int i;
    for (i = 0; i < len; ++i) {
        uint8_t decrypted_block = sdes_decrypt(ciphertext[i], key);
        plaintext[i] = xor(decrypted_block, previous_block);
        previous_block = ciphertext[i];
    }
}

void print_binary(const char *label, const uint8_t *data, int len) {
    printf("%s: ", label);
    int i, j;
    for (i = 0; i < len; ++i) {
        for (j = 7; j >= 0; --j) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[2] = {0x01, 0x23};
    uint8_t ciphertext[2] = {0};
    uint8_t decrypted[2] = {0};

    cbc_encrypt(plaintext, ciphertext, 2);
    print_binary("Ciphertext", ciphertext, 2);

    cbc_decrypt(ciphertext, decrypted, 2);
    print_binary("Decrypted Plaintext", decrypted, 2);

    return 0;
}

