#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>
#include <iostream>

class Encryptor {
protected:
    std::string key;

public:
    Encryptor(const std::string& k = "defaultKey");
    virtual ~Encryptor();

    virtual std::string encrypt(const std::string& plainText);
    virtual std::string decrypt(const std::string& cipherText);

    friend std::ostream& operator<<(std::ostream& os, const Encryptor& e);
};

#endif
