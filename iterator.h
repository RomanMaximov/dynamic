//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include "collectiontypes.h"

#define next(T) _Generic((T),      \
    Iterator : itr_gv_             \
)(T)

#define getValue(T) _Generic((T),  \
    int : itr_giv_,                \
    double : itr_gdv_,             \
    string : itr_gsv_              \
)(T)

typedef struct Itr {
    int count;
    int collectionSize;
    void* collection;
    void* elemValue;
    Type type;
    bool (*hasNext)(struct Itr* iter);
} Itr;

typedef struct ArrayListInt ArrayListInt;
typedef struct LinkedListInt LinkedListInt;
typedef struct LinkedListDouble LinkedListDouble;
typedef struct LinkedListStr LinkedListStr;
typedef struct String String;

typedef ArrayListInt* IntList;
typedef LinkedListInt* IntLinkedList;
typedef LinkedListDouble* DoubleLinkedList;
typedef LinkedListStr* StrLinkedList;
typedef String* string;
typedef Itr* Iterator;

// prototypes
static int itr_giv_(Iterator iter);
static double itr_gdv_(Iterator iter);
static string itr_gsv_(Iterator iter);


static int itr_giv_(Iterator iter) {
    if (iter->type == INT_LIST || iter->type == INT_LL || iter->type == INT_SET) {
        return *((int*)iter->elemValue);
    }
}

static double itr_gdv_(Iterator iter) {
    if (iter->type == DOUBLE_LIST || iter->type == DOUBLE_LL || iter->type == DOUBLE_SET) {
        return *((double *)iter->elemValue);
    }
}

static string itr_gsv_(Iterator iter) {
    if (iter->type == STR_LIST || iter->type == STR_LL || iter->type == STR_SET) {
        return (string)iter->elemValue;
    }
}

static void* itr_gv_(Iterator iter) {
    if (iter->type == INT_LIST || iter->type == INT_LL || iter->type == INT_SET) {
        return itr_giv_;
    }
    if (iter->type == DOUBLE_LIST || iter->type == DOUBLE_LL || iter->type == DOUBLE_SET) {
        return itr_gdv_;
    }
    if (iter->type == STR_LIST || iter->type == STR_LL || iter->type == STR_SET) {
        return itr_gsv_;
    }
}

#endif
