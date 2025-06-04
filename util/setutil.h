//
// Created by Roman Maximov on 05.02.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef SETUTIL_H
#define SETUTIL_H

#include "../linkedlist.h"
#include "../arraylist.h"


typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct InnerIntLL {
    int count;
    int index;
    struct NodeInt* nodes;
    struct NodeInt* begin;
    struct NodeInt* end;
} InnerIntLL;

typedef struct NodeDouble {
    double data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;

typedef struct InnerDoubleLL {
    int count;
    int index;
    struct NodeDouble* nodes;
    struct NodeDouble* begin;
    struct NodeDouble* end;
} InnerDoubleLL;

typedef struct NodeStr {
    string data;
    struct NodeStr* next;
    struct NodeStr* prev;
} NodeStr;

typedef struct InnerStrLL {
    int count;
    int index;
    struct NodeStr* nodes;
    struct NodeStr* begin;
    struct NodeStr* end;
} InnerStrLL;

typedef struct InnerIntList {
    int count;
    int* data;
    int capacity;
} InnerIntList;

typedef struct InnerDoubleList {
    int count;
    double* data;
    int capacity;
} InnerDoubleList;

typedef struct InnerStrList {
    int count;
    struct String** data;
    int capacity;
} InnerStrList;


typedef struct NodeInt NodeInt;
typedef NodeInt* IntNode;
typedef NodeDouble* DoubleNode;
typedef NodeStr* StrNode;



// private funcs



#endif
