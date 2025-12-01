#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "bmp_utils.h"

#define MAX_MESSAGE_LENGTH 1000000

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

static int extract_bit(unsigned char byte) {
    return byte & 1;
}

int decode_message(BMPImage *img, const char *outputText) {
    if (!img || !outputText) {
        printf("Error: Invalid parameters\n");
        return 1;
    }
    
    if (!is_safe_path(outputText)) {
        printf("Error: Invalid file path\n");
        return 1;
    }
    
    // Validate BMP data integrity
    if (!img->data || img->infoHeader.biSizeImage <= 0) {
        printf("Error: Invalid BMP data\n");
        return 1;
    }
    
    FILE *out = fopen(outputText, "w");
    if (!out) {
        perror("Error creating output text file");
        return 1;
    }

    unsigned char *data = img->data;
    long dataSize = img->infoHeader.biSizeImage;
    long maxChars = (dataSize / 8 < MAX_MESSAGE_LENGTH) ? dataSize / 8 : MAX_MESSAGE_LENGTH;
    long charCount = 0;

    unsigned char ch = 0;
    int bitCount = 0;

    printf("[Decode] Extracting hidden message...\n");

    for (long i = 0; i < dataSize && charCount < maxChars; i++) {
        int bit = extract_bit(data[i]);
        ch = (ch << 1) | bit;
        bitCount++;

        if (bitCount == 8) {
            if (ch == '\0')
                break;
            if (fputc(ch, out) == EOF) {
                printf("Error: Failed to write character\n");
                fclose(out);
                return 1;
            }
            bitCount = 0;
            charCount++;
        }
    }

    fclose(out);
    printf("[Decode] Message successfully extracted to '%s'.\n", outputText);
    return 0;
}
