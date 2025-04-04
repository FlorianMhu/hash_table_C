#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_TABLE_INIT_SIZE 53

//Item struct
typedef struct{
    char * key;
    char * value;
}HT_Item;


//Hash table struct
typedef struct{
    int size;
    int count;
    HT_Item ** items;
}HT_HashTable;

HT_HashTable *ht_New(void);

void ht_DelHashTable(HT_HashTable *ht);

#endif //HASH_TABLE_H
