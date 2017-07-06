OBJ_DIR=obj
EXE_DIR=bin
SRC_DIR=src
INC_DIR=inc
CC=gcc

$(OBJ_DIR)/trie_api.o: $(SRC_DIR)/trie_api.c $(INC_DIR)/trie.h
	$(CC) -c $(SRC_DIR)/trie_api.c -I $(INC_DIR)/trie.h  

hello: $(OBJ_DIR)/trie_api.o $(OBJ_DIR)/trie_main.o
	$(CC) $(OBJ_DIR)/trie_api.o $(OBJ_DIR)/trie_main.o -o $(EXE_DIR)

clean: 
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(EXE_DIR)/*
 
