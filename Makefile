BIN_DIR = bin
SYSTEM_BIN = /usr/bin
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -o $(BIN_DIR)/hasshu -I $(INCLUDE_DIR) $(SRC_DIR)/hasshu.c $(SRC_DIR)/hash.c
LDFLAGS = -lcrypto
COMPILER = gcc

hasshu: $(SRC_DIR)
	$(COMPILER) $(CFLAGS) $(LDFLAGS)


install: hasshu
	install -D $(BIN_DIR)/hasshu $(SYSTEM_BIN)/hasshu 
