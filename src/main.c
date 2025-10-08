#include <stdio.h>
#include <stdlib.h>
#include "bmp_utils.h"
#include "encode.h"
#include "decode.h"

int main() {
    int choice;
    char inputImage[100] = "assets/input.bmp";
    char secretFile[100] = "assets/secret.txt";
    char outputImage[100] = "assets/output.bmp";
    char decodedText[100] = "assets/extracted.txt";

    printf("=== IMAGE STEGANOGRAPHY IN C ===\n");
    printf("1. Encode\n");
    printf("2. Decode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    BMPImage *img = read_bmp(inputImage);
    if (!img) return 1;

    if (choice == 1) {
        if (encode_message(img, secretFile, outputImage) != 0) {
            printf("Encoding failed.\n");
        } else {
            printf("Encoding successful.\n");
        }
    } else if (choice == 2) {
        if (decode_message(img, decodedText) != 0) {
            printf("Decoding failed.\n");
        } else {
            printf("Decoding successful.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }

    free_bmp(img);
    return 0;
}
