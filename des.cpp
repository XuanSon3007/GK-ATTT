// des.cpp - Triển khai thuật toán DES
#include "des.h"
#include <iostream>
#include <bitset>
#include <sstream>
#include <iomanip>

namespace DES {
    // Các bảng permutation của DES
    const int IP[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    const int IP_1[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };

    const int PC_1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };

    const int PC_2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

    const int E[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };

    const int P[32] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    };

    const int S[8][4][16] = {
        {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
        },
        {
            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
            {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
            {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
            {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
        },
        {
            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
            {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
        },
        {
            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
            {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
            {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
            {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
        },
        {
            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
            {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
            {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
        },
        {
            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
            {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
            {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
        },
        {
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
            {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
        },
        {
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
            {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
        }
    };

    const int SHIFT[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    // Thực hiện phép hoán vị trên block dữ liệu
    Block permute(const Block& block, const int* table, int size) {
        Block result(size);
        for (int i = 0; i < size; i++) {
            result[i] = block[table[i] - 1];
        }
        return result;
    }

    // Dịch trái block dữ liệu
    Block shiftLeft(const Block& block, int shift) {
        Block result = block;
        int size = block.size();
        for (int i = 0; i < size; i++) {
            result[i] = block[(i + shift) % size];
        }
        return result;
    }

    // Phép XOR hai block
    Block xorBlocks(const Block& block1, const Block& block2) {
        Block result(block1.size());
        for (size_t i = 0; i < block1.size(); i++) {
            result[i] = block1[i] ^ block2[i];
        }
        return result;
    }

    // Chuyển đổi chuỗi thành block bit
    Block stringToBlock(const std::string& str) {
        Block block(64, false);
        for (size_t i = 0; i < 8 && i < str.length(); i++) {
            std::bitset<8> bits(str[i]);
            for (int j = 0; j < 8; j++) {
                block[i * 8 + j] = bits[7 - j];
            }
        }
        return block;
    }

    // Chuyển đổi block bit thành chuỗi
    std::string blockToString(const Block& block) {
        std::string result;
        for (size_t i = 0; i < block.size(); i += 8) {
            std::bitset<8> bits;
            for (int j = 0; j < 8; j++) {
                bits[7 - j] = block[i + j];
            }
            result += static_cast<char>(bits.to_ulong());
        }
        return result;
    }

    // Chuyển đổi chuỗi hex thành block bit
    Block hexStringToBlock(const std::string& hex) {
        Block block(64, false);
        for (size_t i = 0; i < 16 && i < hex.length(); i++) {
            int value;
            std::stringstream ss;
            ss << std::hex << hex[i];
            ss >> value;
            
            for (int j = 0; j < 4; j++) {
                block[i * 4 + j] = (value >> (3 - j)) & 1;
            }
        }
        return block;
    }

    // Chuyển đổi block bit thành chuỗi hex
    std::string blockToHexString(const Block& block) {
        std::stringstream ss;
        for (size_t i = 0; i < block.size(); i += 4) {
            int value = 0;
            for (int j = 0; j < 4; j++) {
                value = (value << 1) | block[i + j];
            }
            ss << std::hex << value;
        }
        return ss.str();
    }

    // Tạo các subkey từ key chính
    std::vector<Block> generateSubkeys(const Block& key) {
        // Áp dụng PC-1
        Block permutedKey = permute(key, PC_1, 56);
        
        // Chia thành hai nửa
        Block C(28), D(28);
        for (int i = 0; i < 28; i++) {
            C[i] = permutedKey[i];
            D[i] = permutedKey[i + 28];
        }
        
        // Tạo 16 subkey
        std::vector<Block> subkeys(16);
        for (int i = 0; i < 16; i++) {
            // Dịch trái
            C = shiftLeft(C, SHIFT[i]);
            D = shiftLeft(D, SHIFT[i]);
            
            // Ghép hai nửa
            Block CD(56);
            for (int j = 0; j < 28; j++) {
                CD[j] = C[j];
                CD[j + 28] = D[j];
            }
            
            // Áp dụng PC-2
            subkeys[i] = permute(CD, PC_2, 48);
        }
        
        return subkeys;
    }

    // Hàm f trong vòng DES
    Block f(const Block& R, const Block& subkey) {
        // Mở rộng R từ 32 bit thành 48 bit
        Block expandedR = permute(R, E, 48);
        
        // XOR với subkey
        Block xored = xorBlocks(expandedR, subkey);
        
        // Áp dụng S-box
        Block sBoxOutput = sBox(xored);
        
        // Áp dụng permutation P
        return permute(sBoxOutput, P, 32);
    }

    // Áp dụng S-box
    Block sBox(const Block& block) {
        Block result(32);
        for (int i = 0; i < 8; i++) {
            // Lấy 6 bit tương ứng
            int row = (block[i * 6] << 1) | block[i * 6 + 5];
            int col = (block[i * 6 + 1] << 3) | (block[i * 6 + 2] << 2) | 
                     (block[i * 6 + 3] << 1) | block[i * 6 + 4];
            
            // Lấy giá trị từ S-box
            int value = S[i][row][col];
            
            // Chuyển đổi thành 4 bit
            for (int j = 0; j < 4; j++) {
                result[i * 4 + j] = (value >> (3 - j)) & 1;
            }
        }
        return result;
    }

    // Mã hóa một block 64-bit
    Block encryptBlock(const Block& plaintext, const Block& key) {
        // Áp dụng hoán vị ban đầu
        Block permuted = permute(plaintext, IP, 64);
        
        // Chia thành hai nửa
        Block L(32), R(32);
        for (int i = 0; i < 32; i++) {
            L[i] = permuted[i];
            R[i] = permuted[i + 32];
        }
        
        // Tạo các subkey
        std::vector<Block> subkeys = generateSubkeys(key);
        
        // 16 vòng của DES
        for (int i = 0; i < 16; i++) {
            Block tempL = L;
            L = R;
            R = xorBlocks(tempL, f(R, subkeys[i]));
        }
        
        // Ghép hai nửa (hoán đổi L và R)
        Block combined(64);
        for (int i = 0; i < 32; i++) {
            combined[i] = R[i];
            combined[i + 32] = L[i];
        }
        
        // Áp dụng hoán vị cuối
        return permute(combined, IP_1, 64);
    }

    // Giải mã một block 64-bit
    Block decryptBlock(const Block& ciphertext, const Block& key) {
        // Áp dụng hoán vị ban đầu
        Block permuted = permute(ciphertext, IP, 64);
        
        // Chia thành hai nửa
        Block L(32), R(32);
        for (int i = 0; i < 32; i++) {
            L[i] = permuted[i];
            R[i] = permuted[i + 32];
        }
        
        // Tạo các subkey (sử dụng thứ tự ngược lại)
        std::vector<Block> subkeys = generateSubkeys(key);
        
        // 16 vòng của DES
        for (int i = 0; i < 16; i++) {
            Block tempL = L;
            L = R;
            R = xorBlocks(tempL, f(R, subkeys[15 - i]));
        }
        
        // Ghép hai nửa (hoán đổi L và R)
        Block combined(64);
        for (int i = 0; i < 32; i++) {
            combined[i] = R[i];
            combined[i + 32] = L[i];
        }
        
        // Áp dụng hoán vị cuối
        return permute(combined, IP_1, 64);
    }

    // Hàm mã hóa chuỗi
    std::string encrypt(const std::string& plaintext, const std::string& key) {
        std::string result;
        Block keyBlock = stringToBlock(key);
        
        // Xử lý từng khối 8 byte
        for (size_t i = 0; i < plaintext.length(); i += 8) {
            std::string block = plaintext.substr(i, 8);
            // Padding nếu cần
            while (block.length() < 8) {
                block += '\0';
            }
            
            Block plaintextBlock = stringToBlock(block);
            Block ciphertextBlock = encryptBlock(plaintextBlock, keyBlock);
            result += blockToString(ciphertextBlock);
        }
        
        return result;
    }

    // Hàm giải mã chuỗi
    std::string decrypt(const std::string& ciphertext, const std::string& key) {
        std::string result;
        Block keyBlock = stringToBlock(key);
        
        // Xử lý từng khối 8 byte
        for (size_t i = 0; i < ciphertext.length(); i += 8) {
            std::string block = ciphertext.substr(i, 8);
            // Cần đủ 8 byte
            if (block.length() < 8) {
                break;
            }
            
            Block ciphertextBlock = stringToBlock(block);
            Block plaintextBlock = decryptBlock(ciphertextBlock, keyBlock);
            result += blockToString(plaintextBlock);
        }
        
        // Loại bỏ padding
        size_t nullPos = result.find('\0');
        if (nullPos != std::string::npos) {
            result = result.substr(0, nullPos);
        }
        
        return result;
    }
}