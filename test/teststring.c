//
// Created by Roman Maximov on 13.06.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include "../dynamic.h"
#include "teststring.h"

// String data encapsulation
typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;


// funcs prototypes
static void assertInt(int, int);
static void assertStr(string , string);
static void assertChar(char, char);
static void assertNotNull(void*);


void testString() {
    puts("=========== test String ===========");
    string str = strOf("first str");
    str->print(str);
    assertNotNull((void*) str);
    str->delete(&str);
    if (str == NULL) {
        printf("String after delete is NULL, ");
        assertInt(1, 1);
    }

    printf("Length of string\n");
    string str2 = strOf("first str");
    int strLength = str2->length(str2);
    assertInt(strLength, 9);  // "first str" = 9

    printf("Concat another string\n");
    string concatStr = strOf("CONCAT");
    printf("new str = ");
    concatStr->print(concatStr);
    str2->concat(str2, concatStr);
    str2->print(str2);
    string checkStr = strOf("first strCONCAT");
    assertStr(str2, checkStr);
    printf("Length of string after concat\n");
    strLength = str2->length(str2);
    assertInt(strLength, 15);
    concatStr->delete(&concatStr);
    deleteStr(&checkStr);

    printf("Replace letter 's' to 'W'\n");
    str2->replace(str2, "s", "W");
    str2->print(str2);
    checkStr = strOf("firWt WtrCONCAT");
    assertStr(str2, checkStr);
    deleteStr(&checkStr);






    printf("String is empty\n");
    string empty = emptyStr();
    empty->print(empty);
    bool isEmpty = empty->isEmpty(empty);
    if (isEmpty) {
        printf("String is empty, ");
        assertInt(1, 1);
    }
    empty->delete(&empty);


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

static void assertStr(string result, string expected ) {
    if (strcmp(result->pf->data, expected->pf->data) == 0) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %s, but result: %s\n", expected->pf->data, result->pf->data);
        puts("");
    }
}

static void assertChar(char result, char expected ) {
    if (result == expected) {
        printf("test: \t%sOK%s\n", GREEN, RESET);
    } else {
        printf("test: \t%sFAILURE%s\n", RED, RESET);
        printf("expected: %c, but result: %c\n", expected, result);
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
