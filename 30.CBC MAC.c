#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16

void block_cipher(const unsigned char *input, const unsigned char *key, unsigned char *output) {
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void cbc_mac(const unsigned char *message, int msg_len, const unsigned char *key, unsigned char *mac) {
    unsigned char previous[BLOCK_SIZE] = {0};
    unsigned char block[BLOCK_SIZE];
    int i, j;

    for (i = 0; i < msg_len; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            block[j] = message[i + j] ^ previous[j];
        }
        block_cipher(block, key, previous);
    }
    memcpy(mac, previous, BLOCK_SIZE);
}

int main() {
    unsigned char key[BLOCK_SIZE] = "thisisakey123456";
    unsigned char message[BLOCK_SIZE] = "oneblockmsg1234";
    unsigned char mac[BLOCK_SIZE];
    unsigned char two_block_message[2 * BLOCK_SIZE];
    int i;

    cbc_mac(message, BLOCK_SIZE, key, mac);

    printf("CBC-MAC of single block message: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    memcpy(two_block_message, message, BLOCK_SIZE);
    for (i = 0; i < BLOCK_SIZE; i++) {
        two_block_message[BLOCK_SIZE + i] = message[i] ^ mac[i];
    }

    cbc_mac(two_block_message, 2 * BLOCK_SIZE, key, mac);

    printf("CBC-MAC of two-block message: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

