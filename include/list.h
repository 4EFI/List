#ifndef LIST_H
#define LIST_H

#include "config.h"

//-----------------------------------------------------------------------------

static const int MaxStrLen = 255;

static const Elem_t ListPoison = 0x5E32DEAD;

//-----------------------------------------------------------------------------

enum TypeListDump
{
    GRAPH_VIZ, 
    CONSOLE
};

struct ListNode
{
    int    prev;
    Elem_t elem;
    int    next;
};

struct List
{  
    int coeffResize;
    
    int head;
    int tail;

    int size;
    ListNode* listNodes;   
};

int ListCtor( List* list, int size );

int PrepareListNodeArr ( ListNode arr[], int size, int val );
int PrintListNodeArr   ( ListNode arr[], int size );
int GraphVizListNodeArr( ListNode arr[], int size, char* fileType, char* fileName );

int ListDump( List* list, int typeDump = TypeListDump::CONSOLE );

// Get head/tail index
int ListHead( List* list );
int ListTail( List* list );

int ListInsert( List* list, int pos, Elem_t val );
int ListMove  ( List* list, int pos );

//-----------------------------------------------------------------------------

#endif