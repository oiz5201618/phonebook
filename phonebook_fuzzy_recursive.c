#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define LD_NUMBER 2

entry *findName(char lastname[], entry *pHead)
{
    printf ("Levenshtein numver set:%d\n",LD_NUMBER);
    int kk1 = strlen(lastname) + LD_NUMBER;
    int kk2 = strlen(lastname) - LD_NUMBER;
    while (pHead != NULL) {
        if (strlen(pHead->lastName) < kk1 + 1) {
            if (strlen(pHead->lastName) > kk2 - 1) {
                int k = LD (lastname, strlen(lastname), pHead->lastName, strlen(pHead->lastName));
                if ( k < LD_NUMBER)
                    printf("Distance=%d,%s\n",k ,pHead->lastName);
            }
        }
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

int LD(char s[], int len_s, char t[], int len_t)
{
    int Last;

    /* base case: empty strings */
    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    /* test if last characters of the strings match */
    if (s[len_s-1] == t[len_t-1])
        Last = 0;
    else
        Last = 1;

    /* return minimum of delete char from s, delete char from t, and delete char from both */
    return MIN(MIN(LD(s, len_s - 1, t, len_t    ) + 1,
                   LD(s, len_s    , t, len_t - 1) + 1),
               LD(s, len_s - 1, t, len_t - 1) + Last);
}
