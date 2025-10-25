#include "hideandseek.h"
#include <iostream>
#include <stdexcept>

TextSteganography::TextSteganography(const std::string& file)
    : Steganography(file) {}

TextSteganography::~TextSteganography() {}

void TextSteganography::encode(const std::string& message) {
    std::string binary = stringToBinary(message);  // Adds '~' at the end

    int width = infoHeader.biWidth;
    int height = std::abs(infoHeader.biHeight);
    int rowSize = (width * 3 + 3) & ~3;

    size_t bitIndex = 0;
    for (int y = height - 1; y >= 0 && bitIndex < binary.size(); --y) {
        for (int x = 0; x < width && bitIndex < binary.size(); ++x) {
            int pixelIndex = y * rowSize + x * 3;
            if (pixelIndex + 2 >= bufferSize) break;

            for (int c = 0; c < 3 && bitIndex < binary.size(); ++c) {
                imageBuffer[pixelIndex + c] &= 0xFE;
                imageBuffer[pixelIndex + c] |= (binary[bitIndex++] == '1');
            }
        }
    }

    std::cout << "Message encoded in image." << std::endl;
}

std::string TextSteganography::decode() {
    std::string binary;
    int width = infoHeader.biWidth;
    int height = std::abs(infoHeader.biHeight);
    int rowSize = (width * 3 + 3) & ~3;

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            int pixelIndex = y * rowSize + x * 3;
            if (pixelIndex + 2 >= bufferSize) break;

            for (int c = 0; c < 3; ++c) {
                binary += (imageBuffer[pixelIndex + c] & 1) ? '1' : '0';
            }
        }
    }

// Decode the whole binary message once
std::string result = binaryToString(binary);

// Trim after delimiter
size_t end = result.find('~');
if (end != std::string::npos) {
    result = result.substr(0, end);
}

std::cout << "Message decoded from image." << std::endl;
return result;
}
