//
// Created by Roman Maximov on 07.06.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include "../dynamic.h"
#include "testset.h"

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
static void assertNotNull(void*);
static void testIntSet();
static void testDoubleSet();
static void testStrSet();


void testSet() {
    testIntSet();
    //testDoubleSet();
    //testStrSet();
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

static void testIntSet() {
    puts("=========== test IntSet ===========");
    IntSet intSet = newSet(intSet, NULL);
    assertNotNull((void*) intSet);
    intSet->delete(&intSet);
    if (intSet == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    int temp[] = {23, 67, 55, 4};
    IntSet intSet2 = setOfArr(intSet2, temp, 4);
    printf("Collection size, ");
    assertInt(intSet2->size(intSet2), 4);
    intSet2->delete(&intSet2);
    puts("");

    printf("Create collection as listOf\n");
    IntSet intSet3 = setOf(intSet3, 4, 23, 67, 55, 40);
    intSet3->print(intSet3);
    IntSet addList = setOf(addList, 4, 111, 122, 133, 144);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 4);

    printf("Add all from list2\n");
    intSet3->addAll(intSet3, addList->values);
    intSet3->print(intSet3);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 8);
    intSet3->print(intSet3);
    addList->delete(&addList);

    IntSet addSet2 = setOf(addSet2, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    printf("Add all from list3\n");
    intSet3->addAll(intSet3, addSet2->values);
    intSet3->print(intSet3);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 28);
    addSet2->delete(&addSet2);

    printf("Clear collection\n");
    intSet3->clear(intSet3);
    intSet3->print(intSet3);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 0);

    printf("Empty collection\n");
    bool isEmpty = intSet3->isEmpty(intSet3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    IntSet addSet3 = setOf(addSet3, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    intSet3->addAll(intSet3, addSet3->values);
    intSet3->print(intSet3);
    addSet3->delete(&addSet3);
    printf("Collection contains value 10\n");
    bool isContains = intSet3->contains(intSet3, 10);
    if (isContains)
        assertInt(1, 1);

    IntSet containsSet = setOf(containsSet, 5, 10,11,12,13,14);
    printf("Collection contains all from list5\n");
    containsSet->print(containsSet);
    isContains = intSet3->containsAll(intSet3, containsSet->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsSet->print(containsSet);
    isContains = intSet3->containsAny(intSet3, containsSet->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem 9 from collection\n");
    intSet3->removeElem(intSet3, 9);
    intSet3->print(intSet3);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 19);

    printf("Remove all from list5\n");
    containsSet->print(containsSet);
    intSet3->removeAll(intSet3, containsSet->values);
    printf("Collection size, ");
    assertInt(intSet3->size(intSet3), 14);
    intSet3->print(intSet3);
    containsSet->delete(&containsSet);


    printf("Subtract from collection\n");
    IntSet subtractSet = setOf(subtractSet, 5, 15,16,17,18,19);
    IntSet subtract = intSet3->subtract(intSet3, subtractSet->values);
    printf("new subtract collection: ");
    subtract->print(subtract);
    assertInt(1, 1);
    subtractSet->delete(&subtractSet);
    subtract->delete(&subtract);

    printf("Collection to string\n");
    string strSet3 = intSet3->toString(intSet3);
    strSet3->print(strSet3);
    assertInt(1, 1);
    intSet3->delete(&intSet3);
    strSet3->delete(&strSet3);

    printf("Remove all test\n");
    IntSet bigSet = newSet( bigSet, NULL);
    IntSet  bigSet2 = newSet(bigSet2, NULL);
    for (int i = 0, j = 0; i < 50000; ++i, ++j) {
        bigSet->add( bigSet, i);
        if (i < 25000) continue;
        bigSet2->add(bigSet2, j);
    }
    printf("Collection size, ");
    assertInt( bigSet->size( bigSet), 50000);
    printf("Collection size, ");
    assertInt( bigSet2->size(bigSet2), 25000);
    bigSet->removeAll(bigSet, bigSet2->values);
    printf("Collection size after remove all, ");
    assertInt(bigSet->size(bigSet), 25000);
    printf("Collection contains value 24999\n");
    isContains = bigSet->contains(bigSet, 24999);
    if (isContains)
        assertInt(1, 1);

    bigSet->delete(&bigSet);
    bigSet2->delete(&bigSet2);
}