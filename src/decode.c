#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "bmp_utils.h"

static int extract_bit(unsigned char byte) {
    return byte & 1;
}

int decode_message(BMPImage *img, const char *outputText) {
    FILE *out = fopen(outputText, "w");
    if (!out) {
        perror("Error creating output text file");
        return 1;
    }

    unsigned char *data = img->data;
    long dataSize = img->infoHeader.biSizeImage;

    unsigned char ch = 0;
    int bitCount = 0;

    printf("[Decode] Extracting hidden message...\n");

    for (long i = 0; i < dataSize; i++) {
        int bit = extract_bit(data[i]);
        ch = (ch << 1) | bit;
        bitCount++;

        if (bitCount == 8) {
            if (ch == '\0')
                break;
            fputc(ch, out);
            ch = 0;
            bitCount = 0;
        }
    }

    fclose(out);
    printf("[Decode] Message successfully extracted to '%s'.\n", outputText);
    return 0;
}
