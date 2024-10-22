#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 1

uint8_t key = 0xFD;
uint8_t counter = 0x00;

uint8_t S_BOX[4][4] = {
    {0x3, 0xF, 0xE, 0x0},
    {0x4, 0x1, 0xA, 0x2},
    {0xD, 0xC, 0x6, 0x5},
    {0x9, 0xB, 0x7, 0x8}
};

uint8_t xor(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t sdes_encrypt(uint8_t input, uint8_t key) {
    uint8_t substituted = S_BOX[(input >> 4) & 0x3][input & 0x3];
    return xor(substituted, key);
}

void ctr_encrypt_decrypt(const uint8_t *input, uint8_t *output, int len, uint8_t key) {
    uint8_t ctr_value = counter;
    int i;
    for (i = 0; i < len; ++i) {
        uint8_t encrypted_counter = sdes_encrypt(ctr_value, key);
        output[i] = xor(input[i], encrypted_counter);
        ctr_value++;
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
    uint8_t plaintext[3] = {0x01, 0x02, 0x04};
    uint8_t ciphertext[3] = {0};
    uint8_t decrypted[3] = {0};

    ctr_encrypt_decrypt(plaintext, ciphertext, 3, key);
    print_binary("Ciphertext", ciphertext, 3);

    ctr_encrypt_decrypt(ciphertext, decrypted, 3, key);
    print_binary("Decrypted Plaintext", decrypted, 3);

    return 0;
}

