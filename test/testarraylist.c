//
// Created by Roman Maximov on 13.06.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include "../dynamic.h"
#include "testarraylist.h"

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
static void assertChar(char, char);
static void assertNotNull(void*);
static void testIntList();
static void testDoubleList();
static void testStrList();


void testArrayList() {
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

    IntList addList2 = listOf(addList2, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
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
    IntList addList3 = listOf(addList3, 20, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
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

    printf("Remove all test\n");
    IntList bigList = newList(bigList, NULL);
    IntList bigList2 = newList(bigList2, NULL);
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

    printf("Set element by index[25] to 777.345\n");
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

static void testStrList() {
    puts("=========== test StrArrayList ===========");
    StrList strList = newList(strList, NULL);
    assertNotNull((void*) strList);
    strList->delete(&strList);
    if (strList == NULL)
        puts("Collection after delete is NULL");
    puts("");

    printf("Create collection as listOfArr\n");
    char* temp[] = {"aaa", "bb", "ccc", "d"};
    StrList strList2 = listOfArr(strList2, temp, 4);
    printf("Collection size, ");
    assertInt(strList2->size(strList2), 4);
    strList2->delete(&strList2);
    puts("");

    printf("Create collection as listOf\n");
    StrList strList3 = listOf(strList3, 4, "bb", "aaa", "ccc", "d");
    strList3->print(strList3);
    assertInt(1, 1);
    StrList addList = listOf(addList, 4, "don", "don2", "don3", "don4");
    addList->print(addList);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 4);

    printf("Get element by index[2]\n");
    string str = strList3->get(strList3, 2);
    string checkStr = strOf("ccc");
    assertStr(str, checkStr);
    str->delete(&str);
    checkStr->delete(&checkStr);

    printf("Add all from list2\n");
    strList3->addAll(strList3, addList->values);
    strList3->print(strList3);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 8);
    printf("Get element by index[7]\n");
    str = strList3->get(strList3, 7);
    strList3->print(strList3);
    checkStr = strOf("don4");
    assertStr(str, checkStr);
    addList->delete(&addList);
    str->delete(&str);
    checkStr->delete(&checkStr);

    char* temp2[] = {"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","s12","s13","s14","s15","s16","s17","s18","s19","s20"};
    StrList addList2 = listOfArr(addList2, temp2, 20);
    printf("Add all from list3\n");
    strList3->addAll(strList3, addList2->values);
    strList3->print(strList3);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 28);
    printf("Get element by index[27]\n");
    str = strList3->get(strList3, 27);
    checkStr = strOf("s20");
    assertStr(str, checkStr);
    addList2->delete(&addList2);
    str->delete(&str);
    checkStr->delete(&checkStr);

    checkStr = strOf("summer");
    printf("Set element by index[25] to summer\n");
    strList3->set(strList3, 25, checkStr);
    str = strList3->get(strList3, 25);
    assertStr(str, checkStr);
    strList3->print(strList3);
    str->delete(&str);

    printf("Index of element with value summer\n");
    int index = strList3->indexOf(strList3, checkStr);
    assertInt(index, 25);

    printf("Sort collection\n");
    strList3->sort(strList3);
    strList3->print(strList3);
    printf("Get element by index[1] after sort\n");
    str = strList3->get(strList3, 1);
    checkStr = strOf("bb");
    assertStr(str, checkStr);
    str->delete(&str);
    checkStr->delete(&checkStr);

    printf("Reverse sort collection\n");
    strList3->sortReverse(strList3);
    strList3->print(strList3);
    printf("Get element by index[1] after reverse sort\n");
    str = strList3->get(strList3, 1);
    checkStr = strOf("s9");
    assertStr(str, checkStr);
    str->delete(&str);
    checkStr->delete(&checkStr);

    printf("Clear collection\n");
    strList3->clear(strList3);
    strList3->print(strList3);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 0);

    printf("Empty collection\n");
    bool isEmpty = strList3->isEmpty(strList3);
    if (isEmpty) {
        printf("collection is empty, ");
        assertInt(1, 1);
    }

    printf("Add all from list4\n");
    StrList addList3 = listOfArr(addList3, temp2, 20);
    strList3->addAll(strList3, addList3->values);
    strList3->print(strList3);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 20);
    addList3->delete(&addList3);
    printf("Collection contains value s10\n");
    checkStr = strOf("s10");
    bool isContains = strList3->contains(strList3, checkStr);
    if (isContains)
        assertInt(1, 1);
    checkStr->delete(&checkStr);
    printf("Collection NOT contains value 999\n");
    checkStr = strOf("999");
    isContains = strList3->contains(strList3, checkStr);
    if (!isContains)
        assertInt(1, 1);
    checkStr->delete(&checkStr);

    StrList containsList = listOf(containsList, 5, "s10", "s11", "s12", "s13", "s14");
    printf("Collection contains all from list5\n");
    containsList->print(containsList);
    isContains = strList3->containsAll(strList3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Collection contains any from list5\n");
    containsList->print(containsList);
    isContains = strList3->containsAny(strList3, containsList->values);
    if (isContains)
        assertInt(1, 1);

    printf("Remove elem by index[8] from collection\n");
    strList3->removeElem(strList3, 8);
    strList3->print(strList3);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 19);
    printf("Get element by index[8] after reverse sort\n");
    str = strList3->get(strList3, 8);
    checkStr = strOf("s10");
    assertStr(str, checkStr);
    str->delete(&str);
    checkStr->delete(&checkStr);

    printf("Remove all from list5\n");
    containsList->print(containsList);
    strList3->removeAll(strList3, containsList->values);
    printf("Collection size, ");
    assertInt(strList3->size(strList3), 14);
    strList3->print(strList3);
    containsList->delete(&containsList);

    printf("Subtract from collection\n");
    StrList subtractList = listOf(subtractList, 5, "s15", "s16", "s17", "s18", "s19");
    StrList subtract = strList3->subtract(strList3, subtractList->values);
    printf("new subtract collection: ");
    subtract->print(subtract);
    assertInt(1, 1);
    subtractList->delete(&subtractList);
    subtract->delete(&subtract);

    printf("reverse collection\n");
    strList3->reverse(strList3);
    strList3->print(strList3);
    printf("Get element by index[0] after reverse\n");
    str = strList3->get(strList3, 0);
    checkStr = strOf("s20");
    assertStr(str, checkStr);
    str->delete(&str);
    checkStr->delete(&checkStr);

    printf("Collection equals list6\n");
    char* temp3[] = {"s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s15", "s16", "s17", "s18", "s19", "s20"};
    StrList strList4 = listOfArr(strList4, temp3, 14);
    printf("Collection after reverse\n");
    strList3->reverse(strList3);
    strList3->print(strList3);
    strList4->print(strList4);
    bool isEquals = strList3->isEquals(strList3, strList4);
    if (isEquals) {
        printf("collection is equals list6, ");
        assertInt(1, 1);
    }
    strList4->delete(&strList4);

    printf("Collection to string\n");
    string listStr = strList3->toString(strList3);
    listStr->print(listStr);
    assertInt(1, 1);
    strList3->delete(&strList3);
    listStr->delete(&listStr);
}


