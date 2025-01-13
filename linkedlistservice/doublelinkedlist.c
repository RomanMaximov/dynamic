//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "doublelinkedlist.h"

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
void addDoubleElemLL(DoubleLinkedList list, double num) {
    DoubleNode newNodeEnd = NULL;
    DoubleNode newNode = NULL;
    DoubleNode current = list->inner->end;
    int* index = &list->inner->index;

    if (list->inner->count == 0) {
        newNode = malloc(sizeof(NodeDouble));
        if (newNode != NULL) {
            fillNodeDouble(newNode, num, index);
        }

        newNode->next = list->inner->nodes;
        list->inner->nodes = newNode;
        list->inner->begin = list->inner->nodes;
        list->inner->end = newNode;
        list->inner->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeDouble));
        if (newNodeEnd != NULL) {
            fillNodeDouble(newNodeEnd, num, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->inner->end = newNodeEnd;
    }

    list->inner->count++;
}

bool setDoubleElemLL(DoubleLinkedList list, int index, double num) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    int tempIndex = 0;
    DoubleNode current = list->inner->begin;
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

void addAllDoubleElemLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return;

    DoubleNode current = list2->inner->nodes;
    while (current != NULL) {
        addDoubleElemLL(list1, current->data);
        current = current->next;
    }
}

double getDoubleElemLL(DoubleLinkedList list, int index) {
    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return INT_MAX;
    }

    int tempIndex = 0;
    DoubleNode current = list->inner->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return INT_MAX;
}

void sortDoubleLL(DoubleLinkedList list) {
    double arr[list->inner->count];
    DoubleNode current = list->inner->begin;
    DoubleNode temp = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(double), compareDouble);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

void sortDoubleLLReverse(DoubleLinkedList list) {
    double arr[list->inner->count];
    DoubleNode current = list->inner->begin;
    DoubleNode temp = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(double), compareDoubleReverse);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

int indexOfDoubleLL(DoubleLinkedList list, double num) {
    if (list == NULL)
        return -1;

    DoubleNode current = list->inner->begin;
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

    DoubleNode current = list->inner->begin;
    DoubleNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    list->inner->nodes = NULL;
}

bool containsDoubleLL(DoubleLinkedList list, double num) {
    if (list == NULL) return false;

    DoubleNode current = list->inner->begin;
    while (current != NULL) {
        if (num == current->data)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count) return false;

    double arr[list1->inner->count];
    DoubleNode temp = list2->inner->begin;

    toArrAndSort(list1, arr);

    while (temp != NULL) {
        if (!binarySearch(temp->data, arr, list1->inner->count))
            return false;

        temp = temp->next;
    }

    return true;
}

bool containsAnyDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    double arr[list1->inner->count];
    DoubleNode temp = list2->inner->begin;

    toArrAndSort(list1, arr);

    while (temp != NULL) {
        if (binarySearch(temp->data, arr, list1->inner->count))
            return true;

        temp = temp->next;
    }

    return false;
}

bool removeDoubleLL(DoubleLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    DoubleNode current = list->inner->begin;
    DoubleNode previous = NULL;
    DoubleNode temp = NULL;

    if (list->inner->count == 1) {
        temp = list->inner->begin;
        list->inner->nodes = NULL;
        list->inner->begin = NULL;
        list->inner->end = NULL;
        list->inner->count = 0;
        list->inner->index = 0;
        free(temp);
        return true;
    }

    return removeNodeDouble(list, current, previous, index);
}

bool removeAllDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 ==NULL) return false;

    int listSize = list1->inner->count;
    double* temp = malloc(listSize * sizeof(int));
    double* filtered = malloc(listSize * sizeof(int));
    double* tempForBS = malloc(listSize * sizeof(int));

    copyLLToArray(list1, temp);
    copyLLToArray(list1, tempForBS);
    qsort(tempForBS, listSize, sizeof(double), compareDouble);

    int j = 0;
    DoubleNode current2 = list2->inner->begin;
    while (current2 != NULL) {
        bool isExist = binarySearch(current2->data, tempForBS, listSize);
        if (isExist) {
            filtered[j] = current2->data;
            ++j;
        }

        current2 = current2->next;
    }

    clearDoubleLL(list1);

    qsort(filtered, j, sizeof(double), compareDouble);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearch(temp[i], filtered, j))
            continue;

        addDoubleElemLL(list1, temp[i]);
    }

    free(tempForBS);
    free(filtered);
    free(temp);

    return true;
}

DoubleLinkedList subtractDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (isEmptyDoubleLL(list1)) {
        DoubleLinkedList temp = NULL;
        return newDoubleLinkedList(temp);
    }

    if (isEmptyDoubleLL(list2)) {
        return copyDoubleLL(list1);
    }

    int listSize = list1->inner->count;
    double* temp = malloc(listSize * sizeof(int));
    double* filtered = malloc(listSize * sizeof(int));
    double* tempForBS = malloc(listSize * sizeof(int));

    copyLLToArray(list1, temp);
    copyLLToArray(list1, tempForBS);
    qsort(tempForBS, listSize, sizeof(double), compareDouble);

    int j = 0;
    DoubleNode current2 = list2->inner->begin;
    while (current2 != NULL) {
        bool isExist = binarySearch(current2->data, tempForBS, listSize);
        if (isExist) {
            filtered[j] = current2->data;
            ++j;
        }

        current2 = current2->next;
    }

    DoubleLinkedList newLL = newDoubleLinkedList(newLL);

    qsort(filtered, j, sizeof(double), compareDouble);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearch(temp[i], filtered, j))
            continue;

        addDoubleElemLL(newLL, temp[i]);
    }

    free(tempForBS);
    free(filtered);
    free(temp);

    return newLL;
}

void printDoubleLL(DoubleLinkedList list) {
    if (list == NULL || list->inner == NULL) return;

    DoubleNode current = list->inner->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->next == NULL)
            printf("%f", current->data);
        else
            printf("%f, ", current->data);
        current = current->next;
    }
    printf("%s\n", "]");
}


void deleteDoubleLL(DoubleLinkedList* list) {
    if (list == NULL || *list == NULL) return;

    if ((*list)->inner != NULL) {
        DoubleNode current = (*list)->inner->begin;
        DoubleNode temp = NULL;

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }

        free((*list)->inner);
    }

    free(*list);
    *list = NULL;
}

int sizeDoubleLL(DoubleLinkedList list) {
    return list->inner->count;
}

bool isEmptyDoubleLL(DoubleLinkedList list) {
    return list == NULL || list->inner->count == 0;
}

void reverseDoubleLL(DoubleLinkedList list) {
    double* arr = malloc(list->inner->count * sizeof(int));
    copyLLToArray(list, arr);

    reverseArr(arr, list->inner->count);

    DoubleNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        current->data = arr[index];
        current = current->next;
        ++index;
    }

    free(arr);
}

bool isEqualListsDoubleLL(DoubleLinkedList list1, DoubleLinkedList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->inner->count != list2->inner->count)
        return false;

    DoubleNode current1 = list1->inner->begin;
    DoubleNode current2 = list2->inner->begin;

    while (current1 != NULL) {
        if (current1->data != current2->data)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

DoubleLinkedList emptyIfNullDoubleLL(DoubleLinkedList list) {
    return list == NULL ? newDoubleLinkedList(list) : list;
}

// ===================== private funcs =======================

static void deleteFirstNodeDouble(DoubleLinkedList list, DoubleNode current) {
    DoubleNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->inner->nodes = current;
    list->inner->begin = current;
    list->inner->count--;
    list->inner->index--;
    free(temp);
}

static void deleteNodeInt(DoubleLinkedList list, DoubleNode current, DoubleNode previous) {
    DoubleNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->inner->end = previous;

    previous->next = current;
    list->inner->count--;
    list->inner->index--;
    free(temp);
}

static bool removeNodeDouble(DoubleLinkedList list, DoubleNode current, DoubleNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeDouble(list, current);
        return true;
    } else {
        previous = list->inner->begin;
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
    DoubleNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(double), compareDouble);
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
    DoubleNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
}

static DoubleLinkedList copyDoubleLL(DoubleLinkedList list) {
    DoubleLinkedList temp = newDoubleLinkedList(temp);
    DoubleNode current = list->inner->begin;

    while (current != NULL) {
        addDoubleElemLL(temp, current->data);
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

