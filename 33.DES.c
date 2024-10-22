#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8

uint64_t initial_permutation(uint64_t input) {
    return input;
}

uint64_t inverse_initial_permutation(uint64_t input) {
    return input;
}

void generate_round_keys(uint8_t *key, uint64_t *round_keys) {
	int i;
    for ( i = 0; i < 16; i++) {
        round_keys[i] = 0;
    }
}

uint64_t feistel_function(uint64_t right, uint64_t round_key) {
    return right;
}

uint64_t des_encrypt(uint64_t plaintext, uint8_t *key) {
    uint64_t round_keys[16];
    generate_round_keys(key, round_keys);
    
    plaintext = initial_permutation(plaintext);
    
    uint64_t left = (plaintext >> 32) & 0xFFFFFFFF;
    uint64_t right = plaintext & 0xFFFFFFFF;
    int i;
    for ( i = 0; i < 16; i++) {
        uint64_t temp = right;
        right = left ^ feistel_function(right, round_keys[i]);
        left = temp;
    }

    uint64_t ciphertext = (right << 32) | left;
    ciphertext = inverse_initial_permutation(ciphertext);
    
    return ciphertext;
}

uint64_t des_decrypt(uint64_t ciphertext, uint8_t *key) {
    uint64_t round_keys[16];
    generate_round_keys(key, round_keys);
    
    ciphertext = initial_permutation(ciphertext);
    
    uint64_t left = (ciphertext >> 32) & 0xFFFFFFFF;
    uint64_t right = ciphertext & 0xFFFFFFFF;
    int i;
    for ( i = 15; i >= 0; i--) {
        uint64_t temp = right;
        right = left ^ feistel_function(right, round_keys[i]);
        left = temp;
    }

    uint64_t plaintext = (right << 32) | left;
    plaintext = inverse_initial_permutation(plaintext);
    
    return plaintext;
}

int main() {
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint64_t plaintext = 0x0123456789ABCDEF;

    printf("Plaintext: 0x%016llX\n", plaintext);
    
    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: 0x%016llX\n", ciphertext);
    
    uint64_t decrypted = des_decrypt(ciphertext, key);
    printf("Decrypted: 0x%016llX\n", decrypted);

    return 0;
}

