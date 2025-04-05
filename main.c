#include "hash_table.h"
#include <stdio.h>

int main(){
    HT_HashTable * ht = ht_New();
    printf("Base size: %d\tSize: %d\n", ht->base_size, ht->size);
    ht_Insert(ht, "one", "45");
    ht_Insert(ht, "two", "789");
    printf("item 2 val: %s", ht_Search(ht, "two"));
    ht_Delete(ht, "two");
    ht_DelHashTable(ht);
    return 0;
}
