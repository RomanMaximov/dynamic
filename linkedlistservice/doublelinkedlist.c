//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "doublelinkedlist.h"
#include "../util/linkedlistutil.h"

// structures
typedef struct NodeDouble {
    double data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;

typedef struct InnerDoubleLL {
    int count;
    int index;
    NodeDouble* nodes;
    NodeDouble* begin;
    NodeDouble* end;
} InnerDoubleLL;

typedef struct NodeDouble NodeDouble;
typedef NodeDouble* DoubleNode;


// funcs prototypes
static void fillNodeDouble(DoubleNode node, double num, int* index);
static bool binarySearch(double elem, const double* arr, int high);
static void deleteNodeDouble(DoubleLinkedList list, DoubleNode current, DoubleNode previous);
static void deleteFirstNodeDouble(DoubleLinkedList list, DoubleNode current);
static bool removeNodeDouble(DoubleLinkedList list, DoubleNode current, DoubleNode previous, int index);
static void toArrAndSort(DoubleLinkedList list, double* arr);
static void copyLLToArray(DoubleLinkedList list, double* arr);
static int indexOf(const double* arr, int size, double num);
static DoubleLinkedList copyDoubleLL(DoubleLinkedList list);
static void reverseArr(double* arr, int size);
static int compareDouble(const void* elem1, const void* elem2);
static int compareDoubleReverse(const void* elem1, const void* elem2);

// funcs
void addDoubleLL(DoubleLinkedList list, double num) {
    DoubleNode newNodeEnd = NULL;
    DoubleNode newNode = NULL;
    DoubleNode current = list->pf->end;
    int* index = &list->pf->index;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeDouble));
        if (newNode != NULL) {
            fillNodeDouble(newNode, num, index);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeDouble));
        if (newNodeEnd != NULL) {
            fillNodeDouble(newNodeEnd, num, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

bool setDoubleLL(DoubleLinkedList list, int index, double num) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    int tempIndex = 0;
    DoubleNode current = list->pf->begin;
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

void addAllDoubleLL(DoubleLinkedList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList from = (DoubleList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i)
            addDoubleLL(dest, from->pf->data[i]);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList from = (DoubleLinkedList) ctx->collection;
        DoubleNode current = from->pf->begin;
        while (current != NULL) {
            addDoubleLL(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet from = (DoubleSet) ctx->collection;
        double* arr = malloc(from->pf->count * sizeof(double));
        setToArrDouble(from, arr);
        for (int i = 0; i < from->pf->count; ++i)
            addDoubleLL(dest, arr[i]);

        free(arr);
    }
}

double getDoubleLL(DoubleLinkedList list, int index) {
    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return INT_MAX;
    }

    int tempIndex = 0;
    DoubleNode current = list->pf->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return INT_MAX;
}

void sortDoubleLL(DoubleLinkedList list) {
    double arr[list->pf->count];
    DoubleNode current = list->pf->begin;
    DoubleNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->pf->count, sizeof(double), compareDouble);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

void sortDoubleLLReverse(DoubleLinkedList list) {
    double arr[list->pf->count];
    DoubleNode current = list->pf->begin;
    DoubleNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->pf->count, sizeof(double), compareDoubleReverse);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

int indexOfDoubleLL(DoubleLinkedList list, double num) {
    if (list == NULL)
        return -1;

    DoubleNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        if (num == current->data)
            return index;

        current = current->next;
        ++index;
    }
    return -1;
}

void clearDoubleLL(DoubleLinkedList list) {
    if (list == NULL)
        return;

    DoubleNode current = list->pf->begin;
    DoubleNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->pf->count = 0;
    list->pf->index = 0;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    list->pf->nodes = NULL;
}

bool containsDoubleLL(DoubleLinkedList list, double num) {
    if (list == NULL) return false;

    DoubleNode current = list->pf->begin;
    while (current != NULL) {
        if (num == current->data)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllDoubleLL(DoubleLinkedList list1, void* source) {
    if (list1 == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        DoubleSet set = pr_initSd_(set, list1->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyDouble(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        DoubleSet set = pr_initSd_(set, list1->values);
        DoubleNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyDouble(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count > list1->pf->count)
            return false;

        DoubleSet setTemp = pr_initSd_(setTemp, list1->values);
        DoubleList listFrom = pr_initLd_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyDouble(setTemp, listFrom->pf->data[i])) {
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

bool containsAnyDoubleLL(DoubleLinkedList list1, void* source) {
    if (list1 == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        DoubleSet set = pr_initSd_(set, list1->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyDouble(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        DoubleSet set = pr_initSd_(set, list1->values);
        DoubleNode current = list2->pf->begin;
        while (current != NULL) {
            if (containsKeyDouble(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count > list1->pf->count)
            return false;

        DoubleSet setTemp = pr_initSd_(setTemp, list1->values);
        DoubleList listFrom = pr_initLd_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyDouble(setTemp, listFrom->pf->data[i])) {
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

bool removeDoubleLL(DoubleLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    DoubleNode current = list->pf->begin;
    DoubleNode previous = NULL;
    DoubleNode temp = NULL;

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

    return removeNodeDouble(list, current, previous, index);
}

bool removeAllDoubleLL(DoubleLinkedList list1, void* source) {
    if (list1 == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    DoubleLinkedList tempList;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        DoubleLinkedList copyValues = pr_initLLd_(copyValues, list2->values);
        tempList = subtractDoubleLL(list1, copyValues);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        tempList = subtractDoubleLL(list1, list2);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet set = (DoubleSet) ctx->collection;
        DoubleLinkedList copyValues = pr_initLLd_(copyValues, set->values);

        tempList = subtractDoubleLL(list1, copyValues);
        copyValues->delete(&copyValues);
    }

    list1->delete(&list1);
    list1 = tempList;

    return true;
}

void reverseDoubleLL(DoubleLinkedList list) {
    double* arr = malloc(list->pf->count * sizeof(int));
    copyLLToArray(list, arr);

    reverseArr(arr, list->pf->count);

    DoubleNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        current->data = arr[index];
        current = current->next;
        ++index;
    }

    free(arr);
}

DoubleLinkedList subtractDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (isEmptyDoubleLL(list1)) {
        DoubleLinkedList temp = NULL;
        return pr_initLLd_(temp, NULL);
    }

    if (isEmptyDoubleLL(list2)) {
        DoubleLinkedList temp = pr_initLLd_(temp, list1->values);
        return temp;
    }

    DoubleSet set = pr_initSd_(set, list2->values);
    DoubleLinkedList temp = pr_initLLd_(temp, NULL);

    DoubleNode current = list1->pf->begin;
    while (current != NULL) {
        if (!set->contains(set, current->data))
            temp->add(temp, current->data);
        current = current->next;
    }

    set->delete(&set);

    return temp;
}

bool isEmptyDoubleLL(DoubleLinkedList list) {
    return list == NULL || list->pf->count == 0;
}

bool isEqualListsDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->pf->count != list2->pf->count)
        return false;

    DoubleNode current1 = list1->pf->begin;
    DoubleNode current2 = list2->pf->begin;

    while (current1 != NULL) {
        if (current1->data != current2->data)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

int sizeDoubleLL(DoubleLinkedList list) {
    return list->pf->count;
}

string toStrDoubleLL(DoubleLinkedList list) {
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
    DoubleNode current = list->pf->begin;
    DoubleNode end = list->pf->end;
    while (current != end) {
        sprintf(&text[strlen(text)], "%.9f,", current->data);
        if (strlen(text) > (int)(count / 8 * 7)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
        current = current->next;
    }

    sprintf(&text[strlen(text)], "%.9f", end->data);
    strcat(text, "]");
    string s = strOf(text);
    free(text);

    return s;
}

void printDoubleLL(DoubleLinkedList list) {
    if (list == NULL || list->pf == NULL) return;

    DoubleNode current = list->pf->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->next == NULL)
            printf("%.9f", current->data);
        else
            printf("%.9f, ", current->data);
        current = current->next;
    }
    printf("%s\n", "]");
}


void deleteDoubleLL(DoubleLinkedList* list) {
    if (list == NULL || *list == NULL) return;

    if ((*list)->pf != NULL) {
        DoubleNode current = (*list)->pf->begin;
        DoubleNode temp = NULL;

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

static void deleteFirstNodeDouble(DoubleLinkedList list, DoubleNode current) {
    DoubleNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->pf->nodes = current;
    list->pf->begin = current;
    list->pf->count--;
    list->pf->index--;
    free(temp);
}

static void deleteNodeInt(DoubleLinkedList list, DoubleNode current, DoubleNode previous) {
    DoubleNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->pf->end = previous;

    previous->next = current;
    list->pf->count--;
    list->pf->index--;
    free(temp);
}

static bool removeNodeDouble(DoubleLinkedList list, DoubleNode current, DoubleNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeDouble(list, current);
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

static bool binarySearch(double elem, const double* arr, int high) {
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

static void toArrAndSort(DoubleLinkedList list, double * arr) {
    DoubleNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->pf->count, sizeof(double), compareDouble);
}

static int indexOf(const double* arr, int size, double num) {
    for (int i = 0; i < size; ++i) {
        if (num == arr[i]) {
            return i;
        }
    }

    return -1;
}

static void copyLLToArray(DoubleLinkedList list, double* arr) {
    DoubleNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
}

static DoubleLinkedList copyDoubleLL(DoubleLinkedList list) {
    DoubleLinkedList temp = pr_initLLd_(temp, NULL);
    DoubleNode current = list->pf->begin;

    while (current != NULL) {
        addDoubleLL(temp, current->data);
        current = current->next;
    }
    return temp;
}

static void reverseArr(double* arr, int size) {
    --size;
    double* start = arr;
    double* end = arr + size;

    double temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }
}

static void fillNodeDouble(DoubleNode node, double num, int* index) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

static int compareDouble(const void* elem1, const void* elem2) {
    return fabs((*(double*)elem1 - *(double*)elem2)) < 0.000000001
           ? 0
           : (*(double*)elem1 - *(double*)elem2) < 0 ? -1 : 1;
}

static int compareDoubleReverse(const void* elem1, const void* elem2) {
    return fabs((*(double*)elem2 - *(double*)elem1)) < 0.000000001
           ? 0
           : (*(double*)elem2 - *(double*)elem1) < 0 ? -1 : 1;
}

