
#include <stdio.h>
#include "list.h"

int main()
{
    List list = {0};
    ListCtor( &list, 10 );

    ListInsert( &list, ListTail( &list ), 300 );
    ListInsert( &list, ListTail( &list ), 500 );
    ListInsert( &list, ListTail( &list ), 700 );

    ListDump( &list, TypeListDump::GRAPH_VIZ, "graph", "png" ); 
}