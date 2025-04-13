// aes.h - Thư viện mã hóa và giải mã AES
#ifndef AES_H
#define AES_H

#include <vector>
#include <string>
#include <array>

namespace AES {
    // Loại AES (128, 192, 256)
    enum class AESType {
        AES_128,
        AES_192,
        AES_256
    };

    // Các hằng số AES
    constexpr int BLOCK_SIZE = 16; // 128 bit
    constexpr int WORD_SIZE = 4; // 32 bit
    
    // Cấu trúc dữ liệu cho state matrix
    typedef std::array<std::array<unsigned char, 4>, 4> State;
    typedef std::vector<unsigned char> Bytes;
    typedef std::vector<std::vector<unsigned char>> RoundKeys;
    
    // Các hàm biến đổi cơ bản
    unsigned char xtime(unsigned char b);
    unsigned char multiply(unsigned char a, unsigned char b);
    
    // Các hàm biến đổi dành cho SubBytes
    unsigned char subByte(unsigned char byte);
    unsigned char invSubByte(unsigned char byte);
    
    // Các hàm cho key expansion
    Bytes keyExpansion(const Bytes& key, AESType type);
    void subWord(std::vector<unsigned char>& word);
    void rotWord(std::vector<unsigned char>& word);
    
    // Các hàm biến đổi state
    void subBytes(State& state);
    void invSubBytes(State& state);
    void shiftRows(State& state);
    void invShiftRows(State& state);
    void mixColumns(State& state);
    void invMixColumns(State& state);
    void addRoundKey(State& state, const std::vector<unsigned char>& roundKey);
    
    // Các hàm chính
    State encrypt(const State& plaintext, const Bytes& key, AESType type);
    State decrypt(const State& ciphertext, const Bytes& key, AESType type);
    
    // Các hàm chuyển đổi
    State bytesToState(const Bytes& bytes);
    Bytes stateToBytes(const State& state);
    Bytes stringToBytes(const std::string& str);
    std::string bytesToString(const Bytes& bytes);
    Bytes hexStringToBytes(const std::string& hex);
    std::string bytesToHexString(const Bytes& bytes);
    
    // Các hàm wrapper
    std::string encrypt(const std::string& plaintext, const std::string& key, AESType type = AESType::AES_128);
    std::string decrypt(const std::string& ciphertext, const std::string& key, AESType type = AESType::AES_128);
}

#endif // AES_H