
#include <stdio.h>
#include <stdlib.h>
#include "list.h" 

//  List functions
//-----------------------------------------------------------------------------

int ListCtor( List* list, int size )
{
    if( list == NULL ) return  0;

    if(size <= 0) size = 1;
    
    list->head = 0;
    list->tail = 0;

    list->listNodes = ( ListNode* )calloc( size , sizeof( ListNode ) );

    return 1;
}

//-----------------------------------------------------------------------------

int ListInsert( List* list, int pos, Elem_t val )
{

}

//-----------------------------------------------------------------------------

int ListMove( List* list, int pos )
{
    
}

//-----------------------------------------------------------------------------
