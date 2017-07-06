#include "trie.h"

void main()
{
    int i =0;

    char line[256];
    create_trie(TRIE_ID);
    char *word = NULL;
    char *data = NULL;
    while(i<3)
    {
        memset(line,0,sizeof(line));
        printf ("Enter a word\n");
        gets(line);
        word = (char *) my_alloc(strlen(line));
        strncpy(word,line,strlen(line));
        memset(line,0,sizeof(line));
        printf ("Enter data to be inserted in %s -->\n",word);
        gets(line);
        data = (char *) my_alloc(strlen(line));
        strncpy(data,line,strlen(line));
        trie_insert(TRIE_ID,word,data);
        i++;
        if (word)
            my_free(word);
        if (data)
            my_free(data);
    }
    printf("Going to print \r\n");
    print_node(find_head(TRIE_ID));
    printf("enter a word to search \r\n");
    memset(line,0,sizeof(line));
    gets(line);
    printf("The found data is %s \r\n",find_word(TRIE_ID,line,find_head(TRIE_ID),0));
    free_node(find_head(TRIE_ID));
    return;
}
