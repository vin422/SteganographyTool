#ifndef BITMAPIMG_H
#define BITMAPIMG_H


#include <string>
#include <iostream>
#include <exception>

// Use #pragma pack to ensure the structures match the BMP binary layout.
#pragma pack(push, 1)
struct BitmapFileHeader { //we use struct instead of class because its public by default and is merely a collection of data
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitmapInfoHeader {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
};
#pragma pack(pop)

// Define the BMPImage class.
class BMPImage {
public:
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    unsigned char* data;

    BMPImage();
    ~BMPImage();

    bool load(const std::string& filename);
};


#endif // BITMAPIMG_H
