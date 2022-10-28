
#include <stdio.h>
#include "list.h"

int main()
{
    List list = {0};
    ListCtor( &list, 10 );

    /*
    ListInsert( &list, ListTail( &list ), 300 );
    ListInsert( &list, ListTail( &list ), 500 );
    ListInsert( &list, ListTail( &list ), 700 );
    */

    ListDump( &list, TypeListDump::GRAPH_VIZ ); 
    ListInsertAfter( &list, 0, 30 );

    ListDump( &list, TypeListDump::GRAPH_VIZ );
    ListInsertAfter( &list, 1, 40 );

    ListDump( &list, TypeListDump::GRAPH_VIZ ); 
    ListInsertAfter( &list, 2, 50 );

    ListDump( &list, TypeListDump::GRAPH_VIZ );
    ListInsertAfter( &list, 1, 100 );
    ListDump( &list, TypeListDump::GRAPH_VIZ );

    ListInsertAfter( &list, 1, 300 );

    ListDump( &list, TypeListDump::GRAPH_VIZ );

    ListDtor( &list );
}