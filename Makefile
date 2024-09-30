BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -o $(BIN_DIR)/main -I $(INCLUDE_DIR) $(SRC_DIR)/main.c $(SRC_DIR)/hash.c
LDFLAGS = -lcrypto
COMPILER = gcc

main:
	$(COMPILER) $(CFLAGS) $(LDFLAGS)
