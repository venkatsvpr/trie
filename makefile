OBJ_DIR=$(PWD)/obj
EXE_DIR=$(PWD)/bin
SRC_DIR=$(PWD)/src
INC_DIR=$(PWD)/inc
CC=gcc

$(OBJ_DIR)/trie_api.o: $(SRC_DIR)/trie_api.c
	$(CC) -I $(INC_DIR) -c $(SRC_DIR)/trie_api.c  -o  $(OBJ_DIR)/trie_api.o

$(OBJ_DIR)/trie_main.o: $(SRC_DIR)/trie_main.c
	$(CC) -I $(INC_DIR) -c $(SRC_DIR)/trie_main.c  -o  $(OBJ_DIR)/trie_main.o

$(EXE_DIR)/trie: $(OBJ_DIR)/trie_api.o $(OBJ_DIR)/trie_main.o 
	$(CC) -I $(INC_DIR) $(OBJ_DIR)/trie_api.o $(OBJ_DIR)/trie_main.o -o $(EXE_DIR)/trie


all: $(EXE_DIR)/trie 

clean: 
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(EXE_DIR)/*
 
