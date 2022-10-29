#ifndef LIST_H
#define LIST_H

#include "config.h"

//-----------------------------------------------------------------------------

static const int MaxStrLen = 255;

static const Elem_t ListPoison = 0x5E32DEAD;

extern const char* FileListDumpName;
extern FILE* FileListDump;

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
    int free;

    bool isSorted;

    int capacity;
    ListNode* nodes;   

    int size;
};

int ListCtor( List* list, int size );
int ListDtor( List* list );

int PrepareListNodeArr ( ListNode arr[], int size, int val );
int PrintListNodeArr   ( ListNode arr[], int size );

int GraphVizListNodeArr( ListNode arr[], int size, FILE* tempFile );
int GraphVizListInfo   ( List* list, /*         */ FILE* tempFile );

FILE* CreateListDumpDotFile( List* list, const char* fileName );

int ListDump( List* list, int typeDump, const char* str = NULL, ... );

// Get head/tail index
int ListHead( List* list );
int ListTail( List* list );

int ListPushBack( List* list, Elem_t val );
int ListPopBack ( List* list, Elem_t val );

int ListInsert( List* list, int pos, Elem_t val );

Elem_t ListMove( List* list, int pos );

int ListLogicalPosToPhysical( List* list, int    desiredLogicalPos );
int ListFindElemByValue     ( List* list, Elem_t value );

int ListLinearize( List* list );

//-----------------------------------------------------------------------------

int CreateGraphVizImg( const char* dotFileName, const char* fileName, const char* fileType );

//-----------------------------------------------------------------------------

#endif