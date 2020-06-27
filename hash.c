#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "hash.h"


struct Pair {
    const char * key; // Cadena
    void * value; // Puntero al valor
};

struct HashTable {
    Pair ** buckets; // Arreglo de punteros a Pair
    long count; // Cantidad de datos no nulos
    long size; // Tamaño del arreglo
    long current; // Variable para poder recorrer el arreglo
    long loadFactor; // Factor de carga del arreglo
};
int equalString(const char* key1,const char* key2){

    if(strcmp(key1,key2) == 0){
        return 1;
    }
    else return 0;
}

HashTable * createHashTable(long size) {
    HashTable  * tabla_hash = (HashTable *) malloc (sizeof(HashTable )*1);
    tabla_hash -> buckets = (Pair**) calloc (size,sizeof(Pair*));
    tabla_hash -> size = size;
    tabla_hash -> count = 0;
    tabla_hash -> current = -1;
    tabla_hash -> loadFactor = (size * 0.77);

    return tabla_hash;
}

Pair * createPair(const char* key , void* value ){

    Pair * new_value =(Pair *)  malloc(sizeof(Pair));
    new_value ->key = key;
    new_value ->value = value;
    return new_value;

}

unsigned long stringHash(const char * key) {
    unsigned long numero = 5381;
    int i;
    for(i = 0; i < strlen(key); i++){
        numero *= 33;
        numero += key[i];
    }
    return numero;
}

long linearProbing(HashTable * table, const char * key) {

    unsigned long hash = (stringHash(key) % table -> size);
    long i;

    for(i=hash ; i <= table -> size ; i++ ){

        if(i == table -> size) i=0;

        table -> current = i;

        if(table -> buckets[i] != NULL)
        {
            if(equalString(key , table->buckets[i] -> key ) == 1)//strcmp()
            {
                table -> current = i;
                return i;
            }

        }
        else
        {
            table -> current = i;
            return i;
        }

    }

    return hash;
}

void insertHashTable(HashTable * table, const char * key, void * value) {

    Pair* dato = createPair(key,value);

    long indice = linearProbing(table,key);
    if (table -> buckets[indice] == NULL || table -> buckets[indice] -> value == NULL){
        table -> buckets[indice] = dato;
        table -> count++;

    }

    if ((((table -> count +1) * 100) /table ->size) > table -> loadFactor ){
        enlarge(table);
    }
}

void * searchHashTable(HashTable * table, const char * key) {

        long indice = linearProbing(table,key);

        if(table -> buckets [indice] != NULL && table -> buckets [indice] -> value != NULL){
            table -> current = indice;
            return table -> buckets[indice] -> value;
        }
        else
        {
            return NULL;
        }
}

void * eraseKeyHashTable(HashTable * table, const char * key) {

    long indice = linearProbing(table,key);

    if(table -> buckets[indice] != NULL ){
        void * dato = table -> buckets[indice] -> value;
        table -> buckets[indice]->value = NULL;
        return dato;
    }
    else
    {
        return NULL;
    }

}

void enlarge(HashTable * table) {

    long size_viejo = table -> size ;
    Pair** auxiliar = table -> buckets;

    long i;
    HashTable* vector = createHashTable(size_viejo*2);

    table -> count = 0;
    table -> size = size_viejo *2;

    for(i = 0; i<size_viejo; i++){
        if(auxiliar[i] != NULL){

            insertHashTable(vector,auxiliar[i] -> key, auxiliar[i] -> value);

        }
    }
    free(table -> buckets);
    table -> buckets = vector->buckets;
    table -> loadFactor = (long)ceil(size_viejo * 0.77);

}

void * firstHashTable(HashTable * table) {
    long indice;
    for(indice = 0; indice <= table -> size-1; indice++){
        if(table -> buckets[indice] != NULL && table -> buckets[indice] -> value != NULL){

                table -> current = indice;
                return table -> buckets[indice] -> value;
        }
    }
    return NULL;

}

void * nextHashTable(HashTable * table) {
    long i;

    for(i = table -> current; i <= table -> size-1 ; i++){

        if(table -> buckets[i] != NULL && i != table -> current && table -> buckets[i] -> value != NULL){
                table -> current = i;
                return table -> buckets[i] -> value;
        }
    }
    return NULL;
}


void imprimirHash(HashTable* table){

    void * valor = firstHashTable(table);
    for(valor = firstHashTable(table); valor != NULL; valor = nextHashTable(table)){
        printf("%s\n",(char *) valor);
    }
}
