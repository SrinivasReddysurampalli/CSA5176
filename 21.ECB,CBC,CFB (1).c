#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8
#define PADDING_BYTE 0x80

int pad_data(unsigned char *data, int data_len) {
    int padding_len = BLOCK_SIZE - (data_len % BLOCK_SIZE),i;
    data[data_len] = PADDING_BYTE;
    for ( i = 1; i < padding_len; ++i) {
        data[data_len + i] = 0x00;
    }
    return data_len + padding_len;
}

void xor_blocks(unsigned char *block1, const unsigned char *block2, int size) {
    int i;
	for ( i = 0; i < size; ++i) {
        block1[i] ^= block2[i];
    }
}

void ecb_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int len, const unsigned char *key) {
    int i;
	for ( i = 0; i < len; i += BLOCK_SIZE) {
        xor_blocks(ciphertext + i, plaintext + i, BLOCK_SIZE);
        xor_blocks(ciphertext + i, key, BLOCK_SIZE);
    }
}

void cbc_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int len, const unsigned char *key, unsigned char *iv) {
    unsigned char block[BLOCK_SIZE];
    int i;
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xor_blocks(block, iv, BLOCK_SIZE);
        xor_blocks(block, key, BLOCK_SIZE);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(iv, block, BLOCK_SIZE);
    }
}

void cfb_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int len, const unsigned char *key, unsigned char *iv) {
    unsigned char temp[BLOCK_SIZE];
    int i;
    for ( i = 0; i < len; i += BLOCK_SIZE) {
        memcpy(temp, iv, BLOCK_SIZE);
        xor_blocks(temp, key, BLOCK_SIZE);
        xor_blocks(ciphertext + i, temp, BLOCK_SIZE);
        memcpy(iv, ciphertext + i, BLOCK_SIZE);
    }
}

void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    int i;
    for ( i = 0; i < len; ++i) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[BLOCK_SIZE] = "abcdefgh";
    unsigned char iv[BLOCK_SIZE] = "12345678";
    unsigned char plaintext[32] = "Hello, this is a test message!";
    unsigned char ciphertext[32] = {0};
    int padded_len = pad_data(plaintext, strlen((char *)plaintext));

    print_hex("Original Plaintext", plaintext, padded_len);

    ecb_encrypt(plaintext, ciphertext, padded_len, key);
    print_hex("ECB Ciphertext", ciphertext, padded_len);

    memcpy(iv, "12345678", BLOCK_SIZE);
    cbc_encrypt(plaintext, ciphertext, padded_len, key, iv);
    print_hex("CBC Ciphertext", ciphertext, padded_len);

    memcpy(iv, "12345678", BLOCK_SIZE);
    cfb_encrypt(plaintext, ciphertext, padded_len, key, iv);
    print_hex("CFB Ciphertext", ciphertext, padded_len);

    return 0;
}

