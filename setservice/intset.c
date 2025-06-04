//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    struct NodeSetInt** bucket;
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
static void removeNode(IntSetNode* node, IntSetNode* previous, int num, bool* found);
static IntSetNode findNode(IntSetNode* node, IntSetNode* previous);
static bool isRoot(IntSetNode* node, IntSetNode* previous);
static  void toStringInOrder(IntSetNode node, int* counter, char* text, int* count);
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
    return containsKeyInt(set, num);
}

bool containsAllIntSet(IntSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list = (IntList) ctx->collection;
        if (list->pf->count > set->pf->count)
            return false;

        if (list->pf->count == 0) return true;

        for (int i = 0; i < list->pf->count; ++i) {
            if (!containsKeyInt(set, list->pf->data[i])) {
                return false;
            }
        }
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list = (IntLinkedList) ctx->collection;
        if (list->pf->count > set->pf->count)
            return false;

        if (list->pf->count == 0) return true;

        IntNode current = list->pf->begin;
        while (current != NULL) {
            if (!containsKeyInt(set, current->data)) {
                return false;
            }
            current = current->next;
        }
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count > set->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (!containsKeyInt(set, listFrom->pf->data[i])) {
                return false;
            }
        }
        listFrom->delete(&listFrom);
    }

    return  true;
}

bool containsAnyIntSet(IntSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyInt(set, list2->pf->data[i])) {
                return true;
            }
        }
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        IntNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyInt(set, current->data)) {
                return true;
            }
            current = current->next;
        }
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (containsKeyInt(set, listFrom->pf->data[i])) {
                return true;
            }
        }
        listFrom->delete(&listFrom);
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

bool removeAllIntSet(IntSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    IntSet tempList;

    if (ctx->type == INT_LIST) {
        IntList list = (IntList) ctx->collection;
        tempList = subtractIntSet(set, list->values);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list = (IntLinkedList) ctx->collection;
        tempList = subtractIntSet(set, list->values);
    }

    if (ctx->type == INT_SET) {
        IntSet set2 = (IntSet) ctx->collection;
        tempList = subtractIntSet(set, set2->values);
    }

    set->delete(&set);
    set = tempList;

    return true;
}

IntSet subtractIntSet(IntSet set, void* source) {
    if (isEmptyIntSet(set)) {
        IntSet temp = NULL;
        return pr_initSi_(temp, NULL);
    }

    if (source == NULL) {
        IntSet temp = pr_initSi_(temp, set->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    IntSet tempSet = pr_initSi_(tempSet, set->values);

    if (ctx->type == INT_LIST) {
        IntList list = (IntList) ctx->collection;
        if (list->pf->count == 0) {
            IntSet temp = pr_initSi_(temp, set->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, list->values);
        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            int num = nextInt(iter);
            if (!setFrom->contains(setFrom, num))
                tempSet->removeElem(tempSet, num);
        }

        setFrom->delete(&setFrom);
        deleteItr(&iter);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list = (IntLinkedList) ctx->collection;
        if (list->pf->count == 0) {
            IntSet temp = pr_initSi_(temp, set->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, list->values);
        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            int num = nextInt(iter);
            if (!setFrom->contains(setFrom, num))
                tempSet->removeElem(tempSet, num);
        }

        setFrom->delete(&setFrom);
        deleteItr(&iter);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            IntSet temp = pr_initSi_(temp, set->values);
            return temp;
        }

        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            int num = nextInt(iter);
            if (!setFrom->contains(setFrom, num))
                tempSet->removeElem(tempSet, num);
        }

        deleteItr(&iter);
    }

    return tempSet;
}

bool isEmptyIntSet(IntSet set) {
    return set == NULL || set->pf->count == 0;
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

// debugging func for tree
void outputTree(IntSetNode node, int* counter) {
    if (node != NULL) {
        ++(*counter);
        outputTree(node->right, counter);
        for (int i = 0; i < *counter * 3; ++i)
            printf("  ");
        printf("%d\n", node->data);
        outputTree(node->left, counter);
        --(*counter);
    }
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
            assert(text != NULL);
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

static bool findKey(NodeSetInt** node, int num, bool* found) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareInt(num, (*node)->data);
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

static bool containsKeyInt(IntSet set, int num) {
    bool found = false;
    int indexBucket = (int) (hashCode(num) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], num, &found);
}