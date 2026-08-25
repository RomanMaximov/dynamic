//
// Created by Roman Maximov on 10.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "doubleset.h"
#include "../util/setutil.h"

#define ACCURACY 0.000000001

typedef struct NodeSetDouble {
    double data;
    struct NodeSetDouble* left;
    struct NodeSetDouble* right;
} NodeSetDouble;

// Set data encapsulation
typedef struct InnerDoubleSet {
    int count;
    int capacity;
    int capacityCounter;
    struct NodeSetDouble** bucket;
} InnerDoubleSet;

typedef SetDouble* DoubleSet;
typedef NodeSetDouble* DoubleSetNode;

// prototypes private funcs
static DoubleSetNode createNode(double num);
static int compareDouble(double elem1, double elem2);
static void insertNode(NodeSetDouble** node, NodeSetDouble** previous, double num, int* counter, int* capacityCounter);
static void printInOrder(DoubleSetNode node, int* counter);
static bool isCapacityFull(DoubleSet set);
static void increaseCapacity(DoubleSet set);
static void increaseCapacityForAddAll(DoubleSet set, int newSize);
static void copyValuesToArr(DoubleSetNode node, double* arr, int* index);
static void setToArr(DoubleSet set, double* arr);
static void deleteNodes(NodeSetDouble** buckets, int capacity);
static void deleteInOrder(DoubleSetNode node);
static void removeNode(DoubleSetNode* node, DoubleSetNode* previous, double num, bool* found, int* capacityCounter);
static DoubleSetNode findNode(DoubleSetNode* node, DoubleSetNode* previous);
static bool isRoot(DoubleSetNode* node, DoubleSetNode* previous);
static int hashDouble(double value);
static  void toStringInOrder(DoubleSetNode node, int* counter, char* text, int* count);
static bool containsKeyDouble(DoubleSet set, double num);


void addDoubleSet(DoubleSet set, double num) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = hashDouble(num) % set->pf->capacity;
    NodeSetDouble* previous = set->pf->bucket[indexBucket];
    insertNode(&set->pf->bucket[indexBucket], &previous, num, &set->pf->count, &set->pf->capacityCounter);
}

void addAllDoubleSet(DoubleSet set, void* source) {
    if (set == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;
    if (ctx->type == DOUBLE_LIST) {
        DoubleList from = (DoubleList) ctx->collection;
        increaseCapacityForAddAll(set, from->pf->count);
        for (int i = 0; i < from->pf->count; ++i) {
            addDoubleSet(set, from->pf->data[i]);
        }
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList from = (DoubleLinkedList) ctx->collection;
        DoubleNode current = from->pf->begin;
        increaseCapacityForAddAll(set, from->pf->count);
        while (current != NULL) {
            addDoubleSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet from = (DoubleSet) ctx->collection;
        double arr[from->pf->count];
        setToArr(from, arr);
        increaseCapacityForAddAll(set, from->pf->count);
        for (int i = 0; i < from->pf->count; ++i)
            addDoubleSet(set, arr[i]);
    }
}

void clearDoubleSet(DoubleSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));
}

bool containsDoubleSet(DoubleSet set, double num) {
    return containsKeyDouble(set, num);
}

bool containsAllDoubleSet(DoubleSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        if (list2->pf->count > set->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyDouble(set, list2->pf->data[i])) {
                return false;
            }
        }
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        if (list2->pf->count > set->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        DoubleNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyDouble(set, current->data)) {
                return false;
            }
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count > set->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        DoubleList listFrom = pr_initLd_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (!containsKeyDouble(set, listFrom->pf->data[i])) {
                return false;
            }
        }
        listFrom->delete(&listFrom);
    }

    return  true;
}

bool containsAnyDoubleSet(DoubleSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyDouble(set, list2->pf->data[i])) {
                return true;
            }
        }
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        DoubleNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyDouble(set, current->data)) {
                return true;
            }
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        DoubleList listFrom = pr_initLd_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (containsKeyDouble(set, listFrom->pf->data[i])) {
                return true;
            }
        }
        listFrom->delete(&listFrom);
    }

    return  false;
}

bool removeDoubleSet(DoubleSet set, double num) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        DoubleSetNode previous = set->pf->bucket[i];
        bool found = false;
        removeNode(&set->pf->bucket[i], &previous, num, &found, &set->pf->capacityCounter);
        if (found)
            set->pf->count--;
    }

    return true;
}

bool removeAllDoubleSet(DoubleSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    DoubleSet tempList;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList listFrom = (DoubleList) ctx->collection;
        if (listFrom->pf->count == 0) return true;

        for (int i = 0; i < listFrom->pf->count; ++i) {
            removeDoubleSet(set, listFrom->pf->data[i]);
        }
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList listFrom = (DoubleLinkedList) ctx->collection;
        if (listFrom->pf->count == 0) return true;

        DoubleNode current = listFrom->pf->begin;
        while (current != NULL) {
            removeDoubleSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count == 0) return true;

        double* arr = malloc(setFrom->pf->count * sizeof(double));
        setToArr(setFrom, arr);
        for (int i = 0; i < setFrom->pf->count; ++i) {
            removeDoubleSet(set, arr[i]);
        }
        free(arr);
    }

    return true;
}

DoubleSet subtractDoubleSet(DoubleSet set, void* source) {
    if (isEmptyDoubleSet(set)) {
        DoubleSet temp = NULL;
        return pr_initSd_(temp, NULL);
    }

    if (source == NULL) {
        DoubleSet temp = pr_initSd_(temp, set->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    DoubleSet tempSet = pr_initSd_(tempSet, NULL);

    if (ctx->type == DOUBLE_LIST) {
        DoubleList listFrom = (DoubleList) ctx->collection;
        if (listFrom->pf->count == 0) {
            DoubleSet temp = pr_initSd_(temp, set->values);
            return temp;
        }

        DoubleSet setFrom = pr_initSd_(setFrom, listFrom->values);
        double* arr = malloc(set->pf->count * sizeof(double));
        setToArr(set, arr);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, arr[i]))
                tempSet->add(tempSet, arr[i]);
        }

        setFrom->delete(&setFrom);
        free(arr);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list = (DoubleLinkedList) ctx->collection;
        if (list->pf->count == 0) {
            DoubleSet temp = pr_initSd_(temp, set->values);
            return temp;
        }

        DoubleSet setFrom = pr_initSd_(setFrom, list->values);
        double* arr = malloc(set->pf->count * sizeof(double));
        setToArr(set, arr);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, arr[i]))
                tempSet->add(tempSet, arr[i]);
        }

        setFrom->delete(&setFrom);
        free(arr);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            DoubleSet temp = pr_initSd_(temp, set->values);
            return temp;
        }

        double* arr = malloc(set->pf->count * sizeof(double));
        setToArr(set, arr);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, arr[i]))
                tempSet->add(tempSet, arr[i]);
        }

        free(arr);
    }

    return tempSet;
}

bool isEmptyDoubleSet(DoubleSet set) {
    return set == NULL || set->pf->count == 0;
}

int sizeDoubleSet(DoubleSet set) {
    return set->pf->count;
}

string toStrDoubleSet(DoubleSet set) {
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

void printDoubleSet(DoubleSet set) {
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

void deleteDoubleSet(DoubleSet* set) {
    if (set == NULL || *set == NULL || (*set)->pf == NULL) return;

    if ((*set)->values != NULL) free((*set)->values);

    if ((*set)->pf->bucket != NULL) {
        deleteNodes((*set)->pf->bucket, (*set)->pf->capacity);
        free((*set)->pf->bucket);
    }
    free((*set)->pf);
    free(*set);
    *set = NULL;
}

// ===================== private funcs =======================

static bool isCapacityFull(DoubleSet set) {
    int fullCapacity = set->pf->capacity / 8 * 6;
    return set->pf->capacityCounter >= fullCapacity;
}

static void increaseCapacity(DoubleSet set) {
    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeSetDouble** temp = set->pf->bucket;

    double arr[count];
    setToArr(set, arr);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));

    for (int i = 0; i < count; ++i) {
        int indexBucket = hashDouble(arr[i]) % set->pf->capacity;
        NodeSetDouble* previous = set->pf->bucket[indexBucket];
        insertNode(&set->pf->bucket[indexBucket], &previous, arr[i], &set->pf->count, &set->pf->capacityCounter);
    }

    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void increaseCapacityForAddAll(DoubleSet set, int newSize) {
    if (newSize < (set->pf->capacity - set->pf->capacityCounter)) return;

    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeSetDouble** temp = set->pf->bucket;

    double* arr = malloc(count * sizeof(double));
    setToArr(set, arr);

    set->pf->capacity = (int)(set->pf->capacity + newSize + (newSize * 0.5));
    set->pf->count = 0;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));

    for (int i = 0; i < count; ++i) {
        int indexBucket = hashDouble(arr[i]) % set->pf->capacity;
        NodeSetDouble* previous = set->pf->bucket[indexBucket];
        insertNode(&set->pf->bucket[indexBucket], &previous, arr[i], &set->pf->count, &set->pf->capacityCounter);
    }

    deleteNodes(temp, oldCapacity);
    free(arr);
    free(temp);
}

static void insertNode(NodeSetDouble** node, NodeSetDouble** previous, double num, int* counter, int* capacityCounter) {
    if (*node == NULL) {
        if (*node == NULL && *previous == NULL) (*capacityCounter)++;
        *node = createNode(num);
        (*counter)++;
    } else {
        int cmp = compareDouble(num, (*node)->data);
        if (cmp == 0) {
            return;
        } else if (cmp < 0) {
            insertNode(&((*node)->left), &(*previous), num, counter, capacityCounter);
        } else {
            insertNode(&((*node)->right), &(*previous), num, counter, capacityCounter);
        }
    }
}

static DoubleSetNode createNode(double num) {
    DoubleSetNode node = malloc(sizeof(NodeSetDouble));
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

static void deleteNodes(NodeSetDouble** buckets, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (buckets[i] != NULL)
            deleteInOrder(buckets[i]);
    }
}

static void deleteInOrder(DoubleSetNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    free(node);
}

static void setToArr(DoubleSet set, double* arr) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToArr(set->pf->bucket[i], arr, &index);
    }
}

static void copyValuesToArr(DoubleSetNode node, double* arr, int* index) {
    if (node != NULL) {
        copyValuesToArr(node->left, arr, index);
        arr[(*index)++] = node->data;
        copyValuesToArr(node->right, arr, index);
    }
}

static int compareqsort(const void* elem1, const void* elem2) {
    if (fabs(*(double*)elem1 - *(double*)elem2) < ACCURACY)
        return 0;
    else if (*(double*)elem1 > *(double*)elem2)
        return 1;
    else
        return -1;
}

static bool isRoot(DoubleSetNode* node, DoubleSetNode* previous) {
    return (*node)->data == (*previous)->data;
}

static void removeNode(DoubleSetNode* node, DoubleSetNode* previous, double num, bool* found, int* capacityCounter) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareDouble(num, (*node)->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    DoubleSetNode temp = *node;
                    *node = NULL;
                    free(temp);
                    (*capacityCounter)--;
                    *found = true;
                    return;
                }

                DoubleSetNode temp = *node;
                if (compareDouble((*node)->data, (*previous)->data) == -1)
                    (*previous)->left = NULL;
                else
                    (*previous)->right = NULL;

                free(temp);
                *found = true;
                return;
            }

            if (((*node)->left != NULL && (*node)->right == NULL) || ((*node)->left == NULL && (*node)->right != NULL)) {
                if (isRoot(node, previous)) {
                    DoubleSetNode temp = *node;
                    *node = (*node)->left != NULL ? (*node)->left : (*node)->right;
                    free(temp);
                    *found = true;
                    return;
                }

                DoubleSetNode temp = *node;
                if (compareDouble((*node)->data, (*previous)->data) == -1) {
                    (*previous)->left = (*node)->left != NULL ? (*node)->left : (*node)->right;
                } else {
                    (*previous)->right = (*node)->left != NULL ? (*node)->left : (*node)->right;
                }

                free(temp);
                *found = true;
                return;
            }

            if ((*node)->right != NULL && (*node)->left != NULL) {
                DoubleSetNode temp = *node;
                DoubleSetNode left = (*node)->left;
                DoubleSetNode right = (*node)->right;


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
            removeNode(&(*node)->left, &(*node), num, found, capacityCounter);
            removeNode(&(*node)->right, &(*node), num, found, capacityCounter);
        }

        return;
    }
}

static DoubleSetNode findNode(DoubleSetNode* node, DoubleSetNode* previous) {
    if ((*node)->right == NULL) {
        DoubleSetNode temp = *node;
        (*previous)->right = NULL;
        return temp;
    }

    return findNode(&(*node)->right, &(*node));
}

static  void printInOrder(DoubleSetNode node, int* counter) {
    if (node != NULL) {
        printInOrder(node->left, counter);
        printf("%f", node->data);
        if (*counter - 1 != 0) {
            printf("%s", ", ");
            --(*counter);
        }
        printInOrder(node->right, counter);
    }
}

static  void toStringInOrder(DoubleSetNode node, int* counter, char* text, int* count) {
    if (node != NULL) {
        toStringInOrder(node->left, counter, text, count);
        sprintf(&text[strlen(text)], "%.9f", node->data);
        if (strlen(text) > (int)(*count / 8 * 7)) {
            *count *= 2;
            text = realloc(text, *count * sizeof(char));
            assert(text != NULL);
        }

        if (*counter - 1 != 0) {
            sprintf(&text[strlen(text)], "%s", ",");
        }
        --(*counter);
        toStringInOrder(node->right, counter, text, count);
    }
}

static int hashDouble(double value) {
    uint64_t intRepresentation;
    memcpy(&intRepresentation, &value, sizeof(double));
    intRepresentation = (intRepresentation ^ (intRepresentation >> 32)) * 0x45d9f3b;
    intRepresentation = (intRepresentation ^ (intRepresentation >> 16)) * 0x45d9f3b;
    intRepresentation = intRepresentation ^ (intRepresentation >> 16);
    return abs((int)intRepresentation);
}

static bool findKey(NodeSetDouble** node, double num, bool* found) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareDouble(num, (*node)->data);
    if (cmp == 0) {
        *found = true;
        return true;
    } else if (cmp < 0) {
        findKey(&((*node)->left), num, found);
    } else {
        findKey(&((*node)->right), num, found);
    }
    return *found;
}

static bool containsKeyDouble(DoubleSet set, double num) {
    bool found = false;
    int indexBucket = (int) (hashDouble(num) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], num, &found);
}