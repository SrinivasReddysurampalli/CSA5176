#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CONST_64  0x1B
#define CONST_128 0x87

void print_hex(const char *label, uint8_t *key, size_t size) {
    printf("%s: ", label);
    size_t i;  // Declare i here
    for (i = 0; i < size; i++) {  // Use i in the loop
        printf("%02X", key[i]);
    }
    printf("\n");
}

void left_shift(uint8_t *key, size_t size) {
    uint8_t overflow = 0;
    int i;  
    for (i = (int)size - 1; i >= 0; i--) {  
        uint8_t new_overflow = (key[i] & 0x80) ? 1 : 0;
        key[i] = (key[i] << 1) | overflow;
        overflow = new_overflow;
    }
}

void xor_with_constant(uint8_t *key, uint8_t constant) {
    key[0] ^= constant;
}

void generate_subkeys(uint8_t *k1, uint8_t *k2, size_t block_size) {
    uint8_t L[16] = {0};
    memcpy(k1, L, block_size);

    left_shift(k1, block_size);
    if (k1[0] & 0x80) {
        xor_with_constant(k1, (block_size == 8) ? CONST_64 : CONST_128);
    }

    memcpy(k2, k1, block_size);
    left_shift(k2, block_size);
    if (k1[0] & 0x80) {
        xor_with_constant(k2, (block_size == 8) ? CONST_64 : CONST_128);
    }
}

int main() {
    size_t block_size = 16;  
    uint8_t k1[16], k2[16];

    generate_subkeys(k1, k2, block_size);

    print_hex("K1", k1, block_size);
    print_hex("K2", k2, block_size);

    return 0;
}

