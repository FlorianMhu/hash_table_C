#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

/**
 * @brief Create an item for the hash table with the given key and value.
 * This function allocate the memory for a new key - value pair.
 * @param k Key
 * @param v Value
 * @return HT_item* allocated item with key - value pair
 */
static HT_Item * ht_NewItem(const char * k, const char * v){
    HT_Item* i = malloc(sizeof(HT_Item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

HT_HashTable * ht_New(void){
    HT_HashTable * ht = malloc(sizeof(HT_HashTable));
    ht->size = HASH_TABLE_INIT_SIZE;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(HT_Item*)); //Allocate items memory with NULL
    return ht;
}

static void ht_DelItem(HT_Item * i){
    free(i->key);
    free(i->value);
    free(i);
}

void ht_DelHashTable(HT_HashTable *ht){
    //Free memory for each items
    for(int i = 0; i < ht->size; i++){
        HT_Item * item = ht->items[i];
        if(item != NULL){
            ht_DelItem(item);
        }
    }
    //Free Hash table
    free(ht->items);
    free(ht);
}
