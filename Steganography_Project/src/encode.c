#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "encode.h"
#include "bmp_utils.h"

static int is_safe_path(const char *path) {
    if (!path) return 0;
    
    // Check for dangerous path traversal sequences
    if (strstr(path, "..") || strstr(path, "//")) {
        return 0;
    }
    
    // Reject absolute paths on Unix/Linux
    if (path[0] == '/') {
        return 0;
    }
    
    // Reject Windows absolute paths (C:, D:, etc.)
    if (strlen(path) > 1 && path[1] == ':') {
        return 0;
    }
    
    return 1;
}

static void embed_bit(unsigned char *byte, int bit) {
    // Clear the LSB and set it to the message bit
    *byte = (*byte & 0xFE) | (bit & 1);
}

int encode_message(BMPImage *img, const char *messageFile, const char *outputFile) {
    if (!img || !messageFile || !outputFile) {
        printf("Error: Invalid parameters\n");
        return 1;
    }
    
    if (!is_safe_path(messageFile) || !is_safe_path(outputFile)) {
        printf("Error: Invalid file path\n");
        return 1;
    }
    
    FILE *msg = fopen(messageFile, "rb");
    if (!msg) {
        perror("Error opening message file");
        return 1;
    }

    // Get message length
    fseek(msg, 0, SEEK_END);
    long msgSize = ftell(msg);
    if (msgSize == -1) {
        printf("Error: Failed to get file size\n");
        fclose(msg);
        return 1;
    }
    rewind(msg);

    char *buffer = (char *)malloc(msgSize + 1);
    if (!buffer) {
        printf("Error: Memory allocation failed\n");
        fclose(msg);
        return 1;
    }
    
    if (fread(buffer, 1, msgSize, msg) != msgSize) {
        printf("Error: Failed to read message file\n");
        free(buffer);
        fclose(msg);
        return 1;
    }
    buffer[msgSize] = '\0';
    fclose(msg);

    // Check for integer overflow
    if (msgSize > LONG_MAX / 8 - 8) {
        printf("Error: Message too large\n");
        free(buffer);
        return 1;
    }
    
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
            if (dataIndex >= img->infoHeader.biSizeImage) {
                printf("Error: Buffer overflow prevented\n");
                free(buffer);
                return 1;
            }
            int bitVal = (ch >> bit) & 1;
            embed_bit(&data[dataIndex++], bitVal);
        }
    }

    if (write_bmp(outputFile, img) != 0) {
        printf("Error: Failed to write output BMP file\n");
        free(buffer);
        return 1;
    }
    printf("[Encode] Message successfully embedded into '%s'.\n", outputFile);

    free(buffer);
    return 0;
}
