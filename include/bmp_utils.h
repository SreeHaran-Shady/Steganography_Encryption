#ifndef BMP_UTILS_H
#define BMP_UTILS_H

#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;       // Magic identifier: 0x4d42 ("BM")
    uint32_t bfSize;       // File size in bytes
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;    // Offset to image data in bytes from beginning of file
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;          // Header size in bytes
    int32_t  biWidth;         // Width of image
    int32_t  biHeight;        // Height of image
    uint16_t biPlanes;        // Number of color planes
    uint16_t biBitCount;      // Bits per pixel
    uint32_t biCompression;   // Compression type
    uint32_t biSizeImage;     // Image size in bytes
    int32_t  biXPelsPerMeter; // Pixels per meter X
    int32_t  biYPelsPerMeter; // Pixels per meter Y
    uint32_t biClrUsed;       // Number of colors
    uint32_t biClrImportant;  // Important colors
} BITMAPINFOHEADER;
#pragma pack(pop)

typedef struct {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    unsigned char *data;
} BMPImage;

BMPImage *read_bmp(const char *filename);
void write_bmp(const char *filename, BMPImage *img);
void free_bmp(BMPImage *img);

#endif
