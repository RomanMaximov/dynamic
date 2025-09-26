#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "dynamic.h"
#include "string.h"
#include "setservice/intset.h"
#include "iterator.h"
#include "logerrors.h"
#include "test/testarraylist.h"
#include "test/testlinkedlist.h"
#include "test/testset.h"
#include "test/teststring.h"

int main()
{
    //testArrayList();
    //testLinkedList();
    testSet();
    //testString();

    return 0;
}
