#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt_hash.h"
#define KK 0

entry *findName(char lastname[], entry *pHead, entry table[])
{
    int hash = hashfunction(lastname);
    pHead = &table[hash];

    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

void append(char lastName[], entry table[])
{
    /* allocate memory for the new entry and put lastName */
    int hash = hashfunction(lastName);
	//printf("%d\n",hash);
	entry *n_entry = (entry *) malloc(sizeof(entry));
	n_entry->pNext = table[hash].pNext;
	table[hash].pNext = n_entry;
        strcpy(n_entry->lastName, lastName);

}

int hashfunction(char lastName[])
{
    unsigned int sum = 0;
    int i = 0;
    while (lastName[i] != '\0') {
        sum = sum*59 + lastName[i];
        i++;
    }

    sum = sum % HASH_NUMBER;
    return sum;
}

void hashtable_init(entry table[])
{
    int i = 0;
    for (; i<HASH_NUMBER ; i++) {
        table[i].pNext = NULL;
    }
}
