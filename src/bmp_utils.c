#include <stdio.h>
#include <stdlib.h>
#include "bmp_utils.h"

#define BMP_SIGNATURE 0x4D42
#define MAX_BMP_SIZE 100000000  // 100MB limit for safety

BMPImage *read_bmp(const char *filename) {
    if (!filename) {
        printf("Error: Invalid filename\n");
        return NULL;
    }
    
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening BMP file");
        return NULL;
    }

    BMPImage *img = (BMPImage *)malloc(sizeof(BMPImage));
    if (!img) {
        printf("Error: Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }
    
    if (fread(&img->fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) != 1 ||
        fread(&img->infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        printf("Error: Failed to read BMP headers\n");
        free(img);
        fclose(fp);
        return NULL;
    }

    if (img->fileHeader.bfType != BMP_SIGNATURE) {
        printf("Not a valid BMP file.\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    // Validate BMP header fields
    if (img->infoHeader.biWidth <= 0 || img->infoHeader.biHeight <= 0 || 
        img->infoHeader.biBitCount == 0) {
        printf("Error: Invalid BMP dimensions\n");
        free(img);
        fclose(fp);
        return NULL;
    }
    
    // Calculate biSizeImage if it's 0 (valid for uncompressed BMPs)
    if (img->infoHeader.biSizeImage == 0) {
        int bytesPerPixel = img->infoHeader.biBitCount / 8;
        img->infoHeader.biSizeImage = img->infoHeader.biWidth * 
                                      abs(img->infoHeader.biHeight) * bytesPerPixel;
    }
    
    // Validate calculated size
    if (img->infoHeader.biSizeImage > MAX_BMP_SIZE) {
        printf("Error: Image too large\n");
        free(img);
        fclose(fp);
        return NULL;
    }
    
    img->data = (unsigned char *)malloc(img->infoHeader.biSizeImage);
    if (!img->data) {
        printf("Memory allocation failed for image data.\n");
        fclose(fp);
        free(img);
        return NULL;
    }
    fseek(fp, img->fileHeader.bfOffBits, SEEK_SET);
    if (fread(img->data, 1, img->infoHeader.biSizeImage, fp) != img->infoHeader.biSizeImage) {
        printf("Error: Failed to read image data\n");
        free(img->data);
        free(img);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return img;
}

int write_bmp(const char *filename, BMPImage *img) {
    if (!filename || !img) {
        printf("Error: Invalid parameters for write_bmp\n");
        return -1;
    }
    
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error creating BMP file");
        return -1;
    }

    if (fwrite(&img->fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) != 1 ||
        fwrite(&img->infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        printf("Error: Failed to write BMP headers\n");
        fclose(fp);
        return -1;
    }
    
    fseek(fp, img->fileHeader.bfOffBits, SEEK_SET);
    if (fwrite(img->data, 1, img->infoHeader.biSizeImage, fp) != img->infoHeader.biSizeImage) {
        printf("Error: Failed to write BMP data\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

void free_bmp(BMPImage *img) {
    if (img) {
        if (img->data) free(img->data);
        free(img);
    }
}
