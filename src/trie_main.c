#include "trie.h"

void main()
{
    int i =0;

    char line[256];
    trie_init(TRIE_ID);
    char *key = NULL;
    char *data = NULL;
    while(i<3)
    {
        memset(line,0,sizeof(line));
        printf ("Enter a key\n");
        gets(line);
        key = (char *) my_alloc(strlen(line));
        strncpy(key,line,strlen(line));
        memset(line,0,sizeof(line));
        printf ("Enter data to be inserted in %s -->\n",key);
        gets(line);
        data = (char *) my_alloc(strlen(line));
        strncpy(data,line,strlen(line));
        printf ("strlen line %d sizeof(data) %d \r\n",strlen(line),sizeof(data));
        trie_insert_data_into_key(TRIE_ID,key,data,strlen(line));
        i++;
        if (key)
            my_free(key);
        if (data)
            my_free(data);
    }
    printf("Going to print \r\n");
    print_node(find_head(TRIE_ID));
    printf("enter a key to search \r\n");
    memset(line,0,sizeof(line));
    gets(line);
    node *tnode = find_data_from_id(TRIE_ID,line);
    memset(line,0,sizeof(line));
    memcpy(line,tnode->data,tnode->size);
    printf("The found data is %s  size %d \r\n",line,tnode->size);
    free_node_id(TRIE_ID);
    return;
}
