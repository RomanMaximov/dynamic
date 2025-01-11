//
// Created by Roman Maximov on 10.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "intset.h"
#include "../collectiontypes.h"

#define ACCURACY 0.000000001

typedef struct NodeDouble {
    double data;
    struct NodeDouble* left;
    struct NodeDouble* right;
} NodeDouble;

// Set data encapsulation
typedef struct InnerDoubleSet {
    int count;
    int capacity;
    NodeDouble** bucket;
} InnerDoubleSet;

typedef SetDouble* DoubleSet;
typedef NodeDouble* DoubleNode;

// prototypes private funcs
static DoubleNode createNode(double num);
static int compareDouble(double elem1, double elem2);
static void insertNode(NodeDouble** node, double num, int* counter);
static void printInOrder(DoubleNode node, int* counter);
static bool isCapacityFull(DoubleSet set);
static void increaseCapacity(DoubleSet set);
static void copyValuesToArr(DoubleNode node, double* arr, int* index);
static void setToArr(DoubleSet set, double* arr);
static void deleteNodes(NodeDouble** nodes, int capacity);
static void deleteInOrder(DoubleNode node);
static bool isContains(DoubleNode node, double num);
static int compareqsort(const void* elem1, const void* elem2);
static bool binarySearch(double elem, const int* arr, int high);
static void toArrAndSort(DoubleSet set, int* arr);
static void removeNode(DoubleNode* node, DoubleNode* previous, double num, bool* found);
static bool isRoot(DoubleNode* node, DoubleNode* previous);
static bool hasNext(Iterator iter);
static int hashDouble(double value);



void addDoubleElemSet(DoubleSet set, double num) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = hashDouble(num) % set->inner->capacity;
    insertNode(&set->inner->bucket[indexBucket], num, &set->inner->count);
}

void addAllDoubleElemSet(DoubleSet set1, DoubleSet set2) {
    if (set2 == NULL) return;

    if (isCapacityFull(set1))
        increaseCapacity(set1);

    int count = set2->inner->count;
    double arr[count];

    setToArr(set2, arr);

    for (int i = 0; i < count; ++i) {
        int indexBucket = hashDouble(arr[i]) % set1->inner->capacity;
        insertNode(&set1->inner->bucket[indexBucket], arr[i], &set1->inner->count);
    }
}

void clearDoubleSet(DoubleSet set) {
    if (set->inner->bucket != NULL) {
        deleteNodes(set->inner->bucket, set->inner->capacity);
        free(set->inner->bucket);
    }

    set->inner->count = 0;
    set->inner->capacity = 16;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeDouble*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;
}

bool containsDoubleSet(DoubleSet set, double num) {
    for (int i = 0; i < set->inner->capacity; ++i) {
        if(isContains(set->inner->bucket[i], num))
            return true;
    }

    return false;
}

// ===================== private funcs =======================

static int hashDouble(double value) {
    uint64_t intRepresentation;
    memcpy(&intRepresentation, &value, sizeof(double));
    intRepresentation = (intRepresentation ^ (intRepresentation >> 32)) * 0x45d9f3b;
    intRepresentation = (intRepresentation ^ (intRepresentation >> 16)) * 0x45d9f3b;
    intRepresentation = intRepresentation ^ (intRepresentation >> 16);
    return (int)intRepresentation;
}

static bool isCapacityFull(DoubleSet set) {
    int counter = 0;
    int fullCapacity = set->inner->capacity / 8 * 6;
    for (int i = 0; i < set->inner->capacity; ++i) {
        if (set->inner->bucket[i] != NULL) ++counter;
    }

    return counter >= fullCapacity;
}

static void increaseCapacity(DoubleSet set) {
    int oldCapacity = set->inner->capacity;
    int count = set->inner->count;
    NodeDouble** temp = set->inner->bucket;

    double arr[count];
    setToArr(set, arr);

    set->inner->capacity *= 2;
    set->inner->count = 0;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeDouble*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = hashDouble(arr[i]) % set->inner->capacity;
        insertNode(&set->inner->bucket[indexBucket], arr[i], &set->inner->count);
    }

    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void insertNode(NodeDouble** node, double num, int* counter) {
    if (*node == NULL) {
        *node = createNode(num);
        (*counter)++;
    } else {
        int cmp = compareDouble(num, (*node)->data);
        if (cmp == 0) {
            return;
        } else if (cmp < 0) {
            insertNode(&((*node)->left), num, counter);
        } else {
            insertNode(&((*node)->right), num, counter);
        }
    }
}

static DoubleNode createNode(double num) {
    DoubleNode node = malloc(sizeof(NodeDouble));
    node->data = num;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static int compareDouble(double elem1, double elem2) {
    if (fabs(elem1 - elem2) < ACCURACY)
        return 0;
    else if (elem1 > elem2)
        return 1;
    else
        return -1;
}

static void deleteNodes(NodeDouble** nodes, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (nodes[i] != NULL)
            deleteInOrder(nodes[i]);
    }
}

static void deleteInOrder(DoubleNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    free(node);
}

static void setToArr(DoubleSet set, double* arr) {
    int index = 0;
    for (int i = 0; i < set->inner->capacity; ++i) {
        copyValuesToArr(set->inner->bucket[i], arr, &index);
    }
}

static void copyValuesToArr(DoubleNode node, double* arr, int* index) {
    if (node != NULL) {
        copyValuesToArr(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArr(node->right, arr, index);
    }
}

static bool isContains(DoubleNode node, double num) {
    if (node != NULL) {
        isContains(node->left, num);
        if (compareDouble(node->data, num) == 0)
            return true;
        isContains(node->right, num);
    }
    return false;
}