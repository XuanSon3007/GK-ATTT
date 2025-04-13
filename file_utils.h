// file_utils.h - Thư viện xử lý file
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

namespace FileUtils {
    // Đọc nội dung từ file
    std::string readFile(const std::string& filename);
    
    // Ghi nội dung vào file
    void writeFile(const std::string& filename, const std::string& content);
    
    // Đọc khóa từ file
    std::string readKey(const std::string& filename);
    
    // Ghi kết quả mã hóa/giải mã vào file
    void writeOutput(const std::string& filename, const std::string& output);
}

#endif // FILE_UTILS_H