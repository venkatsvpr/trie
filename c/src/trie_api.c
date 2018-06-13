#include "trie.h"

/* Function Name :  trie_init
 * Description   :  This function is used to init a trie head node
 *                  creates a TRIE node and inserts it into the
 *                  trie_list. 
 * Return Value  :  OSIX_SUCCESS/OSIX_FAILURE
 */
int trie_init(int trie_id)
{
    node *head_node = NULL;
    head_node = (node *)my_alloc(sizeof(struct node));
    if (head_node == NULL)
    {
        printf(" No memory: %s:%d \r\n",__func__,__LINE__);
        return OSIX_FAILURE;
    }
    
    int i = assign_head(trie_id,head_node);
    return OSIX_SUCCESS;
}
/* Function Name  :  trie_insert_data_into_key
 * Description    :  Insert data(read size from data)
 *                   into the key in the TRIE with id trie_id
 * Return Value   :  OSIX_SUCCESS
 */
int trie_insert_data_into_key(int trie_id, char *key, void *data, int size)
{
    node *head = find_head(trie_id);
    int i = 0;
    node *curr_node = head;
    for (i = 0 ; i <strlen(key); i++)
    {
        create_node(curr_node,key[i]);
        curr_node = get_next_ptr(curr_node,key[i]);
    }                                                                                   
    insert_data(curr_node,data,size);
    return OSIX_SUCCESS;
}
/* Function Name   : print_node
 * Description     : print the contents
 */
void print_node(node *curr_node)
{
    char tptr[256];
    int i = 0;
    

    if (curr_node == NULL)
        return;

    printf (" .%c ",curr_node->data_char);
    if (curr_node->is_data_present)
    {
        memset(tptr,0,256);
        memcpy(tptr,curr_node->data,curr_node->size);
        printf (" [data]:--> %s\n",tptr);
    }

    for (i=0;i<256;i++)
    {
        node *nxt_ptr = curr_node->next_ptr[i];
        if (nxt_ptr)
        {
            print_node(nxt_ptr);
        }
    }
    return;
}


void trie_deinit (int trie_id)
{
    free_node(find_head(trie_id));
    return;
}

/* Function Name :  find_data_from_id
 * Description   :  find the data in the trie_id and key
 * Return Value  :  node ptr/NULL
 */
void *find_data_from_id(int trie_id, char*key)
{
    return (find_data(trie_id,find_head(trie_id),key,0));
}

/* Function Name : trie_init_globals
 * Description   : Used to init global structures 
 */
void trie_init_globals(void)
{
    int i=0;
    for (i=0; i<MAX_TRIE_NODES; i++)
    {
        trie_list[i] = NULL;
    }
    return;
}
 
/* Function Name : trie_deinit_globals
 * Description   : Used to deinit global structures 
 */
void trie_deinit_globals(void)
{
    int i=0;
    for (i=0; i<MAX_TRIE_NODES; i++)
    {
        if (trie_list[i])
            trie_deinit(i);            
        trie_list[i] = NULL;
    }
    return;
}
 

