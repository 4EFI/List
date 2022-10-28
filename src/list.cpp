
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

    list->nodes = ( ListNode* )calloc( size , sizeof( ListNode ) );

    if( list->nodes != NULL ) list->capacity = size;
    else return -1;

    PrepareListNodeArr( list->nodes, list->capacity, -1 );

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

    free( list->nodes );
    list->nodes = NULL;

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
                           "label = \"<p> prev = %d | <d> data[%d] \\n %d | <n> next = %d\" ];\n", 
                            i, arr[i].prev == -1 ? "lightgreen" : "lightgrey", 
                               arr[i].prev, i, arr[i].elem, arr[i].next );
    }

    
    // Connect nodes with invis edges
    fprintf( tempFile, "edge[ style = invis ]" );
    for( int i = 1; i < size; i++ )
    {
        // Connect nodes empty edges 
        fprintf( tempFile, "node%d -> node%d [ style = invis ];", i - 1, i );
    }

    // Connect prev/next to data 
    fprintf( tempFile, "graph[ nodesep = 1, splines = ortho ];\n" );
    for( int i = 1; i < size; i++ )
    {
        if( arr[i].prev != -1 && arr[i].prev != 0 )
        {
            fprintf( tempFile, "node%d -> node%d [ style = solid ];", i, arr[i].prev );
        }

        if( arr[i].next != -1 && arr[i].next != 0 )
        {
            fprintf( tempFile, "node%d -> node%d [ style = dashed ];", i, arr[i].next );
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

        GraphVizListNodeArr( list->nodes, list->capacity, tempDotFile );
        GraphVizListInfo   ( list, /*                  */ tempDotFile );
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
        /*             */  fprintf( stdout, "%*sListDump%*s\n", 13, "", 13, "" );
        /*             */ vfprintf( stdout, str, arg );
        if( str != NULL )  fprintf( stdout, "\n" );

        PrintListNodeArr( list->nodes, list->capacity );
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
        /*            */  fprintf( FileListDump, "<pre>" );

        /*            */  fprintf( FileListDump, "<font size = 4>" );
        /*            */ vfprintf( FileListDump, str, arg );
        /*            */  fprintf( FileListDump, "</font>" );
        if( str != NULL ) fprintf( FileListDump, "\n\n" );

         fprintf( FileListDump, "<img src = \"%s\", style = \" max-width: 95vw \">", graphName );
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

    if( PushtToEmtyList( list, val ) ) return 1;
    
    int tempTail = list->tail;

    list->tail = list->free++;
    //list->free = list->nodes[list->tail].next;

    list->nodes[tempTail].next = list->tail;
    
    list->nodes[list->tail].prev = tempTail;
    list->nodes[list->tail].elem = val;
    list->nodes[list->tail].next = 0;

    list->size++;

    return list->tail;
}

//-----------------------------------------------------------------------------

int ListPopBack( List* list, Elem_t val )
{
    if( list == NULL ) return 0;
    
    if( PushtToEmtyList( list, val ) ) return 1;
    
    int tempHead = list->head;

    list->head = list->free++;
    //list->free = list->nodes[list->tail].next;

    list->nodes[tempHead].next = list->head;
    
    list->nodes[list->head].prev = 0;
    list->nodes[list->head].elem = val;
    list->nodes[list->head].next = tempHead;

    list->size++;
    
    return list->head;
}   

//-----------------------------------------------------------------------------
// Local function 

int PushtToEmtyList( List* list, Elem_t val )
{
    if( list == NULL ) return 0;

    if( list->head && list->tail ) return 0;

    list->head = 1; list-> tail = 1;

    list->nodes[1].prev = 0;
    list->nodes[1].elem = val;
    list->nodes[1].next = 0;

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

    //if( pos == list->nodes[list]          ) list->head = list->free;
    //if( pos == list->tail ) list->tail = list->free;
    
    // Set value
    list->nodes[list->free].elem = val;

    list->nodes[list->free].prev = pos;
    list->nodes[list->free].next = list->nodes[pos].next;

    list->nodes[list->nodes[pos].next].prev = list->free;
    list->nodes[pos                      ].next = list->free;

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
