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

	if (table[hash].pNext == NULL) {
		strcpy(table[hash].lastName, lastName);
	}else {
		entry *link;
		link = table[hash].pNext;
		while (link != NULL) {
			link = link->pNext;
		}
		link = (entry *) malloc(sizeof(entry));
		strcpy(link->lastName, lastName);
	}
}

int hashfunction(char lastName[])
{
        int sum = 0;
        int i = 0;
        while (lastName[i] != '\0') {
                sum = sum + lastName[i];
                i++;
        }

        sum = sum % HASH_NUMBER;
        return sum;
}

void hashtable_init(entry table[])
{
	int i = 0;
	for (i; i<HASH_NUMBER ; i++) {
		table[i].pNext = NULL;
	}
}
