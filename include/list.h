#ifndef LIST_H
#define LIST_H

#include "config.h"

//-----------------------------------------------------------------------------

static const Elem_t ListPoison = 0x5E32DEAD;

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

    int size;
    ListNode* listNodes;   
};

int ListCtor( List* list, int size );

int PrepareListNodeArr( ListNode arr[], int size, int val );
int PrintListNodeArr  ( ListNode arr[], int size );

int ListDump( List* list );

int ListInsert( List* list, int pos, Elem_t val );
int ListMove  ( List* list, int pos );

//-----------------------------------------------------------------------------

#endif