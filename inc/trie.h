#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

typedef int bool;
#define true 1
#define false 0

#define TRIE_ID 1

#define MAX_TRIE_NODES 16

#define OSIX_SUCCESS 0
#define OSIX_FAILURE 1

typedef struct node
{
    bool is_data_present;
    char data_char;
    struct node *next_ptr[256];
    int size;
    void *data;
}node;

static node *trie_list[MAX_TRIE_NODES];

static node *trie_head = NULL;

void *my_alloc(int size);
int trie_init(int trie_id);
node * find_head(int trie_id);
int assign_head(int trie_id, node *h_node);
int create_node(node *curr_node, char new_char);
node *get_next_ptr(node *curr_node, char new_char);
int insert_data(node *curr_node, void *data, int size);
int trie_insert_data_into_key(int trie_id, char *key, void *data, int size);
void free_node(node *new_node);
void free_node_id(int trie_id);
void print_node(node *new_node);
void * find_data(int trie_id,node *node_ptr, char *key, int offset);
