#include "trie.h"

void *my_alloc(int size)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
        memset(ptr,0,size);
    return ptr;
}

/* Function Name :  my_free
 * Description   :  free the pointer passed 
 * Return Value  :  nothing
 */
void my_free(void *void_ptr)
{
    free(void_ptr);
    return;
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

/* Function Name :  find_data
 * Description   :  find the data in the trie_id and key 
 *                  offset - initially called with 0, incremented
 *                  everytime.
 * Return Value  :  node ptr/NULL
 */

find_overlap(node *node_ptr, char *key, offset)
{
    int i = 0, j= 0, match_count = 0;
    
    if (node_ptr->key_size > strlen(key))
        return 0;
    else if(node_ptr->key_size == strlen(key))
    {
        if (0==strncpy(node_ptr->key,key,strlen(key)))
        {
            return strlen(key);
        }    
        return 0;
    }
    else
    {
        for (i = offset;i<key; i++,j++)
        {
            if (node_ptr->key[i] == key[j])
            {
                match_count++;
            }
            else
            {
                match_count = 0;
                break;
            }
        }
    }
    return match_count;
}


find_data(int trie_id,node *nxt_ptr, char *key, int offset)
{
    int key_size = strlen(key);
    int overlap_size = 0;
    char *temp; 

    if (node_ptr == NULL)
        return NULL;

    overlap_size = find_overlap (nxt_ptr, key, offset); 
  
    if (node_ptr->is_data_present)
    {
        if (overlap_size == key_size)
            return node_ptr; 
    }
    
    if (offset == strlen(key))
    {
        if (node_ptr->is_data_present)
        {
            printf("< returning node>\r\n");
            return node_ptr;
        }
        else
        {
            return NULL;
        }
    }
  
    int c=key[offset+overlap_size];   
    printf ("<%c > str:%s offset %d\r\n",c,str,offset);
    node *nxt_ptr = node_ptr->next_ptr[c];
    find_data(trie_id,nxt_ptr, key, offset+1+overlap_size);
}

