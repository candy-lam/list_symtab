#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtab.h"
#define nBuckets 51

typedef struct bucketT{
    int inUse; // This is 1 if the bucket is in use, or 0 otherwise
    char *key;
    void *value;
}bucketT;

struct symtabCDT {bucketT bucket[nBuckets]};

symtabADT EmptySymbolTable(void){
    symtabADT table;

    table = (symtabADT)malloc(sizeof(*table));
    for (int i = 0; i < nBuckets; i++){
        table->bucket[i].inUse = 0;
    }
    return (table);
}

int Hash(char *s, int n){
    unsigned long hashcode = 0UL;
    for (int i = 0; s[i] != '\0'; i++)
        hashcode = (hashcode << 6) + (unsigned long) s[i];
    return (int) (hashcode % n);
}

void Enter(symtabADT table, char *key, void *value){
    int hashCode = Hash(key, nBuckets);
    int i = 1;
    while (table->bucket[hashCode].inUse == 1){
        hashCode = (hashCode + i * i) % nBuckets;
        i++;
    }
    table->bucket[hashCode].inUse = 1;
    table->bucket[hashCode].key = key;
    table->bucket[hashCode].value = value;
}

void *Lookup(symtabADT table, char *key){
    int hashCode = Hash(key, nBuckets);
    int i = 1;
    while ((strcmp(table->bucket[hashCode].key, key)) != 0){
        hashCode = (hashCode + i * i) % nBuckets;
        i++;
    }
    return (table->bucket[hashCode].value);

}

void forEachEntryDo (symtabFnT f, symtabADT table){
    for (int i; i < nBuckets; i++){
        if (table->bucket[i].inUse == 1)
            f(table->bucket[i].key, table->bucket[i].value);
    }
}
