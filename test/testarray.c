#include <stdio.h>
#include "../dynamic.h"
#include "testarray.h"


// funcs prototypes
static void assertInt(int, int);
static void assertDouble(double, double);
static void assertStr(string , string);
static void assertChar(char, char);
static void assertNotNull(void*);
static void testIntList();
static void testDoubleList();

void testArrayList() {

    testIntList();
    testDoubleList();
}

static void assertInt(int result, int expected ) {
    if (result == expected) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %d, but result: %d\n", expected, result);
        puts("");
    }
}

static void assertDouble(double result, double expected) {
    if (result == expected) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %lf, but result: %lf\n", expected, result);
        puts("");
    }
}

static void assertNotNull(void* source) {
    if (source != NULL) {
        printf("Collection non null, test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %s, but result: %s\n", "not NULL", "NULL");
    }
}

static void testIntList() {
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

static void testDoubleList() {
    puts("=========== test DoubleArrayList ===========");
    DoubleList doubleList = newList(doubleList, NULL);
    assertNotNull((void*) doubleList);
    doubleList->delete(&doubleList);
    if (doubleList == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    double temp[] = {23.55, 67.037, 55.999, 4.37};
    DoubleList doubleList2 = listOfArr(doubleList2, temp, 4);
    printf("Collection size, ");
    assertInt(doubleList2->size(doubleList2), 4);
    doubleList2->delete(&doubleList2);
    puts("");

    printf("Create collection as listOf\n");
    DoubleList doubleList3 = listOf(doubleList3, 4, 23.55, 67.037, 55.999, 4.37);
    doubleList3->print(doubleList3);
    DoubleList addDoubleList = listOf(addDoubleList, 4, 11.01, 12.01, 13.01, 14.01);
    printf("Collection size, ");
    assertInt(doubleList3->size(doubleList3), 4);

    printf("Get element by index[2]\n");
    double num = doubleList3->get(doubleList3, 2);
    assertDouble(num, 55.999);

    printf("Add all from list2\n");
    doubleList3->addAll(doubleList3, addDoubleList->values);
    doubleList3->print(doubleList3);
    printf("Collection size, ");
    assertInt(doubleList3->size(doubleList3), 8);
    printf("Get element by index[7]\n");
    num = doubleList3->get(doubleList3, 7);
    doubleList3->print(doubleList3);
    assertDouble(num, 14.01);
    addDoubleList->delete(&addDoubleList);

    DoubleList addDoubleList2 = listOf(addDoubleList2, 20, 1.05,2.05,3.05,4.05,5.05,6.05,7.05,8.05,9.05,10.05,11.05,12.05,13.05,14.05,15.05,16.05,17.05,18.05,19.05,20.05);
    printf("Add all from list3\n");
    doubleList3->addAll(doubleList3, addDoubleList2->values);
    doubleList3->print(doubleList3);
    printf("Collection size, ");
    assertInt(doubleList3->size(doubleList3), 28);
    printf("Get element by index[27]\n");
    num = doubleList3->get(doubleList3, 27);
    assertDouble(num, 20.05);
    addDoubleList2->delete(&addDoubleList2);

    printf("Set element by index[25] by 777.345\n");
    doubleList3->set(doubleList3, 25, 777.345);
    num = doubleList3->get(doubleList3, 25);
    assertDouble(num, 777.345);
    doubleList3->print(doubleList3);

    printf("Index of element with value 777.345\n");
    int index = doubleList3->indexOf(doubleList3, 777.345);
    assertInt(index, 25);

    printf("Sort collection\n");
    doubleList3->sort(doubleList3);
    doubleList3->print(doubleList3);
    printf("Get element by index[1] after sort\n");
    num = doubleList3->get(doubleList3, 1);
    assertDouble(num, 2.05);

    printf("Reverse sort collection\n");
    doubleList3->sortReverse(doubleList3);
    doubleList3->print(doubleList3);
    printf("Get element by index[1] after reverse sort\n");
    num = doubleList3->get(doubleList3, 1);
    assertDouble(num, 67.037);

    printf("Clear collection\n");
    doubleList3->clear(doubleList3);
    doubleList3->print(doubleList3);
    printf("Collection size, ");
    assertInt(doubleList3->size(doubleList3), 0);

    printf("Empty collection\n");
    bool isEmpty = doubleList3->isEmpty(doubleList3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    DoubleList addDoubleList3 = listOf(addDoubleList3, 20, 1.05,2.05,3.05,4.05,5.05,6.05,7.05,8.05,9.05,10.05,11.05,12.05,13.05,14.05,15.05,16.05,17.05,18.05,19.05,20.05);
    doubleList3->addAll(doubleList3, addDoubleList3->values);
    doubleList3->print(doubleList3);
    addDoubleList3->delete(&addDoubleList3);
    printf("Collection contains value 10.05\n");
    bool isContains = doubleList3->contains(doubleList3, 10.05);
    if (isContains)
        assertInt(1, 1);

    DoubleList containsDoubleList = listOf(containsDoubleList, 5, 10.05,11.05,12.05,13.05,14.05);
    printf("Collection contains all from list5\n");
    containsDoubleList->print(containsDoubleList);
    isContains = doubleList3->containsAll(doubleList3, containsDoubleList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsDoubleList->print(containsDoubleList);
    isContains = doubleList3->containsAny(doubleList3, containsDoubleList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem by index[8] from collection\n");
    doubleList3->removeElem(doubleList3, 8);
    doubleList3->print(doubleList3);
    printf("Collection size, ");
    assertInt(doubleList3->size(doubleList3), 19);
    printf("Get element by index[8] after reverse sort\n");
    num = doubleList3->get(doubleList3, 8);
    assertDouble(num, 10.05);

    printf("Remove all from list5\n");
    containsDoubleList->print(containsDoubleList);
    doubleList3->removeAll(doubleList3, containsDoubleList->values);
    printf("Collection size, ");
    doubleList3->print(doubleList3);
    assertInt(doubleList3->size(doubleList3), 14);
    containsDoubleList->delete(&containsDoubleList);


    printf("Subtract from collection\n");
    DoubleList subtractDoubleList = listOf(subtractDoubleList, 5, 15.05,16.05,17.05,18.05,19.05);
    DoubleList subtractDouble = doubleList3->subtract(doubleList3, subtractDoubleList->values);
    printf("new subtract collection: ");
    subtractDouble->print(subtractDouble);
    assertInt(1, 1);
    subtractDoubleList->delete(&subtractDoubleList);
    subtractDouble->delete(&subtractDouble);

    printf("reverse collection\n");
    doubleList3->reverse(doubleList3);
    doubleList3->print(doubleList3);
    printf("Get element by index[0] after reverse\n");
    num = doubleList3->get(doubleList3, 0);
    assertDouble(num, 20.05);

    printf("Collection equals list6\n");
    DoubleList doubleList4 = listOf(doubleList4, 14, 1.05, 2.05, 3.05, 4.05, 5.05, 6.05, 7.05, 8.05, 15.05, 16.05, 17.05, 18.05, 19.05, 20.05);
    printf("Collection after reverse\n");
    doubleList3->reverse(doubleList3);
    doubleList3->print(doubleList3);
    bool isEquals = doubleList3->isEquals(doubleList3, doubleList4);
    if (isEquals) {
        printf("collection is equals list6, ");
        assertInt(1, 1);
    }
    doubleList4->delete(&doubleList4);

    printf("Collection to string\n");
    string strListDouble = doubleList3->toString(doubleList3);
    strListDouble->print(strListDouble);
    assertInt(1, 1);
    doubleList3->delete(&doubleList3);
    strListDouble->delete(&strListDouble);
}


