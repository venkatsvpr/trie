#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

typedef int bool;
#define true 1
#define false 0

#define TRIE_ID 1

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

static node *trie_head = NULL;

void *my_alloc(int size);
int create_trie(int trie_id);
node * find_head(int trie_id);
int assign_head(int trie_id, node *h_node);
int create_node(node *curr_node, char new_char);
node *get_next_ptr(node *curr_node, char new_char);
int insert_data(node *curr_node, void *data, int size);
int trie_insert(int trie_id, char *word, void *data, int size);
void free_node(node *new_node);
void print_node(node *new_node);
