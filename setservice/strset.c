//
// Created by Roman Maximov on 11.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "strset.h"
#include "../dynamicarray.h"

typedef struct NodeStr {
    string data;
    struct NodeStr* left;
    struct NodeStr* right;
} NodeStr;

// Set data encapsulation
typedef struct InnerStrSet {
    int count;
    int capacity;
    NodeStr** bucket;
} InnerStrSet;

typedef SetStr* StrSet;
typedef NodeStr* StrNode;

// prototypes private funcs
static StrNode createNode(string s);
static int compareStr(string s1, string s2);
static void insertNode(NodeStr** node, string s, int* counter);
static void printInOrder(StrNode node, int* counter);
static bool isCapacityFull(StrSet set);
static void increaseCapacity(StrSet set);
static void copyValuesToArr(StrNode node, StringList list, int* index);
static void setToArr(StrSet set, StringList list);
static void deleteNodes(NodeStr** nodes, int capacity);
static void deleteInOrder(StrNode node);
static bool isContains(StrNode node, string s);
static void quickSortStr(String** strList, int low, int high);
static bool binarySearchStr(string s, String** strList, int high);
static void toListAndSort(StrSet set, StringList list);
static void removeNode(StrNode* node, StrNode* previous, string s, bool* found);
static StrNode findNode(StrNode* node, StrNode* previous);
static bool isRoot(StrNode* node, StrNode* previous);
static bool hasNext(Iterator iter);





// ===================== private funcs =======================