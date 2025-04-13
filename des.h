// des.h - Thư viện mã hóa và giải mã DES
#ifndef DES_H
#define DES_H

#include <vector>
#include <string>

namespace DES {
    // Các hằng số và bảng cho thuật toán DES
    extern const int IP[64];  // Initial Permutation
    extern const int IP_1[64];  // Final Permutation
    extern const int PC_1[56];  // Permuted Choice 1
    extern const int PC_2[48];  // Permuted Choice 2
    extern const int E[48];  // Expansion
    extern const int P[32];  // Permutation
    extern const int S[8][4][16];  // S-boxes
    extern const int SHIFT[16];  // Left shifts

    // Cấu trúc dữ liệu cho block 64-bit
    typedef std::vector<bool> Block;
    typedef std::vector<bool> Key;

    // Các hàm xử lý bit
    Block permute(const Block& block, const int* table, int size);
    Block shiftLeft(const Block& block, int shift);
    Block xorBlocks(const Block& block1, const Block& block2);
    
    // Các hàm chuyển đổi
    Block stringToBlock(const std::string& str);
    std::string blockToString(const Block& block);
    Block hexStringToBlock(const std::string& hex);
    std::string blockToHexString(const Block& block);
    
    // Các hàm cho một vòng DES
    std::vector<Block> generateSubkeys(const Block& key);
    Block f(const Block& R, const Block& subkey);
    Block sBox(const Block& block);
    
    // Các hàm chính
    Block encryptBlock(const Block& plaintext, const Block& key);
    Block decryptBlock(const Block& ciphertext, const Block& key);
    
    // Các hàm wrapper
    std::string encrypt(const std::string& plaintext, const std::string& key);
    std::string decrypt(const std::string& ciphertext, const std::string& key);
}

#endif // DES_H