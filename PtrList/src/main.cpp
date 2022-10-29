
#include <stdio.h>
#include "list_ptr.h"
#include "LOG.h"

int main()
{
    List      list = {0};
    ListCtor( &list );

    int typeListDump = TypeListDump::GRAPH_VIZ; 

    ListNode* node1 = ListPushBack( &list, 15 );
    ListDump( &list, typeListDump, "PushBack( 15 )" ); 

    ListNode* node2 = ListPushBack( &list, 25 );
    ListDump( &list, typeListDump, "PushBack( 25 )" ); 

    ListRemove( &list, node );
    ListDump( &list, typeListDump, "ListRemove( %p )", node );

    ListNode* node3 = ListPushBack( &list, 50 );
    ListDump( &list, typeListDump, "PushBack( 50 )" );

    ListDtor( &list );
}