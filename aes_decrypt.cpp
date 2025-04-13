// aes_decrypt.cpp - Chương trình giải mã AES
#include "aes.h"
#include "file_utils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        if (argc < 4 || argc > 5) {
            std::cerr << "Sử dụng: " << argv[0] << " <input_file> <key_file> <output_file> [aes_type]" << std::endl;
            std::cerr << "  aes_type: 128 (mặc định), 192, 256" << std::endl;
            return 1;
        }
        
        std::string inputFile = argv[1];
        std::string keyFile = argv[2];
        std::string outputFile = argv[3];
        
        // Xác định loại AES
        AES::AESType aesType = AES::AESType::AES_128;  // Mặc định là AES-128
        if (argc == 5) {
            std::string typeStr = argv[4];
            if (typeStr == "192") {
                aesType = AES::AESType::AES_192;
            } else if (typeStr == "256") {
                aesType = AES::AESType::AES_256;
            } else if (typeStr != "128") {
                std::cerr << "Loại AES không hợp lệ. Sử dụng 128, 192, hoặc 256." << std::endl;
                return 1;
            }
        }
        
        // Đọc dữ liệu đầu vào và khóa
        std::string ciphertext = FileUtils::readFile(inputFile);
        std::string key = FileUtils::readKey(keyFile);
        
        // Xác định độ dài khóa cần thiết
        int keySize = 16;  // AES-128
        if (aesType == AES::AESType::AES_192) keySize = 24;
        else if (aesType == AES::AESType::AES_256) keySize = 32;
        
        // Đảm bảo khóa đúng độ dài
        if (key.length() < keySize) {
            key.resize(keySize, '\0');  // Padding với null
        } else if (key.length() > keySize) {
            key = key.substr(0, keySize);  // Cắt ngắn nếu dài
        }
        
        // Giải mã dữ liệu
        std::string plaintext = AES::decrypt(ciphertext, key, aesType);
        
        // Ghi kết quả vào file
        FileUtils::writeOutput(outputFile, plaintext);
        
        std::cout << "Giải mã AES thành công. Kết quả được lưu vào: " << outputFile << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Lỗi: " << e.what() << std::endl;
        return 1;
    }
}