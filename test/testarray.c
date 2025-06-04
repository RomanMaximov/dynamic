#include <stdio.h>
#include "../dynamic.h"
#include "testarray.h"


// funcs prototypes
void assertInt(int, int);
void assertNotNull(void*);

void testArrayList() {

    puts("=========== test IntArrayList ===========");
    IntList intList = newList(intList, NULL);
    assertNotNull((void*) intList);
    intList->delete(&intList);
    if (intList == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    int temp[] = {23, 67, 55, 4};
    IntList intList2 = listOfArr(intList2, temp, 4);
    printf("Collection size, ");
    assertInt(intList2->size(intList2), 4);
    intList2->delete(&intList2);
    puts("");

    printf("Create collection as listOf\n");
    IntList intList3 = listOf(intList3, 4, 23, 67, 55, 4);
    intList3->print(intList3);
    IntList addList = listOf(addList, 4, 11, 12, 13, 14);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 4);

    printf("Get element by index[2]\n");
    int num = intList3->get(intList3, 2);
    assertInt(num, 55);

    printf("Add all from list2\n");
    intList3->addAll(intList3, addList->values);
    intList3->print(intList3);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 8);
    printf("Get element by index[7]\n");
    num = intList3->get(intList3, 7);
    intList3->print(intList3);
    assertInt(num, 14);
    addList->delete(&addList);

    IntList addList2 = listOf(addList, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    printf("Add all from list3\n");
    intList3->addAll(intList3, addList2->values);
    intList3->print(intList3);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 28);
    printf("Get element by index[27]\n");
    num = intList3->get(intList3, 27);
    assertInt(num, 20);
    addList2->delete(&addList2);

    printf("Set element by index[25] by 777\n");
    intList3->set(intList3, 25, 777);
    num = intList3->get(intList3, 25);
    assertInt(num, 777);
    intList3->print(intList3);

    printf("Index of element with value 777\n");
    int index = intList3->indexOf(intList3, 777);
    assertInt(index, 25);

    printf("Sort collection\n");
    intList3->sort(intList3);
    intList3->print(intList3);
    printf("Get element by index[1] after sort\n");
    num = intList3->get(intList3, 1);
    assertInt(num, 2);

    printf("Reverse sort collection\n");
    intList3->sortReverse(intList3);
    intList3->print(intList3);
    printf("Get element by index[1] after reverse sort\n");
    num = intList3->get(intList3, 1);
    assertInt(num, 67);

    printf("Clear collection\n");
    intList3->clear(intList3);
    intList3->print(intList3);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 0);

    printf("Empty collection\n");
    bool isEmpty = intList3->isEmpty(intList3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    IntList addList3 = listOf(addList, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    intList3->addAll(intList3, addList3->values);
    intList3->print(intList3);
    addList3->delete(&addList3);
    printf("Collection contains value 10\n");
    bool isContains = intList3->contains(intList3, 10);
    if (isContains)
        assertInt(1, 1);

    IntList containsList = listOf(containsList, 5, 10,11,12,13,14);
    printf("Collection contains all from list5\n");
    containsList->print(containsList);
    isContains = intList3->containsAll(intList3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsList->print(containsList);
    isContains = intList3->containsAny(intList3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem by index[8] from collection\n");
    intList3->removeElem(intList3, 8);
    intList3->print(intList3);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 19);
    printf("Get element by index[8] after reverse sort\n");
    num = intList3->get(intList3, 8);
    assertInt(num, 10);

    printf("Remove all from list5\n");
    containsList->print(containsList);
    intList3->removeAll(intList3, containsList->values);
    printf("Collection size, ");
    intList3->print(intList3);
    assertInt(intList3->size(intList3), 14);
    containsList->delete(&containsList);


    printf("Subtract from collection\n");
    IntList subtractList = listOf(subtractList, 5, 15,16,17,18,19);
    IntList subtract = intList3->subtract(intList3, subtractList->values);
    printf("new subtract collection: ");
    subtract->print(subtract);
    assertInt(1, 1);
    subtractList->delete(&subtractList);
    subtract->delete(&subtract);

    printf("reverse collection\n");
    intList3->reverse(intList3);
    intList3->print(intList3);
    printf("Get element by index[0] after reverse\n");
    num = intList3->get(intList3, 0);
    assertInt(num, 20);

    printf("Collection equals list6\n");
    IntList intList4 = listOf(intList4, 14, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 18, 19, 20);
    printf("Collection after reverse\n");
    intList3->reverse(intList3);
    intList3->print(intList3);
    bool isEquals = intList3->isEquals(intList3, intList4);
    if (isEquals) {
        printf("collection is equals list6, ");
        assertInt(1, 1);
    }
    intList4->delete(&intList4);

    printf("Collection to string\n");
    string strList3 = intList3->toString(intList3);
    strList3->print(strList3);
    assertInt(1, 1);
    intList3->delete(&intList3);
    strList3->delete(&strList3);
}

void assertInt(int result, int expected ) {
    if (result == expected) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %d, but result: %d\n", expected, result);
        puts("");
    }
}

void assertNotNull(void* source) {
    if (source != NULL) {
        printf("Collection non null, test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %s, but result: %s\n", "not NULL", "NULL");
    }
}


