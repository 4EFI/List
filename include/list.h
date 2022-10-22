#ifndef LIST_H
#define LIST_H

#include "config.h"

//-----------------------------------------------------------------------------

struct ListNode
{
    int    prev;
    Elem_t elem;
    int    next;
};

struct List
{  
    int head;
    int tail;
    ListNode* listNodes;   
};

int ListCtor( List* list, int size );

int ListInsert( List* list, int pos, Elem_t val );
int ListMove  ( List* list, int pos );

//-----------------------------------------------------------------------------

#endif