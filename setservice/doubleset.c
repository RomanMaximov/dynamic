//
// Created by Roman Maximov on 10.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "intset.h"
#include "../collectiontypes.h"

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
static int compareInt(double elem1, double elem2);
static void insertNode(NodeDouble** node, double num, int* counter);
static void printInOrder(DoubleNode node, int* counter);
static bool isCapacityFull(DoubleSet set);
static void increaseCapacity(DoubleSet set);
static void copyValuesToArr(DoubleNode node, int* arr, int* index);
static void setToArr(DoubleSet set, int* arr);
static void deleteNodes(NodeDouble** nodes, int capacity);
static void deleteInOrder(DoubleNode node);
static bool isContains(DoubleNode node, double num);
static int compareqsort(const void* elem1, const void* elem2);
static bool binarySearch(double elem, const int* arr, int high);
static void toArrAndSort(DoubleSet set, int* arr);
static void removeNode(DoubleNode* node, DoubleNode* previous, double num, bool* found);
static bool isRoot(DoubleNode* node, DoubleNode* previous);
static bool hasNext(Iterator iter);





