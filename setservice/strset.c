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
static void insertNode(NodeSetStr** node, char* s, int* counter);
static void printInOrder(StrSetNode node, int* counter);
static bool isCapacityFull(StrSet set);
static void increaseCapacity(StrSet set);
static void copyValuesToList(StrSetNode node, StrList list);
static void setToArr(StrSet set, StrList list);
static void deleteNodes(NodeSetStr** buckets, int capacity);
static void deleteInOrder(StrSetNode node);
static void quickSortStr(String** strList, int low, int high);
static void removeNode(StrSetNode* node, StrSetNode* previous, string s, bool* found);
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
    insertNode(&set->pf->bucket[indexBucket], s->pf->data, &set->pf->count);
}

void addCharArrSet(StrSet set, char* s) {
    if (isCapacityFull(set))
        increaseCapacity(set);

    int indexBucket = (hashString(s) & 0x7FFFFFFF) % set->pf->capacity;
    insertNode(&set->pf->bucket[indexBucket], s, &set->pf->count);
}

void addAllStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;
    if (ctx->type == STR_LIST) {
        StrList from = (StrList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i) {
            addStrSet(set, from->pf->data[i]);
        }
    }

    if (ctx->type == STR_LL) {
        StrLinkedList from = (StrLinkedList) ctx->collection;
        StrNode current = from->pf->begin;
        while (current != NULL) {
            addStrSet(set, current->data);
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet from = (StrSet) ctx->collection;
        Iterator iter = iterator(from->values);
        while (hasNext(iter)) {
            addStrSet(set, nextStr(iter));
        }
        deleteItr(&iter);
    }
}

void clearStrSet(StrSet set) {
    if (set->pf->bucket != NULL) {
        deleteNodes(set->pf->bucket, set->pf->capacity);
        free(set->pf->bucket);
    }

    set->pf->count = 0;
    set->pf->capacity = 16;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeSetStr*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;
}

bool containsStrSet(StrSet set, string s) {
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
        removeNode(&set->pf->bucket[i], &previous, s, &found);
        if (found)
            set->pf->count--;
    }

    return true;
}

bool removeAllStrSet(StrSet set, void* source) {
    if (set == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    StrSet tempList;

    if (ctx->type == STR_LIST) {
        StrList list = (StrList) ctx->collection;
        tempList = subtractStrSet(set, list->values);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list = (StrLinkedList) ctx->collection;
        tempList = subtractStrSet(set, list->values);
    }

    if (ctx->type == STR_SET) {
        StrSet set2 = (StrSet) ctx->collection;
        tempList = subtractStrSet(set, set2->values);
    }

    set->delete(&set);
    set = tempList;

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
    StrSet tempSet = pr_initSs_(tempSet, set->values);

    if (ctx->type == STR_LIST) {
        StrList list = (StrList) ctx->collection;
        if (list->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, list->values);
        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            string s = nextStr(iter);
            if (!setFrom->contains(setFrom, s))
                tempSet->removeElem(tempSet, s);
        }

        setFrom->delete(&setFrom);
        deleteItr(&iter);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list = (StrLinkedList) ctx->collection;
        if (list->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, list->values);
        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            string s = nextStr(iter);
            if (!setFrom->contains(setFrom, s))
                tempSet->removeElem(tempSet, s);
        }

        setFrom->delete(&setFrom);
        deleteItr(&iter);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            StrSet temp = pr_initSs_(temp, set->values);
            return temp;
        }

        Iterator iter = iterator(set->values);
        while (hasNext(iter)) {
            string s = nextStr(iter);
            if (!setFrom->contains(setFrom, s))
                tempSet->removeElem(tempSet, s);
        }

        deleteItr(&iter);
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
    NodeSetStr** temp = set->pf->bucket;

    StrList list = pr_initLs_(list, NULL);
    setToArr(set, list);

    set->pf->capacity *= 2;
    set->pf->count = 0;
    set->pf->bucket = malloc(set->pf->capacity * sizeof(NodeSetStr*));
    for (int i = 0; i < set->pf->capacity; ++i)
        set->pf->bucket[i] = NULL;

    for (int i = 0; i < count; ++i) {
        int indexBucket = (hashString(list->pf->data[i]->pf->data) & 0x7FFFFFFF) % set->pf->capacity;
        insertNode(&set->pf->bucket[indexBucket], list->pf->data[i]->pf->data, &set->pf->count);
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

static void insertNode(NodeSetStr** node, char* s, int* counter) {
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

static void removeNode(StrSetNode* node, StrSetNode* previous, string s, bool* found) {
    if (*found) return;

    if (*node != NULL && *previous != NULL) {
        if (compareCharStr(s->pf->data, (*node)->str->pf->data) == 0) {
            if ((*node)->right == NULL && (*node)->left == NULL) {
                if (isRoot(node, previous)) {
                    StrSetNode temp = *node;
                    *node = NULL;
                    temp->str->delete(&temp->str);
                    free(temp);
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
            removeNode(&(*node)->left, &(*node), s, found);
            removeNode(&(*node)->right, &(*node), s, found);
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
        sprintf(&text[strlen(text)], "%s,", node->str->pf->data);
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

static bool findKey(NodeSetStr** node, string s) {
    if (node == NULL || *node == NULL) return false;

    int cmp = compareStr(s, (*node)->str);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        findKey(&((*node)->left), s);
    } else {
        findKey(&((*node)->right), s);
    }
    return false;
}

static bool containsKeyStr(StrSet set, string s) {
    int indexBucket = (int) (hashString(s->pf->data) % set->pf->capacity);
    return findKey(&set->pf->bucket[indexBucket], s);
}