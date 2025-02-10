//
// Created by Roman Maximov on 10.02.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef LINKEDLISTUTIL_H
#define LINKEDLISTUTIL_H

#include <stdint.h>
#include <math.h>
#include "../arraylist.h"
#include "../set.h"
#include "../string.h"


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
    String** data;
    int capacity;
} InnerStrList;

typedef struct NodeSetInt {
    int data;
    struct NodeSetInt* left;
    struct NodeSetInt* right;
} NodeSetInt;

typedef struct InnerIntSet {
    int count;
    int capacity;
    struct NodeSetInt** bucket;
} InnerIntSet;

typedef struct NodeSetDouble {
    double data;
    struct NodeSetDouble* left;
    struct NodeSetDouble* right;
} NodeSetDouble;

typedef struct InnerDoubleSet {
    int count;
    int capacity;
    struct NodeSetDouble** bucket;
} InnerDoubleSet;

typedef struct NodeSetStr {
    string str;
    struct NodeSetStr* left;
    struct NodeSetStr* right;
} NodeSetStr;

typedef struct InnerStrSet {
    int count;
    int capacity;
    struct NodeSetStr** bucket;
} InnerStrSet;

typedef ArrayListInt* IntList;
typedef ArrayListDouble* DoubleList;
typedef ArrayListStr* StrList;

typedef NodeSetInt* IntSetNode;
typedef NodeSetDouble* DoubleSetNode;
typedef NodeSetStr* StrSetNode;

// private funcs
static void copyValuesToArrInt(IntSetNode node, int* arr, int* index) {
    if (node != NULL) {
        copyValuesToArrInt(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArrInt(node->right, arr, index);
    }
}

static void setToArrInt(IntSet set, int* arr) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToArrInt(set->pf->bucket[i], arr, &index);
    }
}

static void copyValuesToArrDouble(DoubleSetNode node, double* arr, int* index) {
    if (node != NULL) {
        copyValuesToArrDouble(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArrDouble(node->right, arr, index);
    }
}

static void setToArrDouble(DoubleSet set, double* arr) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToArrDouble(set->pf->bucket[i], arr, &index);
    }
}

static void copyValuesToList(StrSetNode node, StrList list) {
    if (node != NULL) {
        copyValuesToList(node->left, list);
        list->add(list, node->str);
        copyValuesToList(node->right, list);
    }
}

static void setToArrStr(StrSet set, StrList list) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToList(set->pf->bucket[i], list);
    }
}


#endif
