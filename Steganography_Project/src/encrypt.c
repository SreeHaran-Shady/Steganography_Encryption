#include "encrypt.h"
#include <string.h>

int xor_encrypt_decrypt(char *data, size_t length, char key) {
    if (!data || key == 0) return -1;
    
    for (size_t i = 0; i < length; i++) {
        data[i] ^= key; // XOR encryption/decryption
    }
    return 0;
}
