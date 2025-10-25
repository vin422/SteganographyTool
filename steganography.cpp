#include "steganography.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <bitset>

Steganography::Steganography(const std::string& file)
    : filePath(file), imageBuffer(nullptr), bufferSize(0) {}

Steganography::~Steganography() {
    if (imageBuffer) {
        delete[] imageBuffer;
    }
}

    void Steganography::loadImage() {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file" + filePath);

    in.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    in.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42) throw std::runtime_error("Not a valid BMP file.");
    if (infoHeader.biBitCount != 24) throw std::runtime_error("Only 24-bit BMP supported.");

    infoHeader.biHeight = std::abs(infoHeader.biHeight);
    int rowSize = (infoHeader.biWidth * 3 + 3) & ~3;
    bufferSize = rowSize * abs(infoHeader.biHeight);
    std::cout << "Calculated buffer size: " << bufferSize << std::endl;





    imageBuffer = new unsigned char[bufferSize];
    in.seekg(fileHeader.bfOffBits, std::ios::beg); //с начала файла, eith byte offset
    in.read(reinterpret_cast<char*>(imageBuffer), bufferSize);
    in.close();

    std::cout << "Image loaded: " << filePath << " (" << bufferSize << " bytes)" << std::endl;
}

void Steganography::saveImage() {
    std::string outputPath = "output.bmp";  // Save to project directory
    std::ofstream out(outputPath, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open output file.");

    if (!imageBuffer || bufferSize == 0) {
        throw std::runtime_error("Image buffer is empty or uninitialized.");
    }

    //Update headers before saving
    fileHeader.bfOffBits = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);  // = 54
    fileHeader.bfSize = fileHeader.bfOffBits + bufferSize;  // total file size

    //Write headers
    out.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (!out) throw std::runtime_error("Failed to write file header.");

    out.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (!out) throw std::runtime_error("Failed to write info header.");

    //Write image data
    out.write(reinterpret_cast<char*>(imageBuffer), bufferSize);
    if (!out) throw std::runtime_error("Failed to write image data.");

    out.close();
    if (!out) throw std::runtime_error("Failed to close output file properly.");

    std::cout << "Image successfully saved as: " << outputPath << std::endl;
}


std::string stringToBinary(const std::string& message) {
    std::string binary;
    for (char c : message) {
        binary += std::bitset<8>(c).to_string();
    }
    binary += std::bitset<8>('~').to_string(); // endinf of message
    return binary;
}

std::string binaryToString(const std::string& binary) {
    std::string message;
    for (size_t i = 0; i + 8 <= binary.size(); i += 8) {
        char c = static_cast<char>(std::bitset<8>(binary.substr(i, 8)).to_ulong());
        if (c == '~') break;
        message += c;
    }
    return message;
}
