#ifndef SYMTAB_H
#define SYMTAB_H

typedef struct symtabCDT *symtabADT;
typedef void (*symtabFnT) (char*, void*);

symtabADT EmptySymbolTable(void);
void Enter(symtabADT table, char *key, void *value);
void *Lookup(symtabADT table, char *key);
void forEachEntryDo(symtabFnT, symtabADT);

#endif
