# Makefile cho dự án mã hóa AES và DES

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = 

# Thư mục output
OUTPUT_DIR = bin
OBJ_DIR = obj

# Các file nguồn
SRC_DES = des.cpp file_utils.cpp
SRC_AES = aes.cpp file_utils.cpp

# Tạo thư mục nếu chưa tồn tại
$(shell mkdir -p $(OUTPUT_DIR) $(OBJ_DIR))

# Targets chính
all: $(OUTPUT_DIR)/des_encrypt $(OUTPUT_DIR)/des_decrypt $(OUTPUT_DIR)/aes_encrypt $(OUTPUT_DIR)/aes_decrypt

# DES encrypt
$(OUTPUT_DIR)/des_encrypt: $(OBJ_DIR)/des_encrypt.o $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_DES))
	$(CXX) $(LDFLAGS) $^ -o $@

# DES decrypt
$(OUTPUT_DIR)/des_decrypt: $(OBJ_DIR)/des_decrypt.o $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_DES))
	$(CXX) $(LDFLAGS) $^ -o $@

# AES encrypt
$(OUTPUT_DIR)/aes_encrypt: $(OBJ_DIR)/aes_encrypt.o $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_AES))
	$(CXX) $(LDFLAGS) $^ -o $@

# AES decrypt
$(OUTPUT_DIR)/aes_decrypt: $(OBJ_DIR)/aes_decrypt.o $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_AES))
	$(CXX) $(LDFLAGS) $^ -o $@

# Compile các file .cpp thành .o
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/*

# Phony targets
.PHONY: all clean