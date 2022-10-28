
#include <stdio.h>
#include "list.h"
#include "LOG.h"

int main()
{
    List      list = {0};
    ListCtor( &list, 10 );

    int typeListDump = TypeListDump::GRAPH_VIZ; 

    ListDump( &list, typeListDump, ">>> Ded outside: %d", 32 ); 
    ListPopBack( &list, 17 );
    //ListPushBack( &list, 15 );
    //ListInsertAfter( &list, 0, 30 );

    ListDump( &list, typeListDump );
    ListPopBack( &list, 27 );
    //ListPushBack( &list, 25 );
    //ListInsertAfter( &list, 1, 40 );

    LOG( "%d", ListLogicalPosToPhysical( &list, 1 ) );

    ListDump( &list, typeListDump ); 
    ListInsertAfter( &list, 2, 50 );

    ListDump( &list, typeListDump );
    ListInsertAfter( &list, 1, 100 );
    ListDump( &list, typeListDump );

    ListInsertAfter( &list, 1, 300 );

    ListDump( &list, typeListDump );

    ListDtor( &list );
}