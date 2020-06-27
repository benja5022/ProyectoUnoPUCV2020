#ifndef hash_H_INCLUDED
#define hash_H_INCLUDED

typedef struct Pair Pair;

typedef struct HashTable HashTable;

HashTable * createHashTable(long size);

unsigned long stringHash(const char * key);

Pair * createPair(const char* key , void* value );

int equalString(const char* key1,const char* key2);

long linearProbing(HashTable * table, const char * key);

void insertHashTable(HashTable * table, const char * key, void * value);

void * searchHashTable(HashTable * table, const char * key);

void * eraseKeyHashTable(HashTable * table, const char * key);

void enlarge(HashTable * table);

void * firstHashTable(HashTable * table);

void * nextHashTable(HashTable * table);

void imprimirHash(HashTable* table);

#endif // HASH_H_INCLUDED
