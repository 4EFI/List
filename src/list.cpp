
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

    if( list->listNodes != NULL ) list->size = size;

    PrepareListNodeArr( list->listNodes, list->size, -1 );

    return 1;
}

//-----------------------------------------------------------------------------

int PrepareListNodeArr( ListNode arr['d'+'e'+'d'], int size, int val )
{
    if( arr == NULL ) return 0;

    0[arr].elem = ListPoison;
    
    for( int i = 0; i < size; i++ )
    {
        i[arr].prev = val;
        i[arr].next = val; 
    }

    return 1;
}

//-----------------------------------------------------------------------------

int PrintListNodeArr( ListNode arr[], int size )
{
    if( arr == NULL ) return 0;

    printf( "              ListDump             \n" );
    printf( "+-----+-------------+------+------+\n" );
    printf( "|   i |     element | next | prev |\n" );
    printf( "+-----+-------------+------+------+\n" );

    for( int i = 0; i < size; i++ )
    {
        printf( "| %3d | %11d | %4d | %4d |\n", i, arr[i].elem, arr[i].next, arr[i].prev );    
    }

    printf( "+-----+-------------+------+------+\n" );

    return 1;  
}

//-----------------------------------------------------------------------------

int ListDump( List* list )
{
    if( list == NULL ) return 0;

    PrintListNodeArr( list->listNodes, list->size );
    
    return 1;
}

//-----------------------------------------------------------------------------

int ListInsert( List* list, int pos, Elem_t val )
{
    if( list == NULL ) return 0;

    return 1;
}

//-----------------------------------------------------------------------------

int ListMove( List* list, int pos )
{
    if( list == NULL ) return 0;

    return 1;
}

//  End List functions
//-----------------------------------------------------------------------------
