#include "trie.h"

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}


void main()
{
    int i =0;

    char word[256];
    char data[256];
    create_trie(TRIE_ID);

    while(i<3)
    {
        memset(word,0,sizeof(word));
        memset(data,0,sizeof(data));
        printf ("Enter a word\n");
        scanf ("%s",word);
        printf ("Enter data to be inserted in %s -->\n",word);
        scanf ("%s",data);
        trie_insert(TRIE_ID,word,data);
        i++;
    }
    printf("Going to print \r\n");
    print_node(find_head(TRIE_ID));
    return;
}
