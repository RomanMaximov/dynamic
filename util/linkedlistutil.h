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

#define ACCURACY 0.000000001


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
    int capacityCounter;
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
    int capacityCounter;
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
    int capacityCounter;
    struct NodeSetStr** bucket;
} InnerStrSet;

typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;


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

static int compareIntNums(int elem1, int elem2) {
    if (elem1 == elem2)
        return 0;
    else if (elem1 > elem2)
        return 1;
    else
        return -1;
}

static int compareDoubleNums(double elem1, double elem2) {
    if (fabs(elem1 - elem2) < ACCURACY)
        return 0;
    else if (elem1 > elem2)
        return 1;
    else
        return -1;
}

static int compareStrings(string s1, string s2) {
    return strcmp(s1->pf->data, s2->pf->data);
}

static bool findKeyInt(NodeSetInt** node, int num, bool* found) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareIntNums(num, (*node)->data);
    if (cmp == 0) {
        *found = true;
        return true;
    } else if (cmp < 0) {
        findKeyInt(&((*node)->left), num, found);
    } else {
        findKeyInt(&((*node)->right), num, found);
    }
    return *found;
}

static unsigned long long hashCode(int key) {
    unsigned long long tempKey = (unsigned long long) key;
    tempKey = ((tempKey >> 4) ^ tempKey) * 0x1b873593ULL;
    return tempKey;
}

static bool containsKeyInt(IntSet set, int num) {
    bool found = false;
    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    return findKeyInt(&set->pf->bucket[indexBucket], num, &found);
}

static bool findKeyDouble(NodeSetDouble** node, double num, bool* found) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareDoubleNums(num, (*node)->data);
    if (cmp == 0) {
        *found = true;
        return true;
    } else if (cmp < 0) {
        findKeyDouble(&((*node)->left), num, found);
    } else {
        findKeyDouble(&((*node)->right), num, found);
    }
    return *found;
}

static int hashDouble(double value) {
    uint64_t intRepresentation;
    memcpy(&intRepresentation, &value, sizeof(double));
    intRepresentation = (intRepresentation ^ (intRepresentation >> 32)) * 0x45d9f3b;
    intRepresentation = (intRepresentation ^ (intRepresentation >> 16)) * 0x45d9f3b;
    intRepresentation = intRepresentation ^ (intRepresentation >> 16);
    return abs((int)intRepresentation);
}

static bool containsKeyDouble(DoubleSet set, double num) {
    bool found = false;
    int indexBucket = (int) (hashDouble(num) % set->pf->capacity);
    return findKeyDouble(&set->pf->bucket[indexBucket], num, &found);
}

static bool findKeyStr(NodeSetStr** node, string s) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareStrings(s, (*node)->str);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        findKeyStr(&((*node)->left), s);
    } else {
        findKeyStr(&((*node)->right), s);
    }
    return false;
}

static int hashString(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = (int)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return (int) hash;
}

static bool containsKeyStr(StrSet set, string s) {
    int indexBucket = (int) (hashString(s->pf->data) % set->pf->capacity);
    return findKeyStr(&set->pf->bucket[indexBucket], s);
}


#endif
