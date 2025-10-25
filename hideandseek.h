#ifndef HIDEANDSEEK_H
#define HIDEANDSEEK_H

#include "steganography.h"
#include <string>

class TextSteganography : public Steganography {
public:
    TextSteganography(const std::string& file);
    virtual ~TextSteganography();

    void encode(const std::string& message) override;
    std::string decode() override;
};

#endif

