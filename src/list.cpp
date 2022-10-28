
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "list.h" 
#include "LOG.h" 

//-----------------------------------------------------------------------------

const char* FileListDumpName = "list_dump.html";
FILE* FileListDump = fopen( FileListDumpName, "w" );

//-----------------------------------------------------------------------------

int ListResize     ( List* list ); 
int PushtToEmtyList( List* list, Elem_t val );

//  List functions
//-----------------------------------------------------------------------------

int ListCtor( List* list, int size )
{
    if( list == NULL ) return 0;

    if(size <= 1) size = 2;

    list->coeffResize = 2;
    list->size = 0;
    
    list->head = 0;
    list->tail = 0;
    list->free = 1;

    list->listNodes = ( ListNode* )calloc( size , sizeof( ListNode ) );

    if( list->listNodes != NULL ) list->capacity = size;
    else return -1;

    PrepareListNodeArr( list->listNodes, list->capacity, -1 );

    return 1;
}

//-----------------------------------------------------------------------------

int ListDtor( List* list )
{
    if( list == NULL ) return 0;

    list->coeffResize = ListPoison;
    
    list->head = ListPoison;
    list->tail = ListPoison;
    list->free = ListPoison;

    free( list->listNodes );
    list->listNodes = NULL;

    list->size = ListPoison;

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
    
#define DEF_INFO( name, val )                                                                          \
    fprintf( tempFile, name"[ shape = \"rectangle\", style = \"filled\", fillcolor = \"lightyellow\", " \
                             "label = \"" name" = %d\" ];\n", val );
    
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
    
    // Create null-poison node
    fprintf( tempFile, "node0[ shape = record, style = \"filled\", fillcolor = \"red\", "
                       "label = \"<p0> prev = 0 | <d0> data[0]\\nPOISON | <n0> next = 0\" ];\n" );
    
    for( int i = 1; i < size; i++ )
    {
        // Create node 
        fprintf( tempFile, "node%d[ shape = record, style = \"filled\", fillcolor = \"%s\", " 
                           "label = \"<p%d> prev = %d | <d%d>data[%d] \\n %d | <n%d> next = %d\" ];\n", 
                            i, arr[i].prev == -1 ? "lightgreen" : "lightgrey", 
                            i, arr[i].prev, i, i, arr[i].elem, i, arr[i].next );
    }

    
    // Connect nodes with invis edges
    fprintf( tempFile, "edge[ style = invis ]" ); // constraint = true
    for( int i = 1; i < size; i++ )
    {
        // Connect nodes empty edges 
        fprintf( tempFile, "node%d -> node%d;", i - 1, i );
    }


    // Connect prev/next to data 
    fprintf( tempFile, "edge[ style = solid ]" ); // constraint = false
    for( int i = 1; i < size; i++ )
    {
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

FILE* CreateListDumpDotFile( List* list, const char* fileName )
{
    if( fileName == NULL ) return NULL;
    
    FILE* tempDotFile = fopen( fileName, "w" );

    fprintf( tempDotFile, "digraph ListDump\n" );
    fprintf( tempDotFile, "{\n" );
    {
        fprintf( tempDotFile, "rankdir = LR;\n" );

        GraphVizListNodeArr( list->listNodes, list->capacity, tempDotFile );
        GraphVizListInfo   ( list, /*                      */ tempDotFile );
    }
    fprintf( tempDotFile, "}\n" );

    return tempDotFile;
}

//-----------------------------------------------------------------------------

int CreateGraphVizImg( const char* dotFileName, const char* fileName, const char* fileType )
{
    if(dotFileName == NULL || fileName == NULL || fileType == NULL) return 0; 

    char cmd[MaxStrLen] = "";

    sprintf( cmd, "dot %s -T %s -o %s", dotFileName, fileType, fileName );
    system(  cmd  );

    return 1;
}

//-----------------------------------------------------------------------------

int ListDump( List* list, int typeDump, const char* str, ... )
{
    if( list == NULL ) return 0;

    va_list   arg = {0};
    va_start( arg, str );

    if/* */( typeDump == TypeListDump::CONSOLE )
    {
        vfprintf( stdout, str, arg );
        PrintListNodeArr( list->listNodes, list->capacity );
    }
    else if( typeDump == TypeListDump::GRAPH_VIZ )
    {
        // Create dot file
        const char tempDotFileName[] = "graphVizTemp.dot";
        FILE*      tempDotFile = CreateListDumpDotFile( list, tempDotFileName );  
        fclose(    tempDotFile    );


        static int graphNum = 0;
        char       graphName[MaxStrLen] = "";
        sprintf(   graphName, "img/graph%d.png", graphNum++ );

        CreateGraphVizImg( tempDotFileName, graphName, "png" );


        // Delete temp file
        remove( tempDotFileName );

        // Create html file
         fprintf( FileListDump, "<pre>\n" );

         fprintf( FileListDump, "<font size = 5>" );
        vfprintf( FileListDump, str, arg );
         fprintf( FileListDump, "</font>\n\n" );

         fprintf( FileListDump, "<img src = \"%s\", style = \" max-width: 90vw \">\n", graphName );
         fprintf( FileListDump, "<hr>" );
    }

    va_end( arg );
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

int ListPushBack( List* list, Elem_t val )
{
    if( list == NULL ) return 0;
    
    return ListInsertAfter( list, ListTail( list ), val );;
}

//-----------------------------------------------------------------------------

int ListPopBack( List* list, Elem_t val )
{
    if( list == NULL ) return 0;
    
    return ListInsertAfter( list, ListHead( list ) - 1, val );
}   

//-----------------------------------------------------------------------------
// Local function 

int PushtToEmtyList( List* list, Elem_t val )
{
    if( list == NULL ) return 0;

    if( list->head && list->tail ) return 0;

    list->head = 1; list-> tail = 1;

    list->listNodes[1].prev = 0;
    list->listNodes[1].elem = val;
    list->listNodes[1].next = 0;

    list->size++; 

    list->free++;
    return 1;
}

//-----------------------------------------------------------------------------

int ListInsertAfter( List* list, int pos, Elem_t val )
{
    if( list == NULL ) return 0;

    if( list->free >= list->size ) ListResize( list );


    if( PushtToEmtyList( list, val ) ) return 1;

    //if( pos == list->listNodes[list]          ) list->head = list->free;
    if( pos == list->tail ) list->tail = list->free;
    
    // Set value
    list->listNodes[list->free].elem = val;

    list->listNodes[list->free].prev = pos;
    list->listNodes[list->free].next = list->listNodes[pos].next;

    list->listNodes[list->listNodes[pos].next].prev = list->free;
    list->listNodes[pos                      ].next = list->free;

    list->free++;
    return list->free - 1;
}

//-----------------------------------------------------------------------------

int ListMove( List* list, int pos )
{
    if( list == NULL ) return 0;

    return 1;
}

//  End List functions
//-----------------------------------------------------------------------------
