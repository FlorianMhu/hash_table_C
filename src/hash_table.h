#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_TABLE_INIT_SIZE 53

/*Prime number used for hashing*/
#define HT_PRIME_1 263
#define HT_PRIME_2 401

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

void ht_Insert(HT_HashTable * ht, const char * key, const char * value);

char * ht_Search(HT_HashTable * ht, const char * key);

int ht_Delete(HT_HashTable * ht, const char * key);

#endif //HASH_TABLE_H
