//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "intlinkedlist.h"


// structures
typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct InnerIntLL {
    int count;
    int index;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} InnerIntLL;


typedef struct NodeInt NodeInt;
typedef NodeInt* IntNode;
typedef Itr* Iterator;


// funcs prototypes
static void fillNodeInt(IntNode node, int num, int* index);
static bool binarySearch(int elem, const int* arr, int high);
static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous);
static void deleteFirstNodeInt(IntLinkedList list, IntNode current);
static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index);
static void toArrAndSort(IntLinkedList list, int* arr);
static void copyLLToArray(IntLinkedList list, int* arr);
static int indexOf(int* arr, int size, int num);
static IntLinkedList copyIntLL(IntLinkedList list);
static void reverseArr(int* arr, int size);
static int compareInt(const void* elem1, const void* elem2);
static int compareIntReverse(const void* elem1, const void* elem2);
static bool hasNext(Iterator iter);
static int getIntValue(Iterator iter, IntLinkedList list);

static void insertBeginInt(IntLinkedList list, int num, int* index) {
    IntNode newNodeStart = NULL;
    IntNode newNodeEnd = NULL;
    IntNode current = NULL;

    if (list->inner->count == 0) {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num, index);
        }

        newNodeEnd = list->inner->nodes;
        list->inner->nodes = newNodeEnd;
        list->inner->begin = list->inner->nodes;
        list->inner->end = newNodeEnd;
    } else {
        newNodeStart = malloc(sizeof(NodeInt));
        if (newNodeStart != NULL) {
            fillNodeInt(newNodeStart, num, index);
        }

        newNodeStart->next = list->inner->nodes;
        list->inner->nodes->prev = newNodeStart;
        list->inner->nodes = newNodeStart;
        list->inner->begin = list->inner->nodes;
    }

    list->inner->count++;
}

void addIntElemLL(IntLinkedList list, int num) {
    IntNode newNodeEnd = NULL;
    IntNode newNode = NULL;
    IntNode current = list->inner->end;
    int* index = &list->inner->index;

    if (list->inner->count == 0) {
        newNode = malloc(sizeof(NodeInt));
        if (newNode != NULL) {
            fillNodeInt(newNode, num, index);
        }

        newNode->next = list->inner->nodes;
        list->inner->nodes = newNode;
        list->inner->begin = list->inner->nodes;
        list->inner->end = newNode;
        list->inner->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->inner->end = newNodeEnd;
    }

    list->inner->count++;
}

bool setIntElemLL(IntLinkedList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    int tempIndex = 0;
    IntNode current = list->inner->begin;
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

void addAllIntElemLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return;

    IntNode current = list2->inner->nodes;
    while (current != NULL) {
        addIntElemLL(list1, current->data);
        current = current->next;
    }
}

int getIntElemLL(IntLinkedList list, int index) {
    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return INT_MAX;
    }

    int tempIndex = 0;
    IntNode current = list->inner->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return INT_MAX;
}

void sortIntLL(IntLinkedList list) {
    int arr[list->inner->count];
    IntNode current = list->inner->begin;
    IntNode temp = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(int), compareInt);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

void sortIntLLReverse(IntLinkedList list) {
    int arr[list->inner->count];
    IntNode current = list->inner->begin;
    IntNode temp = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(int), compareIntReverse);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}


int indexOfIntLL(IntLinkedList list, int num) {
    if (list == NULL)
        return -1;

    IntNode current = list->inner->begin;
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

    IntNode current = list->inner->begin;
    IntNode temp = NULL;

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

bool containsIntLL(IntLinkedList list, int num) {
    if (list == NULL) return false;

    IntNode current = list->inner->begin;
    while (current != NULL) {
        if (num == current->data)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count) return false;

    int arr[list1->inner->count];
    IntNode temp = list2->inner->begin;

    toArrAndSort(list1, arr);

    while (temp != NULL) {
        if (!binarySearch(temp->data, arr, list1->inner->count))
            return false;

        temp = temp->next;
    }

    return true;
}

bool containsAnyIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    int arr[list1->inner->count];
    IntNode temp = list2->inner->begin;

    toArrAndSort(list1, arr);

    while (temp != NULL) {
        if (binarySearch(temp->data, arr, list1->inner->count))
            return true;

        temp = temp->next;
    }

    return false;
}

bool removeIntLL(IntLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    IntNode current = list->inner->begin;
    IntNode previous = NULL;
    IntNode temp = NULL;

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

    return removeNodeInt(list, current, previous, index);
}

bool removeAllIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 ==NULL) return false;

    int listSize = list1->inner->count;
    int* temp = malloc(listSize * sizeof(int));
    int* filtered = malloc(listSize * sizeof(int));
    int* tempForBS = malloc(listSize * sizeof(int));

    copyLLToArray(list1, temp);
    copyLLToArray(list1, tempForBS);
    qsort(tempForBS, listSize, sizeof(int), compareInt);

    int j = 0;
    IntNode current2 = list2->inner->begin;
    while (current2 != NULL) {
        bool isExist = binarySearch(current2->data, tempForBS, listSize);
        if (isExist) {
            filtered[j] = current2->data;
            ++j;
        }

        current2 = current2->next;
    }

    clearIntLL(list1);

    qsort(filtered, j, sizeof(int), compareInt);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearch(temp[i], filtered, j))
            continue;

        addIntElemLL(list1, temp[i]);
    }

    free(tempForBS);
    free(filtered);
    free(temp);

    return true;
}

IntLinkedList subtractIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (isEmptyIntLL(list1)) {
        IntLinkedList temp = NULL;
        return newIntLinkedList(temp);
    }

    if (isEmptyIntLL(list2)) {
        return copyIntLL(list1);
    }

    int listSize = list1->inner->count;
    int* temp = malloc(listSize * sizeof(int));
    int* filtered = malloc(listSize * sizeof(int));
    int* tempForBS = malloc(listSize * sizeof(int));

    copyLLToArray(list1, temp);
    copyLLToArray(list1, tempForBS);
    qsort(tempForBS, listSize, sizeof(int), compareInt);

    int j = 0;
    IntNode current2 = list2->inner->begin;
    while (current2 != NULL) {
        bool isExist = binarySearch(current2->data, tempForBS, listSize);
        if (isExist) {
            filtered[j] = current2->data;
            ++j;
        }

        current2 = current2->next;
    }

    IntLinkedList newLL = newIntLinkedList(newLL);

    qsort(filtered, j, sizeof(int), compareInt);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearch(temp[i], filtered, j))
            continue;

        addIntElemLL(newLL, temp[i]);
    }

    free(tempForBS);
    free(filtered);
    free(temp);

    return newLL;
}

void printIntLL(IntLinkedList list) {
    if (list == NULL || list->inner == NULL) return;

    IntNode current = list->inner->begin;
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

    if ((*list)->inner != NULL) {
        IntNode current = (*list)->inner->begin;
        IntNode temp = NULL;

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

int sizeIntLL(IntLinkedList list) {
    return list->inner->count;
}

bool isEmptyIntLL(IntLinkedList list) {
    return list == NULL || list->inner->count == 0;
}

void reverseIntLL(IntLinkedList list) {
    int* arr = malloc(list->inner->count * sizeof(int));
    copyLLToArray(list, arr);

    reverseArr(arr, list->inner->count);

    IntNode current = list->inner->begin;
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

    if (list1->inner->count != list2->inner->count)
        return false;

    IntNode current1 = list1->inner->begin;
    IntNode current2 = list2->inner->begin;

    while (current1 != NULL) {
        if (current1->data != current2->data)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

IntLinkedList emptyIfNullIntLL(IntLinkedList list) {
    return list == NULL ? newIntLinkedList(list) : list;
}

Iterator iteratorIntLL(IntLinkedList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->inner->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = INT_LL;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

// ===================== private funcs =======================

static void deleteFirstNodeInt(IntLinkedList list, IntNode current) {
    IntNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->inner->nodes = current;
    list->inner->begin = current;
    list->inner->count--;
    list->inner->index--;
    free(temp);
}

static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous) {
    IntNode temp = NULL;

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

static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeInt(list, current);
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

static void toArrAndSort(IntLinkedList list, int* arr) {
    IntNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    qsort(arr, list->inner->count, sizeof(int), compareInt);
}

static void fillNodeInt(IntNode node, int num, int* index) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

static int indexOf(int* arr, int size, int num) {
    for (int i = 0; i < size; ++i) {
        if (num == arr[i]) {
            return i;
        }
    }

    return -1;
}

static void copyLLToArray(IntLinkedList list, int* arr) {
    IntNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
}

static IntLinkedList copyIntLL(IntLinkedList list) {
    IntLinkedList temp = newIntLinkedList(temp);
    IntNode current = list->inner->begin;

    while (current != NULL) {
        addIntElemLL(temp, current->data);
        current = current->next;
    }
    return temp;
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
