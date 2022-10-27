
#include <stdio.h>
#include <stdlib.h>
#include "list.h" 
#include "LOG.h" 

int ListResize( List* list ); 

//  List functions
//-----------------------------------------------------------------------------

int ListCtor( List* list, int size )
{
    if( list == NULL ) return 0;

    if(size <= 1) size = 2;

    list->coeffResize = 2;
    
    list->head = 0;
    list->tail = 0;
    list->free = 1;

    list->listNodes = ( ListNode* )calloc( size , sizeof( ListNode ) );

    if( list->listNodes != NULL ) list->size = size;
    else return -1;

    PrepareListNodeArr( list->listNodes, list->size, -1 );

    return 1;
}

//-----------------------------------------------------------------------------

int PrepareListNodeArr( ListNode arr['d'+'e'+'d'], int size, int val )
{
    if( arr == NULL ) return 0;

    0[arr].elem = ListPoison;
    0[arr].prev = 0;
    0[arr].next = 0;
    
    for( int i = 1; i < size; i++ )
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

int GraphVizListInfo( List* list, FILE* tempFile )
{
    if( list == NULL || tempFile == NULL ) return 0;
    
#define DEF_INFO( name, val ) \
    fprintf( tempFile, name"[shape = \"rectangle\",style = \"rounded\", label = \""name" = %d\"];\n", val );
    
    DEF_INFO( "head", list->head )
    DEF_INFO( "tail", list->tail )
    DEF_INFO( "free", list->free )

#undef DEF_INFO

    return 1;
}

//-----------------------------------------------------------------------------

int GraphVizListNodeArr( ListNode arr[], int size, FILE* tempFile )
{
    if( arr == NULL ) return 0;
    
    for( int i = 0; i < size; i++ )
    {
        fprintf( tempFile, "node%d [shape=record, label = \"<p%d> prev = %d | <d%d>data[%d] = %d | <n%d> next = %d\", ];\n", 
                 i, i, arr[i].prev, i, i, arr[i].elem, i, arr[i].next );
    }

    // Connect nodes
    for( int i = 1; i < size; i++ )
    {
        // Connect nodes empty edges 
        fprintf( tempFile, "node%d -> node%d [style=invis];", i - 1, i );

        if( arr[i].prev != -1 && arr[i].prev != 0 )
        {
            fprintf( tempFile, "node%d:<p%d> -> node%d:<d%d>", i, i, arr[i].prev, arr[i].prev );
        }

        if( arr[i].next != -1 && arr[i].next != 0 )
        {
            fprintf( tempFile, "node%d:<n%d> -> node%d:<d%d>", i, i, arr[i].next, arr[i].next );
        }
    }

    return 1;
}

//-----------------------------------------------------------------------------

int ListDump( List* list, int typeDump, char* fileName, char* fileType )
{
    if( list == NULL ) return 0;

    if/* */( typeDump == TypeListDump::CONSOLE )
    {
        PrintListNodeArr( list->listNodes, list->size );
    }
    else if( typeDump == TypeListDump::GRAPH_VIZ )
    {
        // Temp GraphViz file
        char tempFileName[] = "__GRAPH_VIZ_LIST_DUMP__.dot";
        FILE* tempFile = fopen( tempFileName, "w" );

  
        // Create temp GraphViz file
        fprintf( tempFile, "digraph ListDump\n" );
        fprintf( tempFile, "{\n" );
        {
            fprintf( tempFile, "rankdir = LR;\n" );
            
            GraphVizListNodeArr( list->listNodes, list->size, tempFile );
            GraphVizListInfo   ( list, /*                  */ tempFile );
        }
        fprintf( tempFile, "}\n" );


        char cmd[MaxStrLen] = "";
        sprintf( cmd, "dot %s -T %s -o %s.%s", tempFileName, fileType, fileName, fileType );

        // Create graph
        fclose( tempFile );
        system( cmd );

        // Delete temp file
        remove( tempFileName );
    }
    
    return 1;
}

//-----------------------------------------------------------------------------
//  Local function

int ListResize( List* list )
{
    if( list == NULL ) return 0;
    


    if( list->size == NULL )

    return 1;
}

//-----------------------------------------------------------------------------

int ListHead( List* list )
{
    if( list == NULL ) return 0;

    return list->head;
}

//-----------------------------------------------------------------------------

int ListTail( List* list )
{
    if( list == NULL ) return 0;

    return list->tail;
}

//-----------------------------------------------------------------------------

int ListInsert( List* list, int pos, Elem_t val )
{
    if( list == NULL ) return 0;

    list->listNodes[list->free].elem = val;

    list->listNodes[list->free].prev = pos - 1;
    list->listNodes[list->free].next = pos + 1;

    list->tail++;

    list->free++;

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
