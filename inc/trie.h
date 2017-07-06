#include <stdio.h>
#include <string.h>

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
    node *next_ptr[256];
    void *data;
}node;

node *trie_head = NULL;

