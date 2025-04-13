// des_encrypt.cpp - Chương trình mã hóa DES
#include "des.h"
#include "file_utils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cerr << "Sử dụng: " << argv[0] << " <input_file> <key_file> <output_file>" << std::endl;
            return 1;
        }
        
        std::string inputFile = argv[1];
        std::string keyFile = argv[2];
        std::string outputFile = argv[3];
        
        // Đọc dữ liệu đầu vào và khóa
        std::string plaintext = FileUtils::readFile(inputFile);
        std::string key = FileUtils::readKey(keyFile);
        
        // Đảm bảo khóa đủ 8 byte (64 bit) cho DES
        if (key.length() < 8) {
            key.resize(8, '\0');  // Padding với null
        } else if (key.length() > 8) {
            key = key.substr(0, 8);  // Cắt ngắn nếu dài
        }
        
        // Mã hóa dữ liệu
        std::string ciphertext = DES::encrypt(plaintext, key);
        
        // Ghi kết quả vào file
        FileUtils::writeOutput(outputFile, ciphertext);
        
        std::cout << "Mã hóa DES thành công. Kết quả được lưu vào: " << outputFile << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Lỗi: " << e.what() << std::endl;
        return 1;
    }
}