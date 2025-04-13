// file_utils.cpp - Triển khai xử lý file
#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace FileUtils {
    // Đọc nội dung từ file
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Không thể mở file: " + filename);
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    // Ghi nội dung vào file
    void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Không thể tạo file: " + filename);
        }
        
        file << content;
        if (!file) {
            throw std::runtime_error("Lỗi khi ghi vào file: " + filename);
        }
    }
    
    // Đọc khóa từ file
    std::string readKey(const std::string& filename) {
        return readFile(filename);
    }
    
    // Ghi kết quả mã hóa/giải mã vào file
    void writeOutput(const std::string& filename, const std::string& output) {
        writeFile(filename, output);
    }
}