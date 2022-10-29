
#include <stdio.h>
#include "list.h"
#include "LOG.h"

int main()
{
    List      list = {0};
    ListCtor( &list, 5 );

    int typeListDump = TypeListDump::GRAPH_VIZ; 

    ListDump( &list, typeListDump, ">>> Ded outside: %d", 32 ); 
    ListPushBack( &list, 15 );

    ListDump( &list, typeListDump );
    ListPushBack( &list, 25 );

    ListDump( &list, typeListDump );
    ListRemove( &list, 1 );
    ListDump( &list, typeListDump ); 
    ListInsert( &list, 2, 50 );

    ListDump( &list, typeListDump );
    ListInsert( &list, 1, 100 );
    ListDump( &list, typeListDump );

    ListInsert( &list, 1, 300 );

    ListDump( &list, typeListDump );

    //ListLinearize( &list, list.capacity );
    //ListDump( &list, typeListDump );

    ListDtor( &list );
}