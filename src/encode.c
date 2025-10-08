#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"
#include "bmp_utils.h"

static void embed_bit(unsigned char *byte, int bit) {
    // Clear the LSB and set it to the message bit
    *byte = (*byte & 0xFE) | (bit & 1);
}

int encode_message(BMPImage *img, const char *messageFile, const char *outputFile) {
    FILE *msg = fopen(messageFile, "rb");
    if (!msg) {
        perror("Error opening message file");
        return 1;
    }

    // Get message length
    fseek(msg, 0, SEEK_END);
    long msgSize = ftell(msg);
    rewind(msg);

    char *buffer = (char *)malloc(msgSize + 1);
    fread(buffer, 1, msgSize, msg);
    buffer[msgSize] = '\0';
    fclose(msg);

    long totalBits = (msgSize + 1) * 8; // include null terminator
    long availableBits = img->infoHeader.biSizeImage * 8;

    if (totalBits > availableBits) {
        printf("Error: Message is too large to fit in this image.\n");
        free(buffer);
        return 1;
    }

    printf("[Encode] Hiding %ld bytes (%ld bits) into image...\n", msgSize, totalBits);

    unsigned char *data = img->data;
    long dataIndex = 0;

    // Loop through each character and embed its bits
    for (long i = 0; i <= msgSize; i++) {
        unsigned char ch = buffer[i];
        for (int bit = 7; bit >= 0; bit--) {
            int bitVal = (ch >> bit) & 1;
            embed_bit(&data[dataIndex++], bitVal);
        }
    }

    write_bmp(outputFile, img);
    printf("[Encode] Message successfully embedded into '%s'.\n", outputFile);

    free(buffer);
    return 0;
}
