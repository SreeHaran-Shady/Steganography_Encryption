#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stddef.h>

int xor_encrypt_decrypt(char *data, size_t length, char key);

#endif
