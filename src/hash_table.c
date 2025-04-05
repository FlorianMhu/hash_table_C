#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"

/*Global variable*/
static HT_Item HT_DELETED_ITEM = {NULL, NULL};

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

/**
 * @brief Hashing function
 * 
 * @param s 
 * @param a 
 * @param m 
 * @return int 
 */
static int ht_Hash(const char * s, const int a, const int m){
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++){
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

/**
 * @brief Compute double hashing of a given string in order to deal with collision and 
 * to have an even distribution of bucket index (which reduce clustering)
 * @param s String to be hashed
 * @param num_buckets Size of the hash table
 * @param attempt Number of collision occured 
 * @return int Hash value
 */
static int ht_GetHash(const char * s, const int num_buckets, const int attempt){
    const int hash_a = ht_Hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_Hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;   //1 is added to hash_b result to avoid case when hash_b is equel to 0
}

/**
 * @brief Insert a new key-value pair in the hash table.
 * If the key already exists in the hash table update its value with the given one.
 * @param ht Hash table
 * @param key Key
 * @param value Value
 */
void ht_Insert(HT_HashTable *ht, const char *key, const char *value){
    HT_Item * item = ht_NewItem(key, value);
    int index = ht_GetHash(item->key, ht->size, 0); /*Compute the hash of the key*/
    HT_Item * cur_item = ht->items[index];
    int i = 1;
    /*While the current bucket index given by the hash is not empty or not a dleted item compute a new hash*/
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM){
        /*If we found that the key is already existing, we update the item*/
        if(strcmp(cur_item->key, key) == 0){
            ht_DelItem(cur_item);
            ht->items[index] = item;
            return;
        }
        index = ht_GetHash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

/**
 * @brief Search the value of the given key in the Hash Table.
 * If the key is not found returns NULL
 * 
 * @param ht Hash table
 * @param key Key
 */
char * ht_Search(HT_HashTable *ht, const char *key){
    int index = ht_GetHash(key, ht->size, 0); /*Compute the hash of the key*/
    HT_Item * item = ht->items[index];
    int i = 1;
    /*While the current bucket index given by the hash is not empty compute a new hash*/
    while (item != NULL){
        /*Check whether the current item is deleted*/
        if(item != &HT_DELETED_ITEM){
            if(strcmp(item->key, key) == 0){ /*If the key at the current bucket index is the one we are searching for*/
                return item->value;
            }
        }
        index = ht_GetHash(item->key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

/**
 * @brief Delete key-value pair from the Hash table
 * To avoid breaking the collision chain this function delete a pair and then flag this index with a delted item
 * @param ht 
 * @param key 
 * @return int Return 1 if the key-value pair can be deleted, 0 otherwise
 */
int ht_Delete(HT_HashTable * ht, const char * key){
    int index = ht_GetHash(key, ht->size, 0);
    HT_Item * item = ht->items[index];
    int i = 1;
    /*While the current bucket index given by the hash is not empty compute a new hash*/
    while (item != NULL){
        /*Check whether the current item is deleted*/
        if(item != &HT_DELETED_ITEM){
            /*If the key at the current bucket index is the one we are searching for*/
            if(strcmp(item->key, key) == 0){
                /*We delete the item and put a deleted item at the same index to avoid braking the collision chain*/
                ht_DelItem(item);
                ht->items[index] = &HT_DELETED_ITEM;
                
                /*Decrease hash table count*/
                ht->count--;
                return 1;
            }
        }
        index = ht_GetHash(key, ht->size, i);
        i++;
    }
    return 0;
}


