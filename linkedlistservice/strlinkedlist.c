//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strlinkedlist.h"
#include "../util/linkedlistutil.h"

// structures
typedef struct NodeStr {
    string data;
    struct NodeStr* next;
    struct NodeStr* prev;
} NodeStr;

typedef struct InnerStrLL {
    int count;
    int index;
    NodeStr* nodes;
    NodeStr* begin;
    NodeStr* end;
} InnerStrLL;

typedef struct NodeStr NodeStr;
typedef NodeStr* StrNode;
typedef String* string;
typedef ArrayListStr* StrList;


// prototypes
static void fillNodeStr(StrNode node, char* s, int* index);
static void quickSortStr(String** strList, int low, int high);
static void quickSortStrReverse(String** strList, int low, int high);
static bool binarySearchStr(string s, String** strList, int high);
static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index);
static void deleteFirstNodeStr(StrLinkedList list, StrNode current);
static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous);
static void copyLLToStrList(StrLinkedList strLL, StrList strList);
static StrLinkedList copyStrLL(StrLinkedList list);
static int compareStr(string s1, string s2);
static void checkCapacity(char* text, int* count, int strLength);


// funcs
void addStrLL(StrLinkedList list, string s) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->pf->end;
    int* index = &list->pf->index;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, s->pf->data, index);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, s->pf->data, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

void addArrCharLL(StrLinkedList list, char* arr) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->pf->end;
    int* index = &list->pf->index;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, arr, index);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, arr, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

void addAllStrLL(StrLinkedList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList from = (StrList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i)
            addStrLL(dest, from->pf->data[i]);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList from = (StrLinkedList) ctx->collection;
        StrNode current = from->pf->begin;
        while (current != NULL) {
            addStrLL(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet from = (StrSet) ctx->collection;
        StrList tempFrom = pr_initLs_(tempFrom, from->values);
        for (int i = 0; i < from->pf->count; ++i)
            addStrLL(dest, tempFrom->pf->data[i]);

    }
}

string getStrLL(StrLinkedList list, int index) {
    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return NULL;
    }

    int tempIndex = 0;
    StrNode current = list->pf->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return NULL;
}

bool setStrLL(StrLinkedList list, int index, string s) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    int tempIndex = 0;
    StrNode current = list->pf->begin;
    while (current != NULL) {
        if (index == tempIndex) {
            current->data = s;
            return true;
        }
        ++tempIndex;
        current = current->next;
    }
    return false;
}

void sortStrLL(StrLinkedList list) {
    StrList strList = pr_initLs_(strList, NULL);
    StrNode current = list->pf->begin;
    StrNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        strList->add(strList, current->data);
        current = current->next;
    }

    quickSortStr(strList->pf->data, 0, strList->pf->count);

    index = 0;
    while (temp != NULL) {
        temp->data->delete(&temp->data);
        temp->data = strOf(strList->pf->data[index++]->pf->data);
        temp = temp->next;
    }
    strList->delete(&strList);
}

void sortStrLLReverse(StrLinkedList list) {
    StrList strList = pr_initLs_(strList, NULL);
    StrNode current = list->pf->begin;
    StrNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        strList->add(strList, current->data);
        current = current->next;
    }

    quickSortStrReverse(strList->pf->data, 0, strList->pf->count);

    index = 0;
    while (temp != NULL) {
        temp->data->delete(&temp->data);
        temp->data = strOf(strList->pf->data[index++]->pf->data);
        temp = temp->next;
    }
    strList->delete(&strList);
}

int indexOfStrLL(StrLinkedList list, string s) {
    if (list == NULL)
        return -1;

    StrNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        if (compareStr(s, current->data) == 1)
            return index;

        current = current->next;
        ++index;
    }
    return -1;
}

void clearStrLL(StrLinkedList list) {
    if (list == NULL)
        return;

    StrNode current = list->pf->begin;
    StrNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;

        temp->data->delete(&temp->data);
        free(temp);
    }

    list->pf->count = 0;
    list->pf->index = 0;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    list->pf->nodes = NULL;
}

bool containsStrLL(StrLinkedList list, string s) {
    if (list == NULL || s->isEmpty(s)) return false;

    StrNode current = list->pf->begin;
    while (current != NULL) {
        if (compareStr(s, current->data) == 1)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllStrLL(StrLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        StrSet set = pr_initSs_(set, list->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyStr(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        StrSet set = pr_initSs_(set, list->values);
        StrNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyStr(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count > list->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        StrSet setTemp = pr_initSs_(setTemp, list->values);
        StrList listFrom = pr_initLs_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyStr(setTemp, listFrom->pf->data[i])) {
                setTemp->delete(&setTemp);
                listFrom->delete(&listFrom);
                return false;
            }
        }
        setTemp->delete(&setTemp);
        listFrom->delete(&listFrom);
    }

    return true;
}

bool containsAnyStrLL(StrLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;
        StrSet set = pr_initSs_(set, list->values);

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyStr(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        StrSet set = pr_initSs_(set, list->values);
        StrNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyStr(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        StrSet setTemp = pr_initSs_(setTemp, list->values);
        StrList listFrom = pr_initLs_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyStr(setTemp, listFrom->pf->data[i])) {
                setTemp->delete(&setTemp);
                listFrom->delete(&listFrom);
                return true;
            }
        }
        setTemp->delete(&setTemp);
        listFrom->delete(&listFrom);
    }

    return false;
}

bool removeStrLL(StrLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    StrNode current = list->pf->begin;
    StrNode previous = NULL;
    StrNode temp = NULL;

    if (list->pf->count == 1) {
        temp = list->pf->begin;
        list->pf->nodes = NULL;
        list->pf->begin = NULL;
        list->pf->end = NULL;
        list->pf->count = 0;
        list->pf->index = 0;
        free(temp);
        return true;
    }

    return removeNodeStr(list, current, previous, index);
}

bool removeAllStrLL(StrLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    StrLinkedList tempList;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;
        StrLinkedList copyValues = pr_initLLs_(copyValues, list2->values);
        tempList = subtractStrLL(list, copyValues);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        tempList = subtractStrLL(list, list2);
    }

    if (ctx->type == STR_SET) {
        StrSet set = (StrSet) ctx->collection;
        StrLinkedList copyValues = pr_initLLs_(copyValues, set->values);

        tempList = subtractStrLL(list, copyValues);
        copyValues->delete(&copyValues);
    }

    list->delete(&list);
    list = tempList;

    return true;
}

StrLinkedList subtractStrLL(StrLinkedList list, void* source) {
    if (isEmptyStrLL(list)) {
        StrLinkedList temp = NULL;
        return pr_initLLs_(temp, NULL);
    }

    if (source == NULL) {
        StrLinkedList temp = pr_initLLs_(temp, list->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    StrLinkedList tempList = pr_initLLs_(tempList, NULL);

    if (ctx->type == STR_LIST) {
        StrList listSource = (StrList) ctx->collection;
        if (listSource->pf->count == 0) {
            StrLinkedList temp = pr_initLLs_(temp, list->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, listSource->values);
        StrNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
                current = current->next;
            }
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList listSource = (StrLinkedList) ctx->collection;
        if (listSource->pf->count == 0) {
            StrLinkedList temp = pr_initLLs_(temp, list->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, listSource->values);
        StrNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
                current = current->next;
            }
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            StrLinkedList temp = pr_initLLs_(temp, list->values);
            return temp;
        }

        StrNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
                current = current->next;
            }
        }
    }

    list->delete(&list);
    list = tempList;

    return list;
}

void reverseStrLL(StrLinkedList list) {
    int counter = 0;
    string temp = NULL;
    StrNode current = list->pf->begin;
    StrNode end = list->pf->end;

    while (counter != list->pf->count / 2) {
        temp = current->data;
        current->data = end->data;
        end->data = temp;

        current = current->next;
        end = end->prev;
        ++counter;
    }
}

bool isEmptyStrLL(StrLinkedList list) {
    return list == NULL || list->pf->count == 0;
}

bool isEqualListsStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->pf->count != list2->pf->count)
        return false;

    StrNode current1 = list1->pf->begin;
    StrNode current2 = list2->pf->begin;

    while (current1 != NULL) {
        if (compareStr(current1->data, current2->data) != 0)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

int sizeStrLL(StrLinkedList list) {
    return list->pf->count;
}

string toStrStrLL(StrLinkedList list) {
    char* text = NULL;
    if (list->pf->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return strOf(text);
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");

    StrNode current = list->pf->begin;
    StrNode end = list->pf->end;
    while (current != end) {
        checkCapacity(text, &count, current->data->pf->count);
        sprintf(&text[strlen(text)], "%s,", current->data->pf->data);
        current = current->next;
    }

    checkCapacity(text, &count, end->data->pf->count);
    sprintf(&text[strlen(text)], "%s", end->data->pf->data);
    strcat(text, "]");

    string s = strOf(text);
    free(text);

    return s;
}

void printStrLL(StrLinkedList list) {
    if (list == NULL || list->pf == NULL) return;

    StrNode current = list->pf->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->data == NULL || current->data->pf->data == NULL) {
            if (current->next == NULL)
                printf("%s", "null");
            else
                printf("%s, ", "null");

            current = current->next;
            continue;
        }

        if (current->next == NULL)
            printf("%s", current->data->pf->data);
        else
            printf("%s, ", current->data->pf->data);
        current = current->next;
    }
    printf("%s\n", "]");
}

void deleteStrLL(StrLinkedList* list) {
    if (list == NULL || *list == NULL) return;

    if ((*list)->pf != NULL) {
        StrNode current = (*list)->pf->nodes;
        StrNode temp = NULL;

        while (current != NULL) {
            temp = current;
            current->prev = NULL;
            current = current->next;

            if (temp->data != NULL)
                temp->data->delete(&temp->data);

            free(temp);
        }

        free((*list)->pf);
    }

    free(*list);
    *list = NULL;
}

// ===================== private funcs =======================

static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeStr(list, current);
        return true;
    } else {
        previous = list->pf->begin;
        previous->prev = NULL;
        current = current->next;
        current->prev = previous;

        int tempIndex = 1;
        while (current != NULL && tempIndex != index) {
            previous = current;
            current = current->next;
            current->prev = previous;
            ++tempIndex;
        }

        if (current == NULL) return false;

        deleteNodeStr(list, current, previous);

        return true;
    }
}

static void deleteFirstNodeStr(StrLinkedList list, StrNode current) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->pf->nodes = current;
    list->pf->begin = current;
    list->pf->count--;
    list->pf->index--;
    temp->data->delete(&temp->data);
    free(temp);
}

static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->pf->end = previous;

    previous->next = current;
    list->pf->count--;
    list->pf->index--;
    temp->data->delete(&temp->data);
    free(temp);
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

 static void quickSortStrReverse(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareStr(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) == -1) {
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
        quickSortStrReverse(strList, i + 1, high);
    if (low < j - 1)
        quickSortStrReverse(strList, low, j);
}

static bool binarySearchStr(string s, String** strList, int high) {
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

static void fillNodeStr(StrNode node, char* s, int* index) {
    node->data = strOf(s);
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

static void copyLLToStrList(StrLinkedList strLL, StrList strList) {
    StrNode current = strLL->pf->begin;
    while (current != NULL) {
        strList->add(strList, current->data);
        current = current->next;
    }
}

static StrLinkedList copyStrLL(StrLinkedList list) {
    StrLinkedList temp = pr_initLLs_(temp, NULL);
    StrNode current = list->pf->begin;

    while (current != NULL) {
        addStrLL(temp, current->data);
        current = current->next;
    }
    return temp;
}

static int compareStr(string s1, string s2) {
    int result = strcmp(s1->pf->data, s2->pf->data);
    return result;
}

static void checkCapacity(char* text, int* count, int strLength) {
    if (strLength >= *count - strlen(text)) {
        *count = (*count + strLength) * 2;
        text = realloc(text, *count * sizeof(char));
        assert(text != NULL);
    }
}
