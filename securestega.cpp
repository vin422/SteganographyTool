#include "securestega.h"
#include <iostream>

SecureSteganography::SecureSteganography(const std::string& file, const std::string& k)
    : TextSteganography(file), Encryptor(k) {}

SecureSteganography::~SecureSteganography() {}

void SecureSteganography::encode(const std::string& message) {
    std::cout << "secure encoding." << std::endl;
    std::string encryptedMsg = encrypt(message);
    TextSteganography::encode(encryptedMsg);//hides enc msg
}

std::string SecureSteganography::decode() {
    std::cout << "secure decoding" << std::endl;
    std::string extracted = TextSteganography::decode();
    return decrypt(extracted);
}
