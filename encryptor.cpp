#include "encryptor.h"

Encryptor::Encryptor(const std::string& k) : key(k) {} //sets the key

Encryptor::~Encryptor() {}

std::string Encryptor::encrypt(const std::string& plainText) { //xor encryption
    std::string encrypted = plainText;
    for (char &c : encrypted) {
        c ^= key[0];
    }
    return encrypted;
}

std::string Encryptor::decrypt(const std::string& cipherText) { //symmetrical
    std::string decrypted = cipherText;
    for (char &c : decrypted) {
        c ^= key[0];
    }
    return decrypted;
}

std::ostream& operator<<(std::ostream& os, const Encryptor& e) { //overloaded operator
    os << "Encryptor with key: " << e.key;
    return os;
}
