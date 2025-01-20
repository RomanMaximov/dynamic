//
// Created by Roman Maximov on 11.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "strset.h"

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

typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;

typedef struct InnerStrList {
    int count;
    String** str;
    int capacity;
} InnerStrList;

typedef SetStr* StrSet;
typedef NodeStr* StrNode;
typedef String* string;
typedef ArrayListStr* StrList;

// prototypes private funcs
static StrNode createNode(char* s);
static int hashString(const char* str);
static int compareCharStr(char* s1, char* s2);
static int compareStr(string s1, string s2);
static void insertNode(NodeStr** node, char* s, int* counter);
static void printInOrder(StrNode node, int* counter);
static bool isCapacityFull(StrSet set);
static void increaseCapacity(StrSet set);
static void copyValuesToList(StrNode node, StrList list);
static void setToArr(StrSet set, StrList list);
static void deleteNodes(NodeStr** buckets, int capacity);
static void deleteInOrder(StrNode node);
static bool isContains(StrNode node, string s);
static void quickSortStr(String** strList, int low, int high);
static bool binarySearch(string s, String** strList, int high);
static void toListAndSort(StrSet set, StrList list);
static void removeNode(StrNode* node, StrNode* previous, string s, bool* found);
static StrNode findNode(StrNode* node, StrNode* previous);
static bool isRoot(StrNode* node, StrNode* previous);
static bool hasNext(Iterator iter);


void addStrElemSet(StrSet set, string s) {
    if (s == NULL || s->pf->data == NULL) return;

    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
    insertNode(&set->pf->bucket[indexBucket], s->pf->data, &set->pf->count);
}

void addCharElemSet(StrSet set, char* s) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s) & 0x7FFFFFFF) % set->pf->capacity;
    insertNode(&set->pf->bucket[indexBucket], s, &set->pf->count);
}

void addAllStrElemSet(StrSet set1, StrSet set2) {
    if (set2 == NULL) return;

    if (isCapacityFull(set1))
        increaseCapacity(set1);

    int count = set2->pf->count;
    StrList list = newStrList(list);
    setToArr(set2, list);

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->pf->str[i]->pf->data) & 0x7FFFFFFF) % set1->pf->capacity;
        insertNode(&set1->pf->bucket[indexBucket], list->pf->str[i]->pf->data, &set1->pf->count);
    }

    deleteStrList(&list);
}

void clearStrSet(StrSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeStr*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;
}

bool containsStrSet(StrSet set, string s) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        if(isContains(set->pf->bucket[i], s))
            return true;
    }

    return false;
}

bool containsAllStrSet(StrSet set1, StrSet set2) {
    if (set1 == NULL || set2 == NULL || set2->pf->count > set1->pf->count) return false;
    if (isEmptyStrSet(set2)) return true;

    int count2 = set2->pf->count;
    StrList list2 = newStrList(list2);
    setToArr(set2, list2);

    int count1 = set1->pf->count;
    StrList list1 = newStrList(list1);
    toListAndSort(set1, list1);

    for (int i = 0; i < count2; ++i) {
        if(!binarySearch(list2->pf->str[i], list1->pf->str, count1))
            return false;
    }

    deleteStrList(&list1);
    deleteStrList(&list2);

    return  true;
}

bool containsAnyStrSet(StrSet set1, StrSet set2) {
    if (set1 == NULL || set2 == NULL || set2->pf->count > set1->pf->count) return false;

    int count2 = set2->pf->count;
    StrList list2 = newStrList(list2);
    setToArr(set2, list2);

    int count1 = set1->pf->count;
    StrList list1 = newStrList(list1);
    toListAndSort(set1, list1);

    for (int i = 0; i < count2; ++i) {
        if(binarySearch(list2->pf->str[i], list1->pf->str, count1)) {
            deleteStrList(&list1);
            deleteStrList(&list2);
            return true;
        }
    }

    deleteStrList(&list1);
    deleteStrList(&list2);

    return  false;
}

bool removeStrSet(StrSet set, string s) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        StrNode previous = set->pf->bucket[i];
        bool found = false;
        removeNode(&set->pf->bucket[i], &previous, s, &found);
        if (found)
            set->pf->count--;
    }

    return true;
}

bool removeAllStrSet(StrSet set1, StrSet set2) {
    StrList list2 = newStrList(list2);
    setToArr(set2, list2);

    for (int i = 0; i < set2->pf->count; ++i) {
        removeStrSet(set1, list2->pf->str[i]);
    }

    deleteStrList(&list2);

    return true;
}

bool isEmptyStrSet(StrSet set) {
    return set == NULL || set->pf->count == 0;
}

bool isEqualsStrSet(StrSet set1, StrSet set2) {
    if (set1 == NULL || set2 == NULL || set1->pf->count != set2->pf->count) return false;

    StrList list1 = newStrList(list1);
    StrList list2 = newStrList(list2);

    toListAndSort(set1, list1);
    toListAndSort(set2, list2);

    for (int i = 0; i < set1->pf->count; ++i) {
        if (compareCharStr(list1->pf->str[i]->pf->data, list2->pf->str[i]->pf->data) != 0)
            return false;
    }

    deleteStrList(&list1);
    deleteStrList(&list2);

    return true;
}

StrSet emptyIfNullStrSet(StrSet set) {
    if (set == NULL) {
        StrSet temp = newStrSet(temp);
        return temp;
    }

    return set;
}

Iterator iteratorStrSet(StrSet list) { // TODO принимать void* и преобразовывать к Collection
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->pf->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = STR_SET;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

int sizeStrSet(StrSet set) {
    return set->pf->count;
}

void printStrSet(StrSet set) {
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

void deleteStrSet(StrSet* set) {
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
    int fullCapacity = set->pf->capacity / 8 * 6;
    for (int i = 0; i < set->pf->capacity; ++i) {
        if (set->pf->bucket[i] != NULL) ++counter;
    }

    return counter >= fullCapacity;
}

static void increaseCapacity(StrSet set) {
    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeStr** temp = set->pf->bucket;

    StrList list = newStrList(list);
    setToArr(set, list);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeStr*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->pf->str[i]->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
        insertNode(&set->pf->bucket[indexBucket], list->pf->str[i]->pf->data, &set->pf->count);
    }

    deleteStrList(&list);
    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void setToArr(StrSet set, StrList list) {
    int index = 0;
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToList(set->pf->bucket[i], list);
    }
}

static void copyValuesToList(StrNode node, StrList list) {
    if (node != NULL) {
        copyValuesToList(node->left, list);
        addCharArrList(list, node->str->pf->data);
        copyValuesToList(node->right, list);
    }
}

static void insertNode(NodeStr** node, char* s, int* counter) {
    if (*node == NULL) {
        *node = createNode(s);
        (*counter)++;
    } else {
        int cmp = compareCharStr(s, (*node)->str->pf->data);
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
    node->str = strOf(s);
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

int compareCharStr(char* s1, char* s2) {
    return strcmp(s1, s2);
}

int compareStr(string s1, string s2) {
    return strcmp(s1->pf->data, s2->pf->data);
}

static bool isContains(StrNode node, string s) {
    if (node != NULL) {
        isContains(node->left, s);
        if (compareCharStr(node->str->pf->data, s->pf->data) == 0)
            return true;
        isContains(node->right, s);
    }
    return false;
}

static void toListAndSort(StrSet set, StrList list) {
    setToArr(set, list);
    quickSortStr(list->pf->str, 0, list->pf->count);
}

static void quickSortStr(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareStr(strList[i], strList[j]) > 0) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) > 0) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quickSortStr(strList, i + 1, high);
    if (low < j - 1)
        quickSortStr(strList, low, j);
}

static bool binarySearch(string s, String** strList, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (compareStr(s, strList[middle]) < 0)
            high = middle - 1;
        else if (compareStr(s, strList[middle]) > 0)
            low = middle + 1;
        else
            return true;
    }
    return false;
}

static void removeNode(StrNode* node, StrNode* previous, string s, bool* found) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareCharStr(s->pf->data, (*node)->str->pf->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    StrNode temp = *node;
                    *node = NULL;
                    deleteString(&temp->str);
                    free(temp);
                    *found = true;
                    return;
                }

                StrNode temp = *node;
                if (compareStr((*node)->str, (*previous)->str) == -1)
                    (*previous)->left = NULL;
                else
                    (*previous)->right = NULL;

                deleteString(&temp->str);
                free(temp);
                *found = true;
                return;
            }

            if (((*node)->left != NULL && (*node)->right == NULL) || ((*node)->left == NULL && (*node)->right != NULL)) {
                if (isRoot(node, previous)) {
                    StrNode temp = *node;
                    *node = (*node)->left != NULL ? (*node)->left : (*node)->right;
                    deleteString(&temp->str);
                    free(temp);
                    *found = true;
                    return;
                }

                StrNode temp = *node;
                if (compareStr((*node)->str, (*previous)->str) == -1) {
                    (*previous)->left = (*node)->left != NULL ? (*node)->left : (*node)->right;
                } else {
                    (*previous)->right = (*node)->left != NULL ? (*node)->left : (*node)->right;
                }

                deleteString(&temp->str);
                free(temp);
                *found = true;
                return;
            }

            if ((*node)->right != NULL && (*node)->left != NULL) {
                StrNode temp = *node;
                StrNode left = (*node)->left;
                StrNode right = (*node)->right;


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

                deleteString(&temp->str);
                free(temp);
                *found = true;
                return;
            }
        } else {
            removeNode(&(*node)->left, &(*node), s, found);
            removeNode(&(*node)->right, &(*node), s, found);
        }

        return;
    }
}

static StrNode findNode(StrNode* node, StrNode* previous) {
    if ((*node)->right == NULL) {
        StrNode temp = *node;
        (*previous)->right = NULL;
        return temp;
    }

    return findNode(&(*node)->right, &(*node));
}

static bool isRoot(StrNode* node, StrNode* previous) {
    return compareCharStr((*node)->str->pf->data, (*previous)->str->pf->data) == 0;
}

static  void printInOrder(StrNode node, int* counter) {
    if (node != NULL) {
        printInOrder(node->left, counter);
        printf("%s", node->str->pf->data);
        if (*counter - 1 != 0) {
            printf("%s", ", ");
            --(*counter);
        }
        printInOrder(node->right, counter);
    }
}