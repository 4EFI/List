
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "list_ptr.h" 
#include "LOG.h" 

//-----------------------------------------------------------------------------

const char* FileListDumpName = "list_dump.html";
FILE* FileListDump = fopen( FileListDumpName, "w" );

//-----------------------------------------------------------------------------

//  List functions
//-----------------------------------------------------------------------------

int ListCtor( List* list, int size )
{
    if( list == NULL ) return 0;

    list->size = 0;

    list->poisonNode = ( ListNode* )calloc( 1 , sizeof( ListNode ) );
    poisonNode->prev = NULL;
    poisonNode->elem = ListPoison;
    poisonNode->next = NULL;

    list->head = NULL;
    lise->tail = NULL;

    return 1;
}

//-----------------------------------------------------------------------------

int ListDtor( List* list )
{
    if( list == NULL ) return 0;

    list->size = ListPoison;

    return 1;
}

//-----------------------------------------------------------------------------

int GraphVizListInfo( List* list, FILE* tempFile )
{
    if( list == NULL || tempFile == NULL ) return 0;
    
    fprintf( tempFile, "info[ shape = record, style = \"filled\", fillcolor = \"lightyellow\", "
                       "label = \" head = %d | tail = %d | size = %d \" ];\n",  
                        list->head, list->tail, list->size );

    return 1;
}

//-----------------------------------------------------------------------------

int GraphVizListNodeArr( List* list, FILE* tempFile )
{
    if( arr == NULL ) return 0;
    
    // Create null-poison node
    fprintf( tempFile, "node0[ shape = record, style = \"filled\", fillcolor = \"#FF7373\", "
                       "label = \"<p> prev = %p | <d> data[0]\\nPOISON | <n> next = %p\" ];\n", 
                        list.poisonNode.prev, list.poisonNode.next );
    
    int pos = list->head;
    for( int i = 0; i < list->size; i++ )
    {
        fprintf( tempFile, "node%d[ shape = record, style = \"filled\", fillcolor = \"%s\", " 
                           "label = \"<p> prev = %d | <d> data[%d] \\n %d | <n> next = %d\" ];\n", 
                            i, pos.prev == -1 ? "lightgreen" : "lightgrey", 
                               arr[i].prev, i, arr[i].elem, arr[i].next );

        pos = pos.next;
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
        if( arr[i].prev == -1 || arr[i].next == -1 ) continue;
        
        if( arr[i].prev != 0 )
        {
            fprintf( tempFile, "node%d -> node%d [ style = dashed, constraint = false ];", i, arr[i].prev );
        }
        if( arr[i].next != 0 )
        {
            fprintf( tempFile, "node%d -> node%d [ style = solid,  constraint = false ];", i, arr[i].next );
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

        GraphVizListNodeArr( list, tempDotFile );
        GraphVizListInfo   ( list, tempDotFile );
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

int ListPushBack( List* list, Elem_t val )
{
    if( list == NULL ) return 0;

    return ListInsert( list, TAIL, val );
}

//-----------------------------------------------------------------------------

ListNode* ListPopBack( List*  list, Elem_t val )
{
    if( list == NULL ) return 0;

    return ListInsert( list, HEAD.prev, val );
}

//-----------------------------------------------------------------------------

ListNode*
ListInsert( List*     list,  //!< This is a list 
            ListNode* pos,   //!< This is a pos
            Elem_t    val )  //!< This is a CRINGE
{
    if( list == NULL || pos == NULL || val == NULL ) return 0;

    ListNode* tempNode = ( ListNode* list )calloc( 1, sizeof( ListNode ) );

    // Set value
    tempNode->elem = val;

    tempNode->prev = pos;
    tempNode->next = pos->next;    

    pos->next->prev = tempNode;
    pos->next       = tempNode;

    list->size++;

    return tempNode;
}

//-----------------------------------------------------------------------------

int ListRemove( List* list, int pos )
{
    if( list == NULL ) return 0;

    size_t prevTemp = list->nodes[pos].prev;
    size_t nextTemp = list->nodes[pos].next;

    Elem_t elem = list->nodes[pos].elem;

    list->nodes[prevTemp].next = nextTemp;
    list->nodes[nextTemp].prev = prevTemp;

    list->nodes[pos].prev = -1;
    list->nodes[pos].elem = 0;
    list->nodes[pos].next = list->free;

    list->free = pos;
    list->size--;

    list->isSorted = false;

    return 1;
}

//-----------------------------------------------------------------------------

int ListLinearize( List* list )
{
    if( list == NULL ) return 0;

    ListNode* newNodes = ( ListNode* )calloc( list->capacity, sizeof( ListNode ) );

    int pos = ListHead( list );
    int i = 1;
    for( ; i <= list->size; i++ )
    {  
        newNodes[i].elem = list->nodes[pos].elem;
        newNodes[i].next = i + 1;
        newNodes[i].prev = i - 1;
                 
        pos = list->nodes[pos].next;
    }

    free( list->nodes );
    list->nodes    = newNodes; 
    
    TAIL = i - 1;
    HEAD = 1;

    list->nodes[TAIL].next = 0;
    list->nodes[HEAD].prev = 0;

    list->free = i;

    FillListNodeArr( list->nodes, list->free, list->capacity - 1 );

    list->isSorted = true;

    return 1;
}

//-----------------------------------------------------------------------------

int ListLogicalPosToPhysical( List* list, int desiredLogicalPos )
{
    if( list == NULL ) return 0;

    if( list->isSorted ) return desiredLogicalPos;
    
    int curPos = ListHead( list );

    for( int i = 1; ; i++ )
    {
        if( i      == desiredLogicalPos ) return curPos;
        if( curPos == ListTail( list )  ) return 0;
        
        curPos = list->nodes[curPos].next; 
    }

    return 0;
}

//-----------------------------------------------------------------------------

int ListFindElemByValue( List* list, Elem_t value )
{
    if( list == NULL ) return 0;

    int curPos = ListHead( list );

    while( true )
    {
        if( list->nodes[curPos].elem == value ) return curPos;
        
        if( curPos == ListTail( list ) ) return 0;

        curPos = list->nodes[curPos].next;  
    }

    return 0;
}

//  End List functions
//-----------------------------------------------------------------------------
