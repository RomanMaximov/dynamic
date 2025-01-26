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

    int indexBucket = num % set->pf->capacity;
    insertNode(&set->pf->bucket[indexBucket], num, &set->pf->count);
}

void addAllIntElemSet(IntSet set1, IntSet set2) {
    if (set2 == NULL) return;

    if (isCapacityFull(set1))
        increaseCapacity(set1);

    int count = set2->pf->count;
    int arr[count];

    setToArr(set2, arr);

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set1->pf->capacity;
        insertNode(&set1->pf->bucket[indexBucket], arr[i], &set1->pf->count);
    }
}

void clearIntSet(IntSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;
}

bool containsIntSet(IntSet set, int num) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        if(isContains(set->pf->bucket[i], num))
            return true;
    }

    return false;
}

bool containsAllIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set2->pf->count > set1->pf->count) return false;
    if (isEmptyIntSet(set2)) return true;

    int count2 = set2->pf->count;
    int arr2[count2];
    setToArr(set2, arr2);

    int count1 = set1->pf->count;
    int arr1[count1];
    toArrAndSort(set1, arr1);

    for (int i = 0; i < count2; ++i) {
        if(!binarySearch(arr2[i], arr1, count1))
            return false;
    }

    return  true;
}

bool containsAnyIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set2->pf->count > set1->pf->count) return false;

    int count2 = set2->pf->count;
    int arr2[count2];
    setToArr(set2, arr2);

    int count1 = set1->pf->count;
    int arr1[count1];
    toArrAndSort(set1, arr1);

    for (int i = 0; i < count2; ++i) {
        if(binarySearch(arr2[i], arr1, count1))
            return true;
    }

    return  false;
}

bool removeIntSet(IntSet set, int num) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        IntNode previous = set->pf->bucket[i];
        bool found = false;
        removeNode(&set->pf->bucket[i], &previous, num, &found);
        if (found)
            set->pf->count--;
    }

    return true;
}

bool removeAllIntSet(IntSet set1, IntSet set2) {
    int arr[set2->pf->count];
    setToArr(set2, arr);

    for (int i = 0; i < set2->pf->count; ++i) {
        removeIntSet(set1, arr[i]);
    }

    return true;
}

bool isEmptyIntSet(IntSet set) {
    return set == NULL || set->pf->count == 0;
}

bool isEqualsIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set1->pf->count != set2->pf->count) return false;

    int arr1[set1->pf->count];
    int arr2[set2->pf->count];

    toArrAndSort(set1, arr1);
    toArrAndSort(set2, arr2);

    for (int i = 0; i < set1->pf->count; ++i) {
        if (compareInt(arr1[i], arr2[i]) != 0)
            return false;
    }

    return true;
}

Iterator iteratorIntSet(IntSet list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->pf->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = INT_SET;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

int sizeIntSet(IntSet set) {
    return set->pf->count;
}

void printIntSet(IntSet set) {
    if (set == NULL || set->pf == NULL) {
        printf("%s", "[]\n");
        return;
    }

    printf("%s", "[");

    int counter = set->pf->count;
    for (int i = 0; i < set->pf->capacity; ++i) {
        printInOrder(set->pf->bucket[i], &counter);
    }

    printf("%s", "]");
    puts("");
}

void deleteIntSet(IntSet* set) {
    if (set == NULL || *set == NULL || (*set)->pf == NULL) return;

    if ((*set)->pf->bucket != NULL) {
        deleteNodes((*set)->pf->bucket, (*set)->pf->capacity);
        free((*set)->pf->bucket);
    }
    free((*set)->pf);
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
    int fullCapacity = set->pf->capacity / 8 * 6;
    for (int i = 0; i < set->pf->capacity; ++i) {
        if (set->pf->bucket[i] != NULL) ++counter;
    }

    return counter >= fullCapacity;
}

static void increaseCapacity(IntSet set) {
    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeInt** temp = set->pf->bucket;

    int arr[count];
    setToArr(set, arr);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = arr[i] % set->pf->capacity;
        insertNode(&set->pf->bucket[indexBucket], arr[i], &set->pf->count);
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
    outputTree(set->pf->bucket[0], &counter);
}

static void setToArr(IntSet set, int* arr) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToArr(set->pf->bucket[i], arr, &index);
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
    qsort(arr, set->pf->count, sizeof(int), compareqsort);
}

static bool isRoot(IntNode* node, IntNode* previous) {
    return (*node)->data == (*previous)->data;
}