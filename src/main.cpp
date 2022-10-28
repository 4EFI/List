
#include <stdio.h>
#include "list.h"

int main()
{
    List      list = {0};
    ListCtor( &list, 10 );

    int typeListDump = TypeListDump::GRAPH_VIZ; 

    ListDump( &list, typeListDump, "Ded outside: %d", 32 ); 
    ListInsertAfter( &list, 0, 30 );

    ListDump( &list, typeListDump );
    ListInsertAfter( &list, 1, 40 );

    ListDump( &list, typeListDump ); 
    ListInsertAfter( &list, 2, 50 );

    ListDump( &list, typeListDump );
    ListInsertAfter( &list, 1, 100 );
    ListDump( &list, typeListDump );

    ListInsertAfter( &list, 1, 300 );

    ListDump( &list, typeListDump );

    ListDtor( &list );
}