#include "trie.h"
void *my_alloc(int size)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
        memset(ptr,0,size);
    return ptr;
}
int create_trie(int trie_id)
{
    node *head_node = NULL;
    head_node = (node *)my_alloc(sizeof(struct node));
    if (head_node == NULL)
    {
        printf(" No memory: %s:%d \r\n",__func__,__LINE__);
        return OSIX_FAILURE;
    }
    
    assign_head(trie_id,head_node);
    return OSIX_SUCCESS;
}

node * find_head(trie_id)
{
    return head;
}

int assign_head(int trie_id, node *head_node)
{
    head = head_node;
    return OSIX_SUCCESS;
}

int create_node(node *curr_node, char new_char)
{
    int ascii_char = new_char;
    if (curr_node->next_ptr[ascii_char] != NULL)
        return OSIX_FAILURE;
    
    curr_node->next_ptr[ascii_char] = (node *)my_alloc(sizeof(node));
    
    if (curr_node->next_ptr[ascii_char] == NULL)
        return OSIX_FAILURE;

    node *nxt_ptr = curr_node->next_ptr[ascii_char];
    nxt_ptr->data_char = new_char;  
    return OSIX_SUCCESS;
}

node *get_next_ptr(node *curr_node, char new_char)
{   
    int ascii_char = new_char;
    node *nxt_ptr = curr_node->next_ptr[ascii_char];
    return nxt_ptr;
}

int insert_data(node *curr_node, char *data)
{
    curr_node->data = (char *)my_malloc(strlen(data));
    strncpy(curr_node->data,data,strlen(data));
    return OSIX_SUCCESS; 
}

int trie_insert(int trie_id, char *word, char *data)
{
    node *head = find_head(trie_id);
    int i = 0;
    node *curr_node = head;
    node *save_node = NULL;
    for (i = 0 ; i <strlen(word), i++)
    {
        save_node = curr_node;
        create_node(curr_node,word[i]);
        curr_node = get_next_ptr(curr_node,word[i]);
    }                                                                                                        

    insert_data(save_node,data);
    return OSIX_SUCCESS;
}


