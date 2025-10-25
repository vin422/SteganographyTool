#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <string>
#include <iostream>

#pragma pack(push, 1)
struct BitmapFileHeader { //14 bytes
    uint16_t bfType; //always 0x4d42 must be
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits; //offset to pixel data
};

struct BitmapInfoHeader { //usually 40, all abou tthe image
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes; //color planes
    uint16_t biBitCount; // must be 24 bits per pixel
    uint32_t biCompression; //compressed/uncompressed
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter; //horizontal res
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop) //ensures theres no padding so it mateches whats in bmp

class Steganography { //abstract base class
protected: //state of loaded img
    std::string filePath;
    unsigned char* imageBuffer;
    size_t bufferSize;

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

public:
    Steganography(const std::string& file);
    virtual ~Steganography(); //for base class

    virtual void encode(const std::string& message) = 0; //must be implemented by derived claass
    virtual std::string decode() = 0;

    virtual void loadImage();
    virtual void saveImage();
};
std::string stringToBinary(const std::string& message);
std::string binaryToString(const std::string& binary);


#endif

