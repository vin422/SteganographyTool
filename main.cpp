#include <iostream>
#include "securestega.h" //used for encryption and steganography SecureSteganography

int main() {
    try { //catches any runtime exceptions like file loading errors, decrypt issues etc
        std::string imageFile, key, choice;

        std::cout << "Enter image file name (example: image.bmp): ";
        std::getline(std::cin, imageFile); //until newline

        std::cout << "Enter encryption key: ";
        std::getline(std::cin, key);

        SecureSteganography tool(imageFile, key);//main object
        tool.loadImage();//loads image into memory

        std::cout << "Do you want to encode or decode? (e/d): ";
        std::getline(std::cin, choice);

        if (choice == "e") {
            std::string message;
            std::cout << "Enter message to hide: ";
            std::getline(std::cin, message);
            tool.encode(message); //encodes entered msg
            tool.saveImage(); //saves an encoded version as output.bmp
            std::cout << "Message successfully hidden and image saved as output.bmp\n";
        }
        else if (choice == "d") {
            std::string result = tool.decode(); //decodes selected image
            std::cout << "Hidden message: " << result << std::endl;
        }
        else {
            std::cout << "Invalid option. Exiting.\n";
        }

    }
    catch (const std::exception& e) { //pass by ref cuz could be large
        std::cerr << "exception " << e.what() << std::endl; //built in virtual function in stdexception
    }

    return 0;
}

