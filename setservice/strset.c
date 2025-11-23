//
// Created by Roman Maximov on 11.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strset.h"
#include "../util/setutil.h"

typedef struct NodeSetStr {
    string str;
    struct NodeSetStr* left;
    struct NodeSetStr* right;
} NodeSetStr;

// Set data encapsulation
typedef struct InnerStrSet {
    int count;
    int capacity;
    int capacityCounter;
    struct NodeSetStr** bucket;
} InnerStrSet;

// String data encapsulation
typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;

typedef SetStr* StrSet;
typedef NodeSetStr* StrSetNode;
typedef String* string;
typedef ArrayListStr* StrList;

// prototypes private funcs
static StrSetNode createNode(char* s);
static int hashString(const char* str);
static int compareCharStr(char* s1, char* s2);
static int compareStr(string s1, string s2);
static void insertNode(NodeSetStr** node, NodeSetStr** previous, char* s, int* counter, int* capacityCounter);
static void printInOrder(StrSetNode node, int* counter);
static bool isCapacityFull(StrSet set);
static void increaseCapacity(StrSet set);
static void increaseCapacityForAddAll(StrSet set, int newSize);
static void copyValuesToList(StrSetNode node, StrList list);
static void setToArr(StrSet set, StrList list);
static void deleteNodes(NodeSetStr** buckets, int capacity);
static void deleteInOrder(StrSetNode node);
static void quickSortStr(String** strList, int low, int high);
static void removeNode(StrSetNode* node, StrSetNode* previous, string s, bool* found, int* capacityCounter);
static StrSetNode findNode(StrSetNode* node, StrSetNode* previous);
static bool isRoot(StrSetNode* node, StrSetNode* previous);
static void toStringInOrder(StrSetNode node, int* counter, char* text, int* count);
static void checkCapacity(char* text, int* count, int strLength);
static bool containsKeyStr(StrSet set, string s);


void addStrSet(StrSet set, string s) {
    if (s == NULL || s->pf->data == NULL) return;

    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
    NodeSetStr* previous = set->pf->bucket[indexBucket];
    insertNode(&set->pf->bucket[indexBucket], &previous, s->pf->data, &set->pf->count, &set->pf->capacityCounter);
}

void addCharArrSet(StrSet set, char* s) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s) & 0x7FFFFFFF) % set->pf->capacity;
    NodeSetStr* previous = set->pf->bucket[indexBucket];
    insertNode(&set->pf->bucket[indexBucket], &previous, s, &set->pf->count, &set->pf->capacityCounter);
}

void addAllStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;
    if (ctx->type == STR_LIST) {
        StrList from = (StrList) ctx->collection;
        increaseCapacityForAddAll(set, from->pf->count);
        for (int i = 0; i < from->pf->count; ++i) {
            addStrSet(set, from->pf->data[i]);
        }
    }

    if (ctx->type == STR_LL) {
        StrLinkedList from = (StrLinkedList) ctx->collection;
        StrNode current = from->pf->begin;
        increaseCapacityForAddAll(set, from->pf->count);
        while (current != NULL) {
            addStrSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet from = (StrSet) ctx->collection;
        StrList list = pr_initLs_(list, from->values);
        setToArr(set, list);
        increaseCapacityForAddAll(set, from->pf->count);
        for (int i = 0; i < from->pf->count; ++i) {
            addStrSet(set, list->pf->data[i]);
        }
        list->delete(&list);
    }
}

void clearStrSet(StrSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));
}

bool containsStrSet(StrSet set, string s) {
    if (s == NULL) return false;
    return containsKeyStr(set, s);
}

bool containsAllStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list = (StrList) ctx->collection;
        if (list->pf->count > set->pf->count)
            return false;

        if (list->pf->count == 0) return true;

        for (int i = 0; i < list->pf->count; ++i) {
            if (!containsKeyStr(set, list->pf->data[i])) {
                return false;
            }
        }
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list = (StrLinkedList) ctx->collection;
        if (list->pf->count > set->pf->count)
            return false;

        if (list->pf->count == 0) return true;

        StrNode current = list->pf->begin;
        while (current != NULL) {
            if (!containsKeyStr(set, current->data)) {
                return false;
            }
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count > set->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        StrList listFrom = pr_initLs_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (!containsKeyStr(set, listFrom->pf->data[i])) {
                listFrom->delete(&listFrom);
                return false;
            }
        }
        listFrom->delete(&listFrom);
    }

    return  true;
}

bool containsAnyStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyStr(set, list2->pf->data[i])) {
                return true;
            }
        }
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        StrNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyStr(set, current->data)) {
                return true;
            }
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        StrList listFrom = pr_initLs_(listFrom, setFrom->values);

        for (int i = 0; i < listFrom->pf->count; ++i) {
            if (containsKeyStr(set, listFrom->pf->data[i])) {
                return true;
            }
        }
        listFrom->delete(&listFrom);
    }

    return  false;
}

bool removeStrSet(StrSet set, string s) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        StrSetNode previous = set->pf->bucket[i];
        bool found = false;
        removeNode(&set->pf->bucket[i], &previous, s, &found, &set->pf->capacityCounter);
        if (found)
            set->pf->count--;
    }

    return true;
}

bool removeAllStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList listFrom = (StrList) ctx->collection;
        if (listFrom->pf->count == 0) return true;

        for (int i = 0; i < listFrom->pf->count; ++i) {
            removeStrSet(set, listFrom->pf->data[i]);
        }
    }

    if (ctx->type == STR_LL) {
        //tempList = subtractStrSet(set, (void*) ctx);
        StrLinkedList listFrom = (StrLinkedList) ctx->collection;
        if (listFrom->pf->count == 0) return true;

        StrNode current = listFrom->pf->begin;
        while (current != NULL) {
            removeStrSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count == 0) return true;

        StrList listFrom = pr_initLs_(listFrom, setFrom->values);
        for (int i = 0; i < listFrom->pf->count; ++i) {
            removeStrSet(set, listFrom->pf->data[i]);
        }

        listFrom->delete(&listFrom);
    }

    return true;
}

StrSet subtractStrSet(StrSet set, void* source) {
    if (isEmptyStrSet(set)) {
        StrSet temp = NULL;
        return pr_initSs_(temp, NULL);
    }

    if (source == NULL) {
        StrSet temp = pr_initSs_(temp, set->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    StrSet tempSet = pr_initSs_(tempSet, NULL);

    if (ctx->type == STR_LIST) {
        StrList list = (StrList) ctx->collection;
        if (list->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, list->values);
        StrList listFrom = pr_initLs_(listFrom, NULL);
        setToArr(set, listFrom);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, listFrom->pf->data[i]))
                tempSet->addStr(tempSet, listFrom->pf->data[i]);
        }

        setFrom->delete(&setFrom);
        listFrom->delete(&listFrom);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list = (StrLinkedList) ctx->collection;
        if (list->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, list->values);
        StrList listFrom = pr_initLs_(listFrom, NULL);
        setToArr(set, listFrom);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, listFrom->pf->data[i]))
                tempSet->addStr(tempSet, listFrom->pf->data[i]);
        }

        setFrom->delete(&setFrom);
        listFrom->delete(&listFrom);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        StrList listFrom = pr_initLs_(listFrom, NULL);
        setToArr(set, listFrom);
        for (int i = 0; i < set->pf->count; ++i) {
            if (!setFrom->contains(setFrom, listFrom->pf->data[i]))
                tempSet->addStr(tempSet, listFrom->pf->data[i]);
        }

        listFrom->delete(&listFrom);
    }

    return tempSet;
}

bool isEmptyStrSet(StrSet set) {
    return set == NULL || set->pf->count == 0;
}

int sizeStrSet(StrSet set) {
    return set->pf->count;
}

string toStrStrSet(StrSet set) {
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

void printStrSet(StrSet set) {
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

static bool isCapacityFull(StrSet set) {
    int fullCapacity = set->pf->capacity / 8 * 6;
    return set->pf->capacityCounter >= fullCapacity;
}

static void increaseCapacity(StrSet set) {
    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeSetStr** temp = set->pf->bucket;

    StrList list = pr_initLs_(list, NULL);
    setToArr(set, list);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->pf->data[i]->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
        NodeSetStr* previous = set->pf->bucket[indexBucket];
        insertNode(&set->pf->bucket[indexBucket], &previous, list->pf->data[i]->pf->data, &set->pf->count, &set->pf->capacityCounter);
    }

    list->delete(&list);
    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void increaseCapacityForAddAll(StrSet set, int newSize) {
    if (newSize < (set->pf->capacity - set->pf->capacityCounter)) return;

    int oldCapacity = set->pf->capacity;
    int count = set->pf->count;
    NodeSetStr** temp = set->pf->bucket;

    StrList list = pr_initLs_(list, NULL);
    setToArr(set, list);

    set->pf->capacity = (int)(set->pf->capacity + newSize + (newSize * 0.5));
    set->pf->count = 0;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->pf->data[i]->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
        NodeSetStr* previous = set->pf->bucket[indexBucket];
        insertNode(&set->pf->bucket[indexBucket], &previous, list->pf->data[i]->pf->data, &set->pf->count, &set->pf->capacityCounter);
    }

    list->delete(&list);
    deleteNodes(temp, oldCapacity);
    free(temp);
}

static void setToArr(StrSet set, StrList list) {
    for (int i = 0; i < set->pf->capacity; ++i) {
        copyValuesToList(set->pf->bucket[i], list);
    }
}

static void copyValuesToList(StrSetNode node, StrList list) {
    if (node != NULL) {
        copyValuesToList(node->left, list);
        list->add(list, node->str);
        copyValuesToList(node->right, list);
    }
}

static void insertNode(NodeSetStr** node, NodeSetStr** previous, char* s, int* counter, int* capacityCounter) {
    if (*node == NULL) {
        if (*node == NULL && *previous == NULL) (*capacityCounter)++;
        *node = createNode(s);
        (*counter)++;
    } else {
        int cmp = compareCharStr(s, (*node)->str->pf->data);
        if (cmp == 0) {
            return;
        } else if (cmp < 0) {
            insertNode(&((*node)->left), &(*previous), s, counter, capacityCounter);
        } else {
            insertNode(&((*node)->right), &(*previous), s, counter, capacityCounter);
        }
    }
}

static StrSetNode createNode(char* s) {
    StrSetNode node = malloc(sizeof(NodeSetStr));
    node->str = strOf(s);
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void deleteNodes(NodeSetStr** buckets, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (buckets[i] != NULL)
            deleteInOrder(buckets[i]);
    }
}

static void deleteInOrder(StrSetNode node) {
    if (node == NULL)
        return;

    deleteInOrder(node->left);
    deleteInOrder(node->right);

    node->str->delete(&node->str);
    free(node);
}

int compareCharStr(char* s1, char* s2) {
    return strcmp(s1, s2);
}

int compareStr(string s1, string s2) {
    return strcmp(s1->pf->data, s2->pf->data);
}

static void removeNode(StrSetNode* node, StrSetNode* previous, string s, bool* found, int* capacityCounter) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareCharStr(s->pf->data, (*node)->str->pf->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    StrSetNode temp = *node;
                    *node = NULL;
                    temp->str->delete(&temp->str);
                    free(temp);
                    (*capacityCounter)--;
                    *found = true;
                    return;
                }

                StrSetNode temp = *node;
                if (compareStr((*node)->str, (*previous)->str) == -1)
                    (*previous)->left = NULL;
                else
                    (*previous)->right = NULL;

                temp->str->delete(&temp->str);
                free(temp);
                *found = true;
                return;
            }

            if (((*node)->left != NULL && (*node)->right == NULL) || ((*node)->left == NULL && (*node)->right != NULL)) {
                if (isRoot(node, previous)) {
                    StrSetNode temp = *node;
                    *node = (*node)->left != NULL ? (*node)->left : (*node)->right;
                    temp->str->delete(&temp->str);
                    free(temp);
                    *found = true;
                    return;
                }

                StrSetNode temp = *node;
                if (compareStr((*node)->str, (*previous)->str) == -1) {
                    (*previous)->left = (*node)->left != NULL ? (*node)->left : (*node)->right;
                } else {
                    (*previous)->right = (*node)->left != NULL ? (*node)->left : (*node)->right;
                }

                temp->str->delete(&temp->str);
                free(temp);
                *found = true;
                return;
            }

            if ((*node)->right != NULL && (*node)->left != NULL) {
                StrSetNode temp = *node;
                StrSetNode left = (*node)->left;
                StrSetNode right = (*node)->right;


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

                temp->str->delete(&temp->str);
                free(temp);
                *found = true;
                return;
            }
        } else {
            removeNode(&(*node)->left, &(*node), s, found, capacityCounter);
            removeNode(&(*node)->right, &(*node), s, found, capacityCounter);
        }

        return;
    }
}

static StrSetNode findNode(StrSetNode* node, StrSetNode* previous) {
    if ((*node)->right == NULL) {
        StrSetNode temp = *node;
        (*previous)->right = NULL;
        return temp;
    }

    return findNode(&(*node)->right, &(*node));
}

static bool isRoot(StrSetNode* node, StrSetNode* previous) {
    return compareCharStr((*node)->str->pf->data, (*previous)->str->pf->data) == 0;
}

static  void printInOrder(StrSetNode node, int* counter) {
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

static  void toStringInOrder(StrSetNode node, int* counter, char* text, int* count) {
    if (node != NULL) {
        toStringInOrder(node->left, counter, text, count);
        checkCapacity(text, count, node->str->pf->count);
        sprintf(&text[strlen(text)], "%s", node->str->pf->data);
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

static void checkCapacity(char* text, int* count, int strLength) {
    if (strLength >= *count - strlen(text)) {
        *count = (*count + strLength) * 2;
        text = realloc(text, *count * sizeof(char));
        assert(text != NULL);
    }
}

static int hashString(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = (int)*str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return (int) hash;
}

static bool findKey(NodeSetStr** node, string s, bool* found) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareStr(s, (*node)->str);
    if (cmp == 0) {
        *found = true;
        return true;
    } else if (cmp < 0) {
        findKey(&((*node)->left), s, found);
    } else {
        findKey(&((*node)->right), s, found);
    }
    return *found;
}

static bool containsKeyStr(StrSet set, string s) {
    bool found = false;
    int indexBucket = (int) (hashString(s->pf->data) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], s, &found);
}