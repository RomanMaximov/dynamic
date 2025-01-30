//
// Created by Roman Maximov on 30.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef UTIL_H
#define UTIL_H

#include "arraylist.h"
#include "linkedlist.h"
#include "set.h"

// structures for LL
typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

// structures for LL
typedef struct InnerIntLL {
    int count;
    int index;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} InnerIntLL;

typedef struct NodeSetInt {
    int data;
    struct NodeSetInt* left;
    struct NodeSetInt* right;
} NodeSetInt;

// Set data encapsulation
typedef struct InnerIntSet {
    int count;
    int capacity;
    struct NodeSetInt** bucket;
} InnerIntSet;

typedef struct NodeInt NodeInt;
typedef NodeInt* IntNode;
typedef NodeSetInt* IntSetNode;


// private funcs



static void copyValuesToArr(IntSetNode node, int* arr, int* index) {
    if (node != NULL) {
        copyValuesToArr(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArr(node->right, arr, index);
    }
}

void setToArr(IntSet set, int* arr) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToArr(set->pf->bucket[i], arr, &index);
    }
}

#endif
