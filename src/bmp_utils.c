#include <stdio.h>
#include <stdlib.h>
#include "bmp_utils.h"

BMPImage *read_bmp(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening BMP file");
        return NULL;
    }

    BMPImage *img = (BMPImage *)malloc(sizeof(BMPImage));
    fread(&img->fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&img->infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    if (img->fileHeader.bfType != 0x4D42) {
        printf("Not a valid BMP file.\n");
        fclose(fp);
        free(img);
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
    fread(img->data, 1, img->infoHeader.biSizeImage, fp);

    fclose(fp);
    return img;
}

void write_bmp(const char *filename, BMPImage *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error creating BMP file");
        return;
    }

    fwrite(&img->fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(&img->infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(img->data, 1, img->infoHeader.biSizeImage, fp);

    fclose(fp);
}

void free_bmp(BMPImage *img) {
    if (img) {
        if (img->data) free(img->data);
        free(img);
    }
}
