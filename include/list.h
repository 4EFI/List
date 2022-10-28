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

    int capacity;
    ListNode* listNodes;   

    int size;
};

int ListCtor( List* list, int size );
int ListDtor( List* list );

int PrepareListNodeArr ( ListNode arr[], int size, int val );
int PrintListNodeArr   ( ListNode arr[], int size );

int GraphVizListNodeArr( ListNode arr[], int size, FILE* tempFile );
int GraphVizListInfo   ( List* list, /*         */ FILE* tempFile );

FILE* CreateListDumpDotFile( List* list, const char* fileName );

int ListDump( List* list, int typeDump, const char* str = "", ... );

// Get head/tail index
int ListHead( List* list );
int ListTail( List* list );

int ListPushBack( List* list, Elem_t val );
int ListPopBack ( List* list, Elem_t val );

int ListInsertAfter ( List* list, int pos, Elem_t val );
int ListInsertBefore( List* list, int pos, Elem_t val );
int ListMove        ( List* list, int pos );

//-----------------------------------------------------------------------------

int CreateGraphVizImg( const char* dotFileName, const char* fileName, const char* fileType );

//-----------------------------------------------------------------------------

#endif