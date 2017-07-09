#include "trie.h"

void main()
{
    int i =0;

    char line[256];
    trie_init_globals();
    trie_init(TRIE_ID);
    char *key = NULL;
    char *data = NULL;
    int key_size =0;
    int data_size =0;
    while(i<3)
    {
        memset(line,0,sizeof(line));
        printf ("Enter a key\n");
        gets(line);
        key = (char *) my_alloc(strlen(line));
        strncpy(key,line,strlen(line));
        key_size=strlen(line);
        memset(line,0,sizeof(line));
        printf ("Enter data to be inserted in %s -->\n",key);
        gets(line);
        data = (char *) my_alloc(strlen(line));
        strncpy(data,line,strlen(line));
        data_size= strlen(line);
        trie_insert_data_into_key(TRIE_ID, key, key_size, data, data_size);
        i++;
        if (key)
            my_free(key);
        if (data)
            my_free(data);
    }
    print_node(find_head(TRIE_ID));
    printf("Going to print \r\n");
    print_node(find_head(TRIE_ID));
    printf("enter a key to search \r\n");
    memset(line,0,sizeof(line));
    gets(line);
    node *tnode = (node *)find_data_from_id(TRIE_ID,line);
    memset(line,0,sizeof(line));
    memcpy(line,tnode->data,tnode->data_size);
    printf("The found data is %s  size %d \r\n",line,tnode->data_size);
    trie_deinit(TRIE_ID);
    trie_deinit_globals();
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
/* Function Name  :  trie_insert_data_into_key
 * Description    :  Insert data(read size from data)
 *                   into the key in the TRIE with id trie_id
 * Return Value   :  OSIX_SUCCESS
 */
void trie_insert_data_into_key(int trie_id, char *key, int key_size, void *data, int data_size)
{
    node *head = find_head(trie_id);
    rec_trie_insert(head, key, key_size, data,data_size);
    return OSIX_SUCCESS;    
}

void
insert_key(node *node_ptr, char *key, int key_size)
{
    if (node_ptr->key == NULL)
    {
        node_ptr->key_size = key_size;
        node_ptr->key = malloc(key_size);
        memcpy(node_ptr->key,key,key_size);
    }
    else
    {
        create_node(node_ptr,key[0]);
        node *nxt_ptr = get_next_ptr(node_ptr,key[0]);
        insert_key(nxt_ptr, key+1 ,key_size-1);        
    }
    return;
}

void 
insert_data_in_node(node *node_ptr, void *data, int data_size)
{   
    node_ptr->data_size= data_size;
    node_ptr->data = malloc(data_size);
    memcpy(node_ptr->data,data,data_size);
    node_ptr->is_data_present = true;
    return;
}

void
insert_key_and_data(node *node_ptr, char *key, int key_size, void *data, int data_size)
{
    if (false == node_ptr->is_data_present)
    {
        insert_key(node_ptr,key,key_size);
        insert_data_in_node(node_ptr,data,data_size);
    }
}

void
rec_trie_insert(node *node_ptr, char *key, int key_size, void *data, int data_size, int offset)
{
    printf ("<%s:%d> key:%s data:%s offset:%d \r\n",__func__,__LINE__,key,data,offset);
    char *temp_key;
    node *nxt_ptr;
    int overlap_count = 0;
    if ((node_ptr->is_data_present == false) && (node_ptr->key == NULL))
    {   
        insert_key_and_data(node_ptr,key,key_size,data,data_size);
    }
    else
    {
        overlap_count = find_overlap(node_ptr,key,offset);
        if (overlap_count == 0)
        {
            create_node(node_ptr,key[offset]);
            nxt_ptr = get_next_ptr(node_ptr,key[offset]);
            temp_key = key+overlap_count;
            rec_trie_insert(nxt_ptr,key,key_size,data,data_size,offset);
        }
        else
        {
            reorg_data(node_ptr,overlap_count);
            create_node(node_ptr,key[overlap_count]);
            node *nxt_ptr = get_next_ptr(node_ptr, key[overlap_count]);
            insert_key(nxt_ptr, key+overlap_count, key_size-overlap_count);
            rec_trie_insert(nxt_ptr, key+overlap_count, key_size-overlap_count, data, data_size, offset+overlap_count);
        }
    }
}

void
reorg_data(node *node_ptr, int overlap_count)
{
    printf ("<%s> key:%s data %s overlap:%d \r\n",__func__,node_ptr->key,node_ptr->data,overlap_count);
    char *temp_key;
    int temp_key_size;
    char *temp_data;
    int temp_data_size;
    char *rem_key;

    temp_key_size = node_ptr->key_size;
    temp_key =(char *) malloc(temp_key_size);
    memcpy(temp_key,node_ptr->key,temp_key_size);
   
    temp_data_size = node_ptr->data_size;
    temp_data =(char *) malloc(temp_data_size);
    memcpy(temp_data,node_ptr->data,temp_data_size);

    my_free(node_ptr->key);
    node_ptr->key_size = overlap_count;
    memcpy(node_ptr->key,temp_key,overlap_count);

    rem_key = malloc(temp_key_size-overlap_count);
    memcpy(rem_key,temp_key+overlap_count,temp_key_size-overlap_count);    

    my_free(node_ptr->data);
    node_ptr->data_size = 0;
    node_ptr->is_data_present = false;

    rec_trie_insert(node_ptr,rem_key,temp_key_size-overlap_count,temp_data,temp_data_size, overlap_count);
    return;
}
    
/* Function Name   : print_node
 * Description     : print the contents
 */
void print_node(node *curr_node)
{
    char tptr[256];
    int i = 0;
    
    if (curr_node == NULL)
    {
        printf ("<null>\r\n");
            return;
    }
    if (curr_node->is_data_present)
    {
        memset(tptr,0,256);
        memcpy(tptr,curr_node->data,curr_node->data_size);
        printf ("<char: %s> <data:%s>\r\n",curr_node->key,curr_node->data);
    }
    else
    {
        printf ("no data \r\n");
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
    curr_node->data_size =size;
    memcpy(curr_node->data,data,size);
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

int find_overlap(node *node_ptr, char *key, int offset)
{
    int i = 0, j= 0, match_count = 0;

    if (node_ptr == NULL)
        return 0;

    if (node_ptr->key == NULL)
        return 0;
    
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
        for (i = offset;i<strlen(key); i++,j++)
        {
            char *key2 =(char *) node_ptr->key;
            if (0==memcmp(key2,key,1))
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
    printf ("<%s:%d> finding overlap between %s and %s: match:%d \r\n",__func__,__LINE__,(char *)node_ptr->data,key,match_count); 
    return match_count;
}


node *find_data(int trie_id,node *node_ptr, char *key, int offset)
{
    int key_size = strlen(key);
    int overlap_size = 0;
    char *temp; 

    if (node_ptr == NULL)
        return NULL;

    overlap_size = find_overlap (node_ptr, key, offset); 
  
    if (node_ptr->is_data_present)
    {
        if (overlap_size == key_size)
            return node_ptr; 
    }
    
    if (offset == strlen(key))
    {
        if (node_ptr->is_data_present)
        {
            return node_ptr;
        }
        else
        {
            return NULL;
        }
    }
 
    node *nxt_ptr= get_next_ptr(node_ptr,key[offset+overlap_size]); 
    return(find_data(trie_id,nxt_ptr, key, offset+1+overlap_size));
}

