//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intlinkedlist.h"
#include "../util/linkedlistutil.h"


// structures
typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct InnerIntLL {
    int count;
    struct NodeInt* nodes;
    struct NodeInt* begin;
    struct NodeInt* end;
} InnerIntLL;


typedef struct NodeInt NodeInt;
typedef NodeInt* IntNode;
typedef Itr* Iterator;


// private funcs prototypes
static void fillNodeInt(IntNode node, int num);
static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous);
static void deleteFirstNodeInt(IntLinkedList list, IntNode current);
static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index);
static void copyLLToArray(IntLinkedList list, int* arr);
static void reverseArr(int* arr, int size);
static int compareInt(const void* elem1, const void* elem2);
static int compareIntReverse(const void* elem1, const void* elem2);

static void insertBeginInt(IntLinkedList list, int num) {
    IntNode newNodeStart = NULL;
    IntNode newNodeEnd = NULL;
    IntNode current = NULL;

    if (list->pf->count == 0) {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num);
        }

        newNodeEnd = list->pf->nodes;
        list->pf->nodes = newNodeEnd;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNodeEnd;
    } else {
        newNodeStart = malloc(sizeof(NodeInt));
        if (newNodeStart != NULL) {
            fillNodeInt(newNodeStart, num);
        }

        newNodeStart->next = list->pf->nodes;
        list->pf->nodes->prev = newNodeStart;
        list->pf->nodes = newNodeStart;
        list->pf->begin = list->pf->nodes;
    }

    list->pf->count++;
}

void addIntLL(IntLinkedList list, int num) {
    IntNode newNodeEnd = NULL;
    IntNode newNode = NULL;
    IntNode current = list->pf->end;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeInt));
        if (newNode != NULL) {
            fillNodeInt(newNode, num);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

void addAllIntLL(IntLinkedList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList from = (IntList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i)
            addIntLL(dest, from->pf->data[i]);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList from = (IntLinkedList) ctx->collection;
        IntNode current = from->pf->begin;
        while (current != NULL) {
            addIntLL(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == INT_SET) {
        IntSet from = (IntSet) ctx->collection;
        int* arr = malloc(from->pf->count * sizeof(int));
        setToArrInt(from, arr);
        for (int i = 0; i < from->pf->count; ++i)
            addIntLL(dest, arr[i]);

        free(arr);
    }
}

int getIntLL(IntLinkedList list, int index) {
    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return INT_MAX;
    }

    int tempIndex = 0;
    IntNode current = list->pf->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return INT_MAX;
}

bool setIntLL(IntLinkedList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    int tempIndex = 0;
    IntNode current = list->pf->begin;
    while (current != NULL) {
        if (index == tempIndex) {
            current->data = num;
            return true;
        }
        ++tempIndex;
        current = current->next;
    }
    return false;
}

void sortIntLL(IntLinkedList list) {
    int arr[list->pf->count];
    IntNode current = list->pf->begin;
    IntNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->pf->count, sizeof(int), compareInt);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

void sortIntLLReverse(IntLinkedList list) {
    int arr[list->pf->count];
    IntNode current = list->pf->begin;
    IntNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->pf->count, sizeof(int), compareIntReverse);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}


int indexOfIntLL(IntLinkedList list, int num) {
    if (list == NULL)
        return -1;

    IntNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        if (num == current->data)
            return index;

        current = current->next;
        ++index;
    }
    return -1;
}

void clearIntLL(IntLinkedList list) {
    if (list == NULL)
        return;

    IntNode current = list->pf->begin;
    IntNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->pf->count = 0;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    list->pf->nodes = NULL;
}

bool containsIntLL(IntLinkedList list, int num) {
    if (list == NULL) return false;

    IntNode current = list->pf->begin;
    while (current != NULL) {
        if (num == current->data)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllIntLL(IntLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        IntSet set = pr_initSi_(set, list->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyInt(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        IntSet set = pr_initSi_(set, list->values);
        IntNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyInt(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count > list->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        IntSet setTemp = pr_initSi_(setTemp, list->values);
        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyInt(setTemp, listFrom->pf->data[i])) {
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

bool containsAnyIntLL(IntLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        IntSet set = pr_initSi_(set, list->values);

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyInt(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        IntSet set = pr_initSi_(set, list->values);
        IntNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyInt(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        IntSet setTemp = pr_initSi_(setTemp, list->values);
        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyInt(setTemp, listFrom->pf->data[i])) {
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

bool removeIntLL(IntLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    IntNode current = list->pf->begin;
    IntNode previous = NULL;
    IntNode temp = NULL;

    if (list->pf->count == 1) {
        temp = list->pf->begin;
        list->pf->nodes = NULL;
        list->pf->begin = NULL;
        list->pf->end = NULL;
        list->pf->count = 0;
        free(temp);
        return true;
    }

    return removeNodeInt(list, current, previous, index);
}

bool removeAllIntLL(IntLinkedList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    IntLinkedList tempList;

    if (ctx->type == INT_LIST) {
        tempList = subtractIntLL(list, (void*) ctx);
    }

    if (ctx->type == INT_LL) {
        tempList = subtractIntLL(list, (void*) ctx);
    }

    if (ctx->type == INT_SET) {
        tempList = subtractIntLL(list, (void*) ctx);
    }

    clearIntLL(list);
    list->addAll(list, tempList->values);
    tempList->delete(&tempList);

    return true;
}

IntLinkedList subtractIntLL(IntLinkedList list, void* source) {
    if (isEmptyIntLL(list)) {
        IntLinkedList temp = NULL;
        return pr_initLLi_(temp, NULL);
    }

    if (source == NULL) {
        IntLinkedList temp = pr_initLLi_(temp, list->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    IntLinkedList tempList = pr_initLLi_(tempList, NULL);

    if (ctx->type == INT_LIST) {
        IntList listSource = (IntList) ctx->collection;
        if (listSource->pf->count == 0) {
            IntLinkedList temp = pr_initLLi_(temp, list->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, listSource->values);
        IntNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
            }
            current = current->next;
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList listSource = (IntLinkedList) ctx->collection;
        if (listSource->pf->count == 0) {
            IntLinkedList temp = pr_initLLi_(temp, list->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, listSource->values);
        IntNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
            }
            current = current->next;
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            IntLinkedList temp = pr_initLLi_(temp, list->values);
            return temp;
        }

        IntNode current = list->pf->begin;
        while (current != NULL) {
            if (!setFrom->contains(setFrom, current->data)) {
                tempList->add(tempList, current->data);
            }
            current = current->next;
        }
    }

    return tempList;
}

bool isEmptyIntLL(IntLinkedList list) {
    return list == NULL || list->pf->count == 0;
}

void reverseIntLL(IntLinkedList list) {
    int* arr = malloc(list->pf->count * sizeof(int));
    copyLLToArray(list, arr);

    reverseArr(arr, list->pf->count);

    IntNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        current->data = arr[index];
        current = current->next;
        ++index;
    }

    free(arr);
}

bool isEqualListsIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->pf->count != list2->pf->count)
        return false;

    IntNode current1 = list1->pf->begin;
    IntNode current2 = list2->pf->begin;

    while (current1 != NULL) {
        if (current1->data != current2->data)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

int sizeIntLL(IntLinkedList list) {
    return list->pf->count;
}

string toStrIntLL(IntLinkedList list) {
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
    IntNode current = list->pf->begin;
    IntNode end = list->pf->end;
    while (current != end) {
        sprintf(&text[strlen(text)], "%d,", current->data);
        if (strlen(text) > (int)(count / 8 * 7)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
            assert(text != NULL);
        }
        current = current->next;
    }

    sprintf(&text[strlen(text)], "%d", end->data);
    strcat(text, "]");
    string s = strOf(text);
    free(text);

    return s;
}

void printIntLL(IntLinkedList list) {
    if (list == NULL || list->pf == NULL) return;

    IntNode current = list->pf->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->next == NULL)
            printf("%d", current->data);
        else
            printf("%d, ", current->data);
        current = current->next;
    }
    printf("%s\n", "]");
}


void deleteIntLL(IntLinkedList* list) {
    if (list == NULL || *list == NULL) return;

    if ((*list)->values != NULL) free((*list)->values);

    if ((*list)->pf != NULL) {
        IntNode current = (*list)->pf->begin;
        IntNode temp = NULL;

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }

        free((*list)->pf);
    }

    free(*list);
    *list = NULL;
}

// ===================== private funcs =======================

static void deleteFirstNodeInt(IntLinkedList list, IntNode current) {
    IntNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->pf->nodes = current;
    list->pf->begin = current;
    list->pf->count--;
    free(temp);
}

static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous) {
    IntNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->pf->end = previous;

    previous->next = current;
    list->pf->count--;
    free(temp);
}

static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeInt(list, current);
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

        deleteNodeInt(list, current, previous);

        return true;
    }
}

static void fillNodeInt(IntNode node, int num) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
}

static void copyLLToArray(IntLinkedList list, int* arr) {
    IntNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
}

static void reverseArr(int* arr, int size) {
    --size;
    int* start = arr;
    int* end = arr + size;

    int temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }
}

static int compareInt(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

static int compareIntReverse(const void* elem1, const void* elem2) {
    return (*(int*)elem2 - *(int*)elem1);
}
