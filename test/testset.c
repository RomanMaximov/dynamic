//
// Created by Roman Maximov on 07.06.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <time.h>
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
        printf("test: ===== OK =====\n");
    } else {
        printf("test: =============================== FAILURE ===============================\n");
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

    clock_t start = clock();
    printf("Remove all test\n");
    IntSet bigSet = newSet( bigSet, NULL);
    IntSet  bigSet2 = newSet(bigSet2, NULL);
    for (int i = 0, j = 0; i < 50000; ++i, ++j) {
        bigSet->add(bigSet, i);
        if (i < 25000) continue;
        bigSet2->add(bigSet2, j);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / 1000;
    printf("========= Total time filling collections: %lf\n", (double) time_spent);

    printf("Collection size, ");
    assertInt( bigSet->size(bigSet), 50000);
    printf("Collection size, ");
    assertInt( bigSet2->size(bigSet2), 25000);

    bigSet->removeAll(bigSet, bigSet2->values);
    end = clock();
    time_spent = (double)(end - start) / 1000;
    printf("========= Total time for removeAll function: %lf\n", (double) time_spent);

    printf("Collection size after remove all, ");
    assertInt(bigSet->size(bigSet), 25000);
    printf("Collection contains value 24999\n");
    isContains = bigSet->contains(bigSet, 24999);
    if (isContains)
        assertInt(1, 1);
    printf("Collection NOT contains value 35000\n");
    isContains = bigSet->contains(bigSet, 35000);
    if (!isContains)
        assertInt(1, 1);

    
    IntSet bigSet3 = newSet(bigSet3, NULL);
    IntSet bigSet4 = newSet(bigSet4, NULL);

    for (int i = 0, j = 50000; i < 50000; ++i, ++j) {
        bigSet4->add(bigSet4, i);
        if (j >= 50010) continue;
        bigSet3->add(bigSet3, j);
    }
    start = clock();
    bigSet3->addAll(bigSet3, bigSet4->values);
    end = clock();
    time_spent = (double)(end - start) / 1000;
    printf("========= Total time for addAll function: %lf\n", (double) time_spent);
    printf("Collection size after add all, ");
    assertInt( bigSet3->size(bigSet3), 50010);

    bigSet->delete(&bigSet);
    bigSet2->delete(&bigSet2);
    bigSet3->delete(&bigSet3);
    bigSet4->delete(&bigSet4);
}

static void testDoubleSet() {
    puts("=========== test DoubleSet ===========");
    DoubleSet doubleSet = newSet(doubleSet, NULL);
    assertNotNull((void*) doubleSet);
    doubleSet->delete(&doubleSet);
    if (doubleSet == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    double temp[] = {23.55, 67.037, 55.999, 4.37};
    DoubleSet doubleSet2 = setOfArr(doubleSet2, temp, 4);
    printf("Collection size, ");
    assertInt(doubleSet2->size(doubleSet2), 4);
    doubleSet2->delete(&doubleSet2);
    puts("");

    printf("Create collection as listOf\n");
    DoubleSet doubleSet3 = setOf(doubleSet3, 4, 23.55, 67.037, 55.999, 4.37);
    doubleSet3->print(doubleSet3);
    DoubleSet adddoubleSet = setOf(adddoubleSet, 4, 11.01, 12.01, 13.01, 14.01);
    printf("Collection size, ");
    assertInt(doubleSet3->size(doubleSet3), 4);

    printf("Add all from list2\n");
    doubleSet3->addAll(doubleSet3, adddoubleSet->values);
    doubleSet3->print(doubleSet3);
    printf("Collection size, ");
    assertInt(doubleSet3->size(doubleSet3), 8);
    doubleSet3->print(doubleSet3);
    adddoubleSet->delete(&adddoubleSet);

    DoubleSet adddoubleSet2 = setOf(adddoubleSet2, 20, 1.05,2.05,3.05,4.05,5.05,6.05,7.05,8.05,9.05,10.05,11.05,12.05,13.05,14.05,15.05,16.05,17.05,18.05,19.05,20.05);
    printf("Add all from list3\n");
    doubleSet3->addAll(doubleSet3, adddoubleSet2->values);
    doubleSet3->print(doubleSet3);
    printf("Collection size, ");
    assertInt(doubleSet3->size(doubleSet3), 28);
    adddoubleSet2->delete(&adddoubleSet2);

    printf("Clear collection\n");
    doubleSet3->clear(doubleSet3);
    doubleSet3->print(doubleSet3);
    printf("Collection size, ");
    assertInt(doubleSet3->size(doubleSet3), 0);

    printf("Empty collection\n");
    bool isEmpty = doubleSet3->isEmpty(doubleSet3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    DoubleSet adddoubleSet3 = setOf(adddoubleSet3, 20, 1.05,2.05,3.05,4.05,5.05,6.05,7.05,8.05,9.05,10.05,11.05,12.05,13.05,14.05,15.05,16.05,17.05,18.05,19.05,20.05);
    doubleSet3->addAll(doubleSet3, adddoubleSet3->values);
    doubleSet3->print(doubleSet3);
    adddoubleSet3->delete(&adddoubleSet3);
    printf("Collection contains value 10.05\n");
    bool isContains = doubleSet3->contains(doubleSet3, 10.05);
    if (isContains)
        assertInt(1, 1);

    DoubleSet containsdoubleSet = setOf(containsdoubleSet, 5, 10.05,11.05,12.05,13.05,14.05);
    printf("Collection contains all from list5\n");
    containsdoubleSet->print(containsdoubleSet);
    isContains = doubleSet3->containsAll(doubleSet3, containsdoubleSet->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsdoubleSet->print(containsdoubleSet);
    isContains = doubleSet3->containsAny(doubleSet3, containsdoubleSet->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem with value 9.05 from collection\n");
    doubleSet3->removeElem(doubleSet3, 9.05);
    doubleSet3->print(doubleSet3);
    printf("Collection size, ");
    assertInt(doubleSet3->size(doubleSet3), 19);

    printf("Remove all from list5\n");
    containsdoubleSet->print(containsdoubleSet);
    doubleSet3->removeAll(doubleSet3, containsdoubleSet->values);
    printf("Collection size, ");
    doubleSet3->print(doubleSet3);
    assertInt(doubleSet3->size(doubleSet3), 14);
    containsdoubleSet->delete(&containsdoubleSet);

    printf("Subtract from collection\n");
    DoubleSet subtractdoubleSet = setOf(subtractdoubleSet, 5, 15.05,16.05,17.05,18.05,19.05);
    DoubleSet subtractDouble = doubleSet3->subtract(doubleSet3, subtractdoubleSet->values);
    printf("new subtract collection: ");
    subtractDouble->print(subtractDouble);
    assertInt(1, 1);
    subtractdoubleSet->delete(&subtractdoubleSet);
    subtractDouble->delete(&subtractDouble);

    printf("Collection to string\n");
    string strSetDouble = doubleSet3->toString(doubleSet3);
    strSetDouble->print(strSetDouble);
    assertInt(1, 1);
    doubleSet3->delete(&doubleSet3);
    strSetDouble->delete(&strSetDouble);
}

static void testStrSet() {
    puts("=========== test StrSet ===========");
    StrSet strSet = newSet(strSet, NULL);
    assertNotNull((void*) strSet);
    strSet->delete(&strSet);
    if (strSet == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    char* temp[] = {"aaa", "bb", "ccc", "d"};
    StrSet strSet2 = setOfArr(strSet2, temp, 4);
    printf("Collection size, ");
    assertInt(strSet2->size(strSet2), 4);
    strSet2->delete(&strSet2);
    puts("");

    printf("Create collection as listOf\n");
    StrSet strSet3 = setOf(strSet3, 4, "bb", "aaa", "ccc", "d");
    strSet3->print(strSet3);
    assertInt(1, 1);
    StrSet addList = setOf(addList, 4, "don", "don2", "don3", "don4");
    addList->print(addList);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 4);

    printf("Add all from list2\n");
    strSet3->addAll(strSet3, addList->values);
    strSet3->print(strSet3);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 8);
    addList->delete(&addList);

    char* temp2[] = {"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","s12","s13","s14","s15","s16","s17","s18","s19","s20"};
    StrSet addList2 = setOfArr(addList2, temp2, 20);
    printf("Add all from list3\n");
    strSet3->addAll(strSet3, addList2->values);
    strSet3->print(strSet3);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 28);
    addList2->delete(&addList2);

    printf("Clear collection\n");
    strSet3->clear(strSet3);
    strSet3->print(strSet3);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 0);

    printf("Empty collection\n");
    bool isEmpty = strSet3->isEmpty(strSet3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    StrSet addList3 = setOfArr(addList3, temp2, 20);
    strSet3->addAll(strSet3, addList3->values);
    strSet3->print(strSet3);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 20);
    addList3->delete(&addList3);
    printf("Collection contains value s10\n");
    string checkStr = strOf("s10");
    bool isContains = strSet3->contains(strSet3, checkStr);
    if (isContains)
        assertInt(1, 1);
    checkStr->delete(&checkStr);
    printf("Collection NOT contains value 999\n");
    checkStr = strOf("999");
    isContains = strSet3->contains(strSet3, checkStr);
    if (!isContains)
        assertInt(1, 1);
    checkStr->delete(&checkStr);

    StrSet containsList = setOf(containsList, 5, "s10", "s11", "s12", "s13", "s14");
    printf("Collection contains all from list5\n");
    containsList->print(containsList);
    isContains = strSet3->containsAll(strSet3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsList->print(containsList);
    isContains = strSet3->containsAny(strSet3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem with value s9 from collection\n");
    checkStr = strOf("s9");
    strSet3->removeElem(strSet3, checkStr);
    strSet3->print(strSet3);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 19);
    checkStr->delete(&checkStr);

    printf("Remove all from list5\n");
    containsList->print(containsList);
    strSet3->removeAll(strSet3, containsList->values);
    printf("Collection size, ");
    assertInt(strSet3->size(strSet3), 14);
    strSet3->print(strSet3);
    containsList->delete(&containsList);

    printf("Subtract from collection\n");
    StrSet subtractList = setOf(subtractList, 5, "s15", "s16", "s17", "s18", "s19");
    StrSet subtract = strSet3->subtract(strSet3, subtractList->values);
    printf("new subtract collection: ");
    subtract->print(subtract);
    assertInt(1, 1);
    subtractList->delete(&subtractList);
    subtract->delete(&subtract);

    printf("Collection to string\n");
    string listStr = strSet3->toString(strSet3);
    listStr->print(listStr);
    assertInt(1, 1);
    strSet3->delete(&strSet3);
    listStr->delete(&listStr);
}