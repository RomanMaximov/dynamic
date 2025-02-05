//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intset.h"
#include "../util/setutil.h"

typedef struct NodeSetInt {
    int data;
    struct NodeSetInt* left;
    struct NodeSetInt* right;
} NodeSetInt;

// Set data encapsulation
typedef struct InnerIntSet {
    int count;
    int capacity;
    NodeSetInt** bucket;
} InnerIntSet;

typedef SetInt* IntSet;
typedef NodeSetInt* IntSetNode;

// prototypes private funcs
static IntSetNode createNode(int num);
static int compareInt(int elem1, int elem2);
static void insertNode(NodeSetInt** node, int num, int* counter);
static void printInOrder(IntSetNode node, int* counter);
static bool isCapacityFull(IntSet set);
static unsigned long long hashCode(int key);
static void increaseCapacity(IntSet set);
static void copyValuesToArr(IntSetNode node, int* arr, int* index);
static void setToArr(IntSet set, int* arr);
static void deleteNodes(NodeSetInt** buckets, int capacity);
static void deleteInOrder(IntSetNode node);
static bool isContains(IntSetNode node, int num);
static int compareqsort(const void* elem1, const void* elem2);
static bool binarySearch(int elem, const int* arr, int high);
static void toArrAndSort(IntSet set, int* arr);
static void removeNode(IntSetNode* node, IntSetNode* previous, int num, bool* found);
static IntSetNode findNode(IntSetNode* node, IntSetNode* previous);
static bool isRoot(IntSetNode* node, IntSetNode* previous);
static  void toStringInOrder(IntSetNode node, int* counter, char* text, int* count);
static bool hasNext(Iterator iter);
static bool containsKeyInt(IntSet set, int num);


void addIntSet(IntSet set, int num) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    insertNode(&set->pf->bucket[indexBucket], num, &set->pf->count);
}

void addAllIntSet(IntSet set, void* source) {
    if (set == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;
    if (ctx->type == INT_LIST) {
        IntList from = (IntList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i) {
            addIntSet(set, from->pf->data[i]);
        }
    }

    if (ctx->type == INT_LL) {
        IntLinkedList from = (IntLinkedList) ctx->collection;
        IntNode current = from->pf->begin;
        while (current != NULL) {
            addIntSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == INT_SET) {
        IntSet from = (IntSet) ctx->collection;
        int arr[from->pf->count];
        setToArr(from, arr);
        for (int i = 0; i < from->pf->count; ++i)
            addIntSet(set, arr[i]);
    }
}

void clearIntSet(IntSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeSetInt*));
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

    for (int i = 0; i < count2; ++i) {
        if (!containsKeyInt(set1, arr2[i]))
            return false;
    }

    return  true;
}

bool containsAnyIntSet(IntSet set1, IntSet set2) {
    if (set1 == NULL || set2 == NULL || set2->pf->count > set1->pf->count) return false;

    int count2 = set2->pf->count;
    int arr2[count2];
    setToArr(set2, arr2);

    for (int i = 0; i < count2; ++i) {
        if(containsKeyInt(set1, arr2[i]))
            return true;
    }

    return  false;
}

bool removeIntSet(IntSet set, int num) {
    if (set == NULL) return false;

    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    IntSetNode previous = set->pf->bucket[indexBucket];
    bool found = false;
    removeNode(&set->pf->bucket[indexBucket], &previous, num, &found);
    if (found)
        set->pf->count--;

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

string toStrIntSet(IntSet set) {
    if (set == NULL || set->pf == NULL || set->pf->bucket == NULL) {
        printf("%s", "[]\n");
        return NULL;
    }

    char* text = NULL;
    if (set->pf->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return strOf(text);
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");

    int counter = set->pf->count;
    for (int i = 0; i < set->pf->capacity; ++i) {
        toStringInOrder(set->pf->bucket[i], &counter, text, &count);
    }

    strcat(text, "]");
    string s = strOf(text);
    free(text);

    return s;
}

void printIntSet(IntSet set) {
    if (set == NULL || set->pf == NULL || set->pf->bucket == NULL) {
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

static  void printInOrder(IntSetNode node, int* counter) {
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

static void insertNode(NodeSetInt** node, int num, int* counter) {
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

static IntSetNode createNode(int num) {
    IntSetNode node = malloc(sizeof(NodeSetInt));
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
    NodeSetInt** temp = set->pf->bucket;

    int arr[count];
    setToArr(set, arr);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeSetInt*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = (int) (hashCode(arr[i]) % set->pf->capacity);
        insertNode(&set->pf->bucket[indexBucket], arr[i], &set->pf->count);
    }

    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void copyValuesToArr(IntSetNode node, int* arr, int* index) {
    if (node != NULL) {
        copyValuesToArr(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArr(node->right, arr, index);
    }
}

static IntSetNode findNode(IntSetNode* node, IntSetNode* previous) {
    if ((*node)->right == NULL) {
        IntSetNode temp = *node;
        (*previous)->right = NULL;
        return temp;
    }

    return findNode(&(*node)->right, &(*node));
}

static void removeNode(IntSetNode* node, IntSetNode* previous, int num, bool* found) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareInt(num, (*node)->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    IntSetNode temp = *node;
                    *node = NULL;
                    free(temp);
                    *found = true;
                    return;
                }

                IntSetNode temp = *node;
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
                    IntSetNode temp = *node;
                    *node = (*node)->left != NULL ? (*node)->left : (*node)->right;
                    free(temp);
                    *found = true;
                    return;
                }

                IntSetNode temp = *node;
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
                IntSetNode temp = *node;
                IntSetNode left = (*node)->left;
                IntSetNode right = (*node)->right;


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
void outputTree(IntSetNode node, int* counter) {
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

static void deleteNodes(NodeSetInt** buckets, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (buckets[i] != NULL)
            deleteInOrder(buckets[i]);
    }
}

static void deleteInOrder(IntSetNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    free(node);
}

static bool isContains(IntSetNode node, int num) {
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

static bool isRoot(IntSetNode* node, IntSetNode* previous) {
    return (*node)->data == (*previous)->data;
}

static  void toStringInOrder(IntSetNode node, int* counter, char* text, int* count) {
    if (node != NULL) {
        toStringInOrder(node->left, counter, text, count);
        sprintf(&text[strlen(text)], "%d,", node->data);
        if (strlen(text) > (int)(*count / 8 * 7)) {
            *count *= 2;
            text = realloc(text, *count * sizeof(char));
        }

        if (*counter - 1 != 0) {
            printf("%s", ",");
            --(*counter);
        }
        toStringInOrder(node->right, counter, text, count);
    }
}

static unsigned long long hashCode(int key) {
    unsigned long long tempKey = (unsigned long long) key;
    tempKey = ((tempKey >> 4) ^ tempKey) * 0x1b873593ULL;
    return tempKey;
}

static bool findKey(NodeSetInt** node, int num) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareInt(num, (*node)->data);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        findKey(&((*node)->left), num);
    } else {
        findKey(&((*node)->right), num);
    }
    return false;
}

static bool containsKeyInt(IntSet set, int num) {
    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], num);
}