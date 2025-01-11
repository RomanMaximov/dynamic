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
    string str;
    struct NodeStr* left;
    struct NodeStr* right;
} NodeStr;

// Set data encapsulation
typedef struct InnerStrSet {
    int count;
    int capacity;
    NodeStr** bucket;
} InnerStrSet;

typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct StringArray {
    int count;
    String** str;
    int capacity;
} StringArray;

typedef SetStr* StrSet;
typedef NodeStr* StrNode;
typedef String* string;
typedef StringArray* StringList;

// prototypes private funcs
static StrNode createNode(char* s);
static int hashString(const char* str);
static int compareStr(char* s1, char* s2);
static void insertNode(NodeStr** node, char* s, int* counter);
static void printInOrder(StrNode node, int* counter);
static bool isCapacityFull(StrSet set);
static void increaseCapacity(StrSet set);
static void copyValuesToList(StrNode node, StringList list);
static void setToArr(StrSet set, StringList list);
static void deleteNodes(NodeStr** buckets, int capacity);
static void deleteInOrder(StrNode node);
static bool isContains(StrNode node, string s);
static void quickSortStr(String** strList, int low, int high);
static bool binarySearchStr(string s, String** strList, int high);
static void toListAndSort(StrSet set, StringList list);
static void removeNode(StrNode* node, StrNode* previous, string s, bool* found);
static StrNode findNode(StrNode* node, StrNode* previous);
static bool isRoot(StrNode* node, StrNode* previous);
static bool hasNext(Iterator iter);


void addStrElemSet(StrSet set, string s) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s->data) & 0x7FFFFFFF) % set->inner->capacity;
    insertNode(&set->inner->bucket[indexBucket], s, &set->inner->count);
}

void addCharElemSet(StrSet set, char* s) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s) & 0x7FFFFFFF) % set->inner->capacity;
    insertNode(&set->inner->bucket[indexBucket], s, &set->inner->count);
}

void addAllStrElemSet(StrSet set1, StrSet set2) {
    if (set2 == NULL) return;

    if (isCapacityFull(set1))
        increaseCapacity(set1);

    int count = set2->inner->count;
    StringList list = newStrArray(list);
    setToArr(set2, list);

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->str[i]->data) & 0x7FFFFFFF) % set1->inner->capacity;
        insertNode(&set1->inner->bucket[indexBucket], list->str[i]->data, &set1->inner->count);
    }
}

void clearStrSet(StrSet set) {
    if (set->inner->bucket != NULL) {
        deleteNodes(set->inner->bucket, set->inner->capacity);
        free(set->inner->bucket);
    }

    set->inner->count = 0;
    set->inner->capacity = 16;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeStr*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;
}

bool containsStrSet(StrSet set, string s) {
    for (int i = 0; i < set->inner->capacity; ++i) {
        if(isContains(set->inner->bucket[i], s))
            return true;
    }

    return false;
}

// ===================== private funcs =======================

static int hashString(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = (int)*str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return (int) hash;
}

static bool isCapacityFull(StrSet set) {
    int counter = 0;
    int fullCapacity = set->inner->capacity / 8 * 6;
    for (int i = 0; i < set->inner->capacity; ++i) {
        if (set->inner->bucket[i] != NULL) ++counter;
    }

    return counter >= fullCapacity;
}

static void increaseCapacity(StrSet set) {
    int oldCapacity = set->inner->capacity;
    int count = set->inner->count;
    NodeStr** temp = set->inner->bucket;

    StringList list = newStrArray(list);
    setToArr(set, list);

    set->inner->capacity *= 2;
    set->inner->count = 0;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeStr*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->str[i]->data) & 0x7FFFFFFF) % set->inner->capacity;
        insertNode(&set->inner->bucket[indexBucket], list->str[i]->data, &set->inner->count);
    }

    deleteStrList(list);
    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void setToArr(StrSet set, StringList list) {
    int index = 0;
    for (int i = 0; i < set->inner->capacity; ++i) {
        copyValuesToList(set->inner->bucket[i], list);
    }
}

static void copyValuesToList(StrNode node, StringList list) {
    if (node != NULL) {
        copyValuesToList(node->left, list);
        addCharArrElem(list, node->str->data);
        copyValuesToList(node->right, list);
    }
}

static void insertNode(NodeStr** node, char* s, int* counter) {
    if (*node == NULL) {
        *node = createNode(s);
        (*counter)++;
    } else {
        int cmp = compareStr(s, (*node)->str->data);
        if (cmp == 0) {
            return;
        } else if (cmp < 0) {
            insertNode(&((*node)->left), s, counter);
        } else {
            insertNode(&((*node)->right), s, counter);
        }
    }
}

static StrNode createNode(char* s) {
    StrNode node = malloc(sizeof(NodeStr));
    node->str = stringOf(s);
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void deleteNodes(NodeStr** buckets, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (buckets[i] != NULL)
            deleteInOrder(buckets[i]);
    }
}

static void deleteInOrder(StrNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    deleteString(&node->str);
    free(node);
}

int compareStr(char* s1, char* s2) {
    return strcmp(s1, s2);
}

static bool isContains(StrNode node, string s) {
    if (node != NULL) {
        isContains(node->left, s);
        if (compareStr(node->str->data, s->data) == 0)
            return true;
        isContains(node->right, s);
    }
    return false;
}