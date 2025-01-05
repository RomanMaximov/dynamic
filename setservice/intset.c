//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "intset.h"
#include "../collectiontypes.h"

typedef struct NodeInt {
    int data;
    struct NodeInt* left;
    struct NodeInt* right;
} NodeInt;

// Set data encapsulation
typedef struct InnerIntSet {
    int count;
    int capacity;
    NodeInt** bucket;
} InnerIntSet;

typedef SetInt* IntSet;
typedef NodeInt* IntNode;

// prototypes private funcs
static IntNode createNode(int num);
static int compareInt(int elem1, int elem2);
static void insertNode(NodeInt** node, int num, int* counter);
static void printInOrder(IntNode node, int* counter);
static bool isCapacityFull(IntSet set);
static void increaseCapacity(IntSet set);
static void getValueInOrder(IntNode node, int* arr, int* index);
static void deleteNodes(NodeInt** nodes, int capacity);
static void deleteInOrder(IntNode node);


void addIntElemSet(IntSet set, int num) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = num % set->inner->capacity;
    insertNode(&set->inner->bucket[indexBucket], num, &set->inner->count);
}

void addAllIntElemSet(IntSet set1, IntSet set2) {
    if (set2 == NULL) return;

    if (isCapacityFull(set1))
        increaseCapacity(set1);

    int count = set2->inner->count;
    int* arr = malloc(count * sizeof(int));

    int index = 0;
    for (int i = 0; i < set2->inner->capacity; ++i) {
        getValueInOrder(set2->inner->bucket[i], arr, &index);
    }

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set1->inner->capacity;
        insertNode(&set1->inner->bucket[indexBucket], arr[i], &set1->inner->count);
    }

    free(arr);
}

void clearIntSet(IntSet set) {
    if (set->inner->bucket != NULL) {
        deleteNodes(set->inner->bucket, set->inner->capacity);
        free(set->inner->bucket);
    }

    set->inner->count = 0;
    set->inner->capacity = 16;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;
}

void printSet(IntSet set) {
    if (set == NULL || set->inner == NULL) {
        printf("%s", "[]");
        return;
    }

    printf("%s", "[");

    int counter = set->inner->count;
    for (int i = 0; i < set->inner->capacity; ++i) {
        printInOrder(set->inner->bucket[i], &counter);
    }

    printf("%s", "]");
    puts("");
}

void deleteIntSet(IntSet* set) {
    if (set == NULL || *set == NULL || (*set)->inner == NULL) return;

    if ((*set)->inner->bucket != NULL) {
        deleteNodes((*set)->inner->bucket, (*set)->inner->capacity);
        free((*set)->inner->bucket);
    }
    free(*set);
    *set = NULL;
}

static  void printInOrder(IntNode node, int* counter) {
    if (node != NULL) {
        printInOrder(node->left, counter);
        printf("%d", node->data);
        if (*counter - 1 != 0) {
            printf("%s", ", ");
            --(*counter);
        }
        printInOrder(node->right, counter);
    }
}

static int compareInt(int elem1, int elem2) {
    if (elem1 == elem2)
        return 0;
    else if (elem1 > elem2)
        return 1;
    else
        return -1;
}

static void insertNode(NodeInt** node, int num, int* counter) {
    if (*node == NULL) {
        *node = createNode(num);
        (*counter)++;
    } else {
        int cmp = compareInt(num, (*node)->data);
        if (cmp == 0) {
            return;
        } else if (cmp < 0) {
            insertNode(&((*node)->left), num, counter);
        } else {
            insertNode(&((*node)->right), num, counter);
        }
    }
}

static IntNode createNode(int num) {
    IntNode node = malloc(sizeof(NodeInt));
    node->data = num;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static bool isCapacityFull(IntSet set) {
    int counter = 0;
    int fullCapacity = set->inner->capacity / 8 * 6;
    for (int i = 0; i < set->inner->capacity; ++i) {
        if (set->inner->bucket[i] != NULL) ++counter;
    }

    return counter >= fullCapacity;
}

static void increaseCapacity(IntSet set) {
    int oldCapacity = set->inner->capacity;
    int count = set->inner->count;
    NodeInt** temp = set->inner->bucket;

    set->inner->capacity *= 2;
    set->inner->count = 0;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;

    int* arr = malloc(count * sizeof(int));

    int index = 0;
    for (int i = 0; i < oldCapacity; ++i) {
        getValueInOrder(temp[i], arr, &index);
    }

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set->inner->capacity;
        insertNode(&set->inner->bucket[indexBucket], arr[i], &set->inner->count);
    }

    free(arr);
    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void getValueInOrder(IntNode node, int* arr, int* index) {
    if (node != NULL) {
        getValueInOrder(node->left, arr, index);
        arr[(*index)++] = node->data;
        getValueInOrder(node->right, arr, index);
    }
}

static void deleteNodes(NodeInt** nodes, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (nodes[i] != NULL)
            deleteInOrder(nodes[i]);
    }
}

static void deleteInOrder(IntNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    free(node);
}