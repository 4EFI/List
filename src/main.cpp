
#include <stdio.h>
#include "list.h"

int main()
{
    List list = {0};
    ListCtor( &list, 10 );

    ListDump( &list, TypeListDump::GRAPH_VIZ );
}