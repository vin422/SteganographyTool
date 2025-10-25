#ifndef SECURESTEGA_H //header guard
#define SECURESTEGA_H

#include "hideandseek.h"
#include "encryptor.h"
#include <string>

class SecureSteganography : public TextSteganography, public Encryptor { /*
    inherits 2 classes: hide/extract text from image, encrypt/decrypt text*/
public:
    SecureSteganography(const std::string& file, const std::string& k = "defaultKey"); /*constructor,
    takes filename and key, if no key = default key; code is in securestega.cpp*/
    virtual ~SecureSteganography(); //destructor, this specific class

    void encode(const std::string& message) override; //gives custom version of encode() and decode
    std::string decode() override;
};

#endif
