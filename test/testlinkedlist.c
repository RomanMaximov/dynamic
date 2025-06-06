//
// Created by Roman Maximov on 06.06.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include "../dynamic.h"
#include "testlinkedlist.h"

// String data encapsulation
typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;


// funcs prototypes
static void assertInt(int, int);
static void assertDouble(double, double);
static void assertStr(string , string);
//static void assertChar(char, char);
static void assertNotNull(void*);
static void testIntList();
static void testDoubleList();
static void testStrList();

void testLinkedList() {
    testIntList();
    //testDoubleList();
    //testStrList();
}


// private funcs
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

static void assertStr(string result, string expected ) {
    if (strcmp(result->pf->data, expected->pf->data) == 0) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %s, but result: %s\n", expected->pf->data, result->pf->data);
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
    puts("=========== test IntLinkedList ===========");
    IntLinkedList intList = newList(intList, NULL);
    assertNotNull((void*) intList);
    intList->delete(&intList);
    if (intList == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    int temp[] = {23, 67, 55, 4};
    IntLinkedList intList2 = listOfArr(intList2, temp, 4);
    printf("Collection size, ");
    assertInt(intList2->size(intList2), 4);
    intList2->delete(&intList2);
    puts("");

    printf("Create collection as listOf\n");
    IntLinkedList intList3 = listOf(intList3, 4, 23, 67, 55, 4);
    intList3->print(intList3);
    IntLinkedList addList = listOf(addList, 4, 11, 12, 13, 14);
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

    IntLinkedList addList2 = listOf(addList2, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    printf("Add all from list3\n");
    intList3->addAll(intList3, addList2->values);
    intList3->print(intList3);
    printf("Collection size, ");
    assertInt(intList3->size(intList3), 28);
    printf("Get element by index[27]\n");
    num = intList3->get(intList3, 27);
    assertInt(num, 20);
    addList2->delete(&addList2);

    printf("Set element by index[25] to 777\n");
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
    IntLinkedList addList3 = listOf(addList3, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    intList3->addAll(intList3, addList3->values);
    intList3->print(intList3);
    addList3->delete(&addList3);
    printf("Collection contains value 10\n");
    bool isContains = intList3->contains(intList3, 10);
    if (isContains)
        assertInt(1, 1);

    IntLinkedList containsList = listOf(containsList, 5, 10,11,12,13,14);
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
    IntLinkedList subtractList = listOf(subtractList, 5, 15,16,17,18,19);
    IntLinkedList subtract = intList3->subtract(intList3, subtractList->values);
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
    IntLinkedList intList4 = listOf(intList4, 14, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 18, 19, 20);
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

    printf("Remove all test\n");
    IntLinkedList bigList = newList(bigList, NULL);
    IntLinkedList bigList2 = newList(bigList2, NULL);
    for (int i = 0, j = 0; i < 50000; ++i, ++j) {
        bigList->add(bigList, i);
        if (i < 25000) continue;
        bigList2->add(bigList2, j);
    }
    printf("Collection size, ");
    assertInt(bigList->size(bigList), 50000);
    printf("Collection size, ");
    assertInt(bigList2->size(bigList2), 25000);
    bigList->removeAll(bigList, bigList2->values);
    printf("Collection size after remove all, ");
    assertInt(bigList->size(bigList), 25000);
    printf("Get element by index[24999]\n");
    num = bigList->get(bigList, 24999);
    assertInt(num, 24999);
    bigList->delete(&bigList);
    bigList2->delete(&bigList2);
}