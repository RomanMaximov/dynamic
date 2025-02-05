//
// Created by Roman Maximov on 30.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ARRAYLISTUTIL_H
#define ARRAYLISTUTIL_H

#include "../linkedlist.h"
#include "../set.h"

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


typedef struct NodeInt NodeInt;
typedef NodeInt* IntNode;
typedef NodeDouble* DoubleNode;
typedef NodeStr* StrNode;

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

static int compareIntNums(int elem1, int elem2) {
    if (elem1 == elem2)
        return 0;
    else if (elem1 > elem2)
        return 1;
    else
        return -1;
}

static bool findKey(NodeSetInt** node, int num) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareIntNums(num, (*node)->data);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        findKey(&((*node)->left), num);
    } else {
        findKey(&((*node)->right), num);
    }
    return false;
}

static unsigned long long hashCode(int key) {
    unsigned long long tempKey = (unsigned long long) key;
    tempKey = ((tempKey >> 4) ^ tempKey) * 0x1b873593ULL;
    return tempKey;
}

static bool containsKeyInt(IntSet set, int num) {
    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], num);
}

#endif
