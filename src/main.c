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
    
    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid input. Please enter a number.\n");
        return 1;
    }
    
    if (choice < 1 || choice > 2) {
        printf("Error: Invalid choice. Please enter 1 or 2.\n");
        return 1;
    }

    if (choice == 1) {
        BMPImage *img = read_bmp(inputImage);
        if (!img) return 1;
        
        if (encode_message(img, secretFile, outputImage) != 0) {
            printf("Encoding failed.\n");
        } else {
            printf("Encoding successful.\n");
        }
        free_bmp(img);
    } else if (choice == 2) {
        BMPImage *img = read_bmp(outputImage);
        if (!img) return 1;
        
        if (decode_message(img, decodedText) != 0) {
            printf("Decoding failed.\n");
        } else {
            printf("Decoding successful.\n");
        }
        free_bmp(img);
    }

    return 0;
}
