#include "trie.h"

void main()
{
    create_trie(TRIE_ID);
    while(1)
    {
        printf ("Enter a word\n");
        scanf ("%s",word);
        printf ("Enter data to be inserted in %s -->\n",word);
        scanf ("%s",data);
        trie_insert(TRIE_ID,word,data);
        
    
    
    


    return 0;
}
