#include "trie.h"

/* Function Name :  my_alloc
 * Description   :  This function is used to malloc for specified size
 * Return Value  :  void_ptr
 */
void *my_alloc(int size)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
        memset(ptr,0,size);
    return ptr;
}

/* Function Name :  trie_init
 * Description   :  This function is used to init a trie head node
 *                  creates a TRIE node and inserts it into the
 *                  trie_list. 
 * Return Value  :  OSIX_SUCCESS/OSIX_FAILURE
 */
void my_free(void *void_ptr)
{
    free(void_ptr);
    return;
}

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

/* Function Name :  find_head
 * Description   :  Returns the head node for TRIE_ID.
 * Return Value  :  Head Node/NULL
 */
struct node * find_head(int trie_id)
{
    if (trie_list[trie_id] != NULL)
    {
        return trie_list[trie_id];
    }
    return NULL;
}

/* Function Name :  assign_head
 * Description   :  Assigns head_node for the trie_id
 * Return Value  :  OSIX_SUCCESS
 */
int assign_head(int trie_id, node *h_node)
{
    if (trie_list[trie_id] == NULL)
    {
        trie_list[trie_id] = h_node;
    }
    return OSIX_SUCCESS;
}

int create_node(node *curr_node, char new_char)
{
    int ascii_char = new_char;
    if (curr_node->next_ptr[ascii_char] != NULL)
        return OSIX_SUCCESS;
    
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

int insert_data(node *curr_node, void *data, int size)
{
    if (curr_node->is_data_present == true)
        printf ("conflicting data \r\n");
    curr_node->is_data_present = true;
    curr_node->data = my_alloc(size);
    curr_node->size =size;
    memcpy(curr_node->data,data,size);
    printf ("<%s:%d>  insert successfully at %c size %d\r\n",__func__,__LINE__,curr_node->data_char,size);
    return OSIX_SUCCESS;
}

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

void free_node_id (int trie_id)
{
    free_node(find_head(trie_id));
    return;
}

void free_node(node *curr_node)
{
    node *nxt_ptr;
    int i = 0;
    if (curr_node->is_data_present)
    {
        curr_node->is_data_present = false;
        my_free(curr_node->data);
    }

    for (i = 0 ;i < 256; i++)
    {
        nxt_ptr = curr_node->next_ptr[i];
        if (nxt_ptr != NULL)
        {
            free_node(nxt_ptr);
            curr_node->next_ptr[i]=NULL;
        }
    }
    
    my_free(curr_node);
    return;
}   

/* Function Name :  find_data_from_id
 * Description   :  find the data in the trie_id and key
 * Return Value  :  node ptr/NULL
 */
void *find_data_from_id(int trie_id, char*key)
{
    return (find_data(trie_id,find_head(trie_id,key,0);
}
 
/* Function Name :  find_data
 * Description   :  find the data in the trie_id and key 
 *                  offset - initially called with 0, incremented
 *                  everytime.
 * Return Value  :  node ptr/NULL
 */
void * find_data(int trie_id,node *node_ptr, char *key, int offset)
{
    if (node_ptr == NULL)
        return NULL;

    char c = key[offset];    
   // printf ("<%c > str:%s offset %d\r\n",c,str,offset);
    if (offset == strlen(key))
    {
        if (node_ptr->is_data_present)
        {
     //       printf("< returning node>\r\n");
            return node_ptr;
        }
        else
        {
            return NULL;
        }
    }
    node *nxt_ptr = node_ptr->next_ptr[c];
    find_data(trie_id,nxt_ptr,key,offset+1);
}

    
