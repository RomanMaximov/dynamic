//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "intset.h"

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
static void copyValuesToArr(IntNode node, int* arr, int* index);
static void setToArr(IntSet set, int* arr);
static void deleteNodes(NodeInt** buckets, int capacity);
static void deleteInOrder(IntNode node);
static bool isContains(IntNode node, int num);
static int compareqsort(const void* elem1, const void* elem2);
static bool binarySearch(int elem, const int* arr, int high);
static void toArrAndSort(IntSet set, int* arr);
static void removeNode(IntNode* node, IntNode* previous, int num, bool* found);
static IntNode findNode(IntNode* node, IntNode* previous);
static bool isRoot(IntNode* node, IntNode* previous);
static bool hasNext(Iterator iter);


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
    int arr[count];

    setToArr(set2, arr);

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set1->inner->capacity;
        insertNode(&set1->inner->bucket[indexBucket], arr[i], &set1->inner->count);
    }
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

bool containsIntSet(IntSet set, int num) {
    for (int i = 0; i < set->inner->capacity; ++i) {
        if(isContains(set->inner->bucket[i], num))
            return true;
    }

    return false;
}

bool containsAllIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set2->inner->count > set1->inner->count) return false;
    if (isEmptyIntSet(set2)) return true;

    int count2 = set2->inner->count;
    int arr2[count2];
    setToArr(set2, arr2);

    int count1 = set1->inner->count;
    int arr1[count1];
    toArrAndSort(set1, arr1);

    for (int i = 0; i < count2; ++i) {
        if(!binarySearch(arr2[i], arr1, count1))
            return false;
    }

    return  true;
}

bool containsAnyIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set2->inner->count > set1->inner->count) return false;

    int count2 = set2->inner->count;
    int arr2[count2];
    setToArr(set2, arr2);

    int count1 = set1->inner->count;
    int arr1[count1];
    toArrAndSort(set1, arr1);

    for (int i = 0; i < count2; ++i) {
        if(binarySearch(arr2[i], arr1, count1))
            return true;
    }

    return  false;
}

bool removeIntSet(IntSet set, int num) {
    for (int i = 0; i < set->inner->capacity; ++i) {
        IntNode previous = set->inner->bucket[i];
        bool found = false;
        removeNode(&set->inner->bucket[i], &previous, num, &found);
        if (found)
            set->inner->count--;
    }

    return true;
}

bool removeAllIntSet(IntSet set1, IntSet set2) {
    int arr[set2->inner->count];
    setToArr(set2, arr);

    for (int i = 0; i < set2->inner->count; ++i) {
        removeIntSet(set1, arr[i]);
    }

    return true;
}

bool isEmptyIntSet(IntSet set) {
    return set == NULL || set->inner->count == 0;
}

bool isEqualsIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set1->inner->count != set2->inner->count) return false;

    int arr1[set1->inner->count];
    int arr2[set2->inner->count];

    toArrAndSort(set1, arr1);
    toArrAndSort(set2, arr2);

    for (int i = 0; i < set1->inner->count; ++i) {
        if (compareInt(arr1[i], arr2[i]) != 0)
            return false;
    }

    return true;
}

IntSet emptyIfNullIntSet(IntSet set) {
    if (set == NULL) {
        IntSet temp = newIntSet(temp);
        return temp;
    }

    return set;
}

Iterator iteratorIntSet(IntSet list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->inner->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = INT_SET;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

int sizeIntSet(IntSet set) {
    return set->inner->count;
}

void printIntSet(IntSet set) {
    if (set == NULL || set->inner == NULL) {
        printf("%s", "[]\n");
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
    free((*set)->inner);
    free(*set);
    *set = NULL;
}

// ===================== private funcs =======================

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

static int compareqsort(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

static bool binarySearch(int elem, const int* arr, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (elem < arr[middle])
            high = middle - 1;
        else if (elem > arr[middle])
            low = middle + 1;
        else
            return true;
    }
    return false;
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

    int arr[count];
    setToArr(set, arr);

    set->inner->capacity *= 2;
    set->inner->count = 0;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set->inner->capacity;
        insertNode(&set->inner->bucket[indexBucket], arr[i], &set->inner->count);
    }

    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void copyValuesToArr(IntNode node, int* arr, int* index) {
    if (node != NULL) {
        copyValuesToArr(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArr(node->right, arr, index);
    }
}

static IntNode findNode(IntNode* node, IntNode* previous) {
    if ((*node)->right == NULL) {
        IntNode temp = *node;
        (*previous)->right = NULL;
        return temp;
    }

    return findNode(&(*node)->right, &(*node));
}

static void removeNode(IntNode* node, IntNode* previous, int num, bool* found) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareInt(num, (*node)->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    IntNode temp = *node;
                    *node = NULL;
                    free(temp);
                    *found = true;
                    return;
                }

                IntNode temp = *node;
                if (compareInt((*node)->data, (*previous)->data) == -1)
                    (*previous)->left = NULL;
                else
                    (*previous)->right = NULL;

                free(temp);
                *found = true;
                return;
            }

            if (((*node)->left != NULL && (*node)->right == NULL) || ((*node)->left == NULL && (*node)->right != NULL)) {
                if (isRoot(node, previous)) {
                    IntNode temp = *node;
                    *node = (*node)->left != NULL ? (*node)->left : (*node)->right;
                    free(temp);
                    *found = true;
                    return;
                }

                IntNode temp = *node;
                if (compareInt((*node)->data, (*previous)->data) == -1) {
                    (*previous)->left = (*node)->left != NULL ? (*node)->left : (*node)->right;
                } else {
                    (*previous)->right = (*node)->left != NULL ? (*node)->left : (*node)->right;
                }

                free(temp);
                *found = true;
                return;
            }

            if ((*node)->right != NULL && (*node)->left != NULL) {
                IntNode temp = *node;
                IntNode left = (*node)->left;
                IntNode right = (*node)->right;


                *node = findNode(&temp->left, &temp);
                (*node)->right = right;
                temp->left = NULL;
                temp->right = NULL;

                // if remove root node
                if (isRoot(&temp, previous)) {
                    if ((*node)->left == NULL)
                        (*node)->left = left;
                    else
                        (*node)->left->left = left;
                }

                free(temp);
                *found = true;
                return;
            }
        } else {
            removeNode(&(*node)->left, &(*node), num, found);
            removeNode(&(*node)->right, &(*node), num, found);
        }

        return;
    }
}

// служебная функция для вывода дерева
void outputTree(IntNode node, int* counter) {
    if (node != NULL) {
        ++(*counter);
        outputTree(node->right, counter);
        for (int i = 0; i < *counter * 3; ++i)
            printf("  ");
        printf("%d\n", node->data);
        //--(*counter);
        outputTree(node->left, counter);
        --(*counter);
    }
}

void printTree(IntSet set) {
    int counter = 0;
    outputTree(set->inner->bucket[0], &counter);
}

static void setToArr(IntSet set, int* arr) {
    int index = 0;
    for (int i = 0; i < set->inner->capacity; ++i) {
        copyValuesToArr(set->inner->bucket[i], arr, &index);
    }
}

static void deleteNodes(NodeInt** buckets, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (buckets[i] != NULL)
            deleteInOrder(buckets[i]);
    }
}

static void deleteInOrder(IntNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    free(node);
}

static bool isContains(IntNode node, int num) {
    if (node != NULL) {
        isContains(node->left, num);
        if (compareInt(node->data, num) == 0)
            return true;
        isContains(node->right, num);
    }
    return false;
}

static void toArrAndSort(IntSet set, int* arr) {
    setToArr(set, arr);
    qsort(arr, set->inner->count, sizeof(int), compareqsort);
}

static bool isRoot(IntNode* node, IntNode* previous) {
    return (*node)->data == (*previous)->data;
}