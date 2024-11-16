//
// Created by Roman Maximov on 14.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "dynamicarray.h"
#include "arrcustom.h"


// structures
typedef struct InnerIntArray {
    int count;
    int* data;
    int capacity;
} InnerIntArray;

typedef IntArraySS* IntListSS;

// custom types
typedef enum TypeSS {
    INT_LIST_SS
} TypeSS;


// funcs prototypes
bool addIntElemSS(IntListSS list, int num);
static void initFuncs(IntListSS list);
static void* add(TypeSS type);


IntListSS newIntArraySS(IntListSS temp) {
    IntListSS list = malloc(sizeof(IntArraySS));
    list->inner = malloc(sizeof(InnerIntArray));
    list->inner->count = 0;
    list->inner->capacity = 20;
    list->inner->data = malloc(list->inner->capacity * sizeof(int));
    initFuncs(list);
    return list;
}

bool addIntElemSS(IntListSS list, int num) {
    void* elem = &num;
    if (list->inner->count == list->inner->capacity) {
        //list->data = increaseCapacityInt(list);

        memcpy(&list->inner->data[list->inner->count], elem, sizeof(int));
        list->inner->count++;
    }
    else {
        memcpy(&list->inner->data[list->inner->count], elem, sizeof(int));
        list->inner->count++;
    }
    return true;
}

static void initFuncs(IntListSS list) {
    list->add = add(INT_LIST_SS);
}

void* add(TypeSS type) {
    switch (type) {
        case INT_LIST_SS:
            return addIntElemSS;

    }
}
