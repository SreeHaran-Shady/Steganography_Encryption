#include "encrypt.h"

void xor_encrypt_decrypt(char *data, char key) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key; // XOR encryption/decryption
    }
}
