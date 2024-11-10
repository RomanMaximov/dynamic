//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "linkedlist.h"

// structures
typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct LinkedListInt {
    int count;
    int index;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} LinkedListInt;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;


// prototypes
void static insertBeginInt(IntLinkedList list, int num, int* index);
static void quickSortInt(int* arr, int low, int high);
static bool binarySearchInt(int elem, const int* arr, int high);
void static fillNodeInt(IntNode node, int num, int* index);
static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous);
static void deleteFirstNodeInt(IntLinkedList list, IntNode current);
static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index);


// funcs
IntLinkedList newIntLinkedList() {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->count = 0;
    list->index = 0;
    list->nodes = NULL;
    return list;
}

IntLinkedList linkedListOfInt(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->count = 0;
    list->index = 0;
    list->nodes = NULL;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntElemLL(list, va_arg(param, int), &list->index);
    }
    va_end(param);
    return list;
}

int sizeList(IntLinkedList list) {
    return list->count;
}

bool isEmptyIntLinkedList(IntLinkedList list) {
    return list == NULL || list->count == 0;
}

void static insertBeginInt(IntLinkedList list, int num, int* index) {
    IntNode newNodeStart = NULL;
    IntNode newNodeEnd = NULL;
    IntNode current = NULL;

    if (list->count == 0) {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num, index);
        }

        newNodeEnd = list->nodes;
        list->nodes = newNodeEnd;
        list->begin = list->nodes;
        list->end = newNodeEnd;
    } else {
        newNodeStart = malloc(sizeof(NodeInt));
        if (newNodeStart != NULL) {
            fillNodeInt(newNodeStart, num, index);
        }

        newNodeStart->next = list->nodes;
        list->nodes->prev = newNodeStart;
        list->nodes = newNodeStart;
        list->begin = list->nodes;
    }

    list->count++;
}

void addIntElemLL(IntLinkedList list, int num, int* index) {
    IntNode newNodeEnd = NULL;
    IntNode newNode = NULL;
    IntNode current = list->end;

    if (list->count == 0) {
        newNode = malloc(sizeof(NodeInt));
        if (newNode != NULL) {
            fillNodeInt(newNode, num, index);
        }

        newNode->next = list->nodes;
        list->nodes = newNode;
        list->begin = list->nodes;
        list->end = newNode;
        list->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNodeInt(newNodeEnd, num, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->end = newNodeEnd;
    }

    list->count++;
}

void addAllIntElemLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return;

    IntNode current = list2->nodes;
    while (current != NULL) {
        addIntElemLL(list1, current->data, &list1->index);
        current = current->next;
    }
}

int getIntElemLL(IntLinkedList list, int index) {
    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return INT_MAX;
    }

    int tempIndex = 0;
    IntNode current = list->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return INT_MAX;
}

void sortIntLL(IntLinkedList list) {
    int arr[list->count];
    IntNode current = list->begin;
    IntNode temp = list->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    quickSortInt(arr, 0, list->count);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

bool setIntElemLL(IntLinkedList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return false;
    }

    int tempIndex = 0;
    IntNode current = list->begin;
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

int indexOfIntLL(IntLinkedList list, int num) {
    if (list == NULL)
        return -1;

    IntNode current = list->begin;
    while (current != NULL) {
        if (num == current->data)
            return list->index;

        current = current->next;
    }
    return -1;
}

void clearIntLL(IntLinkedList list) {
    if (list == NULL)
        return;

    IntNode current = list->begin;
    IntNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->count = 0;
    list->index = 0;
    list->begin = NULL;
    list->end = NULL;
    list->nodes = NULL;
}

bool containsIntLL(IntLinkedList list, int num) {
    if (list == NULL) return false;

    IntNode current = list->begin;
    while (current != NULL) {
        if (num == current->data)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    int arr[list1->count];
    IntNode current = list1->begin;
    IntNode temp = list2->begin;

    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    quickSortInt(arr, 0, list1->count);

    while (temp != NULL) {
        if (!binarySearchInt(temp->data, arr, list1->count - 1))
            return false;

        temp = temp->next;
    }

    return true;
}

bool containsAnyIntLL(IntLinkedList list1, IntLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    int arr[list1->count];
    IntNode current = list1->begin;
    IntNode temp = list2->begin;

    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    quickSortInt(arr, 0, list1->count);

    while (temp != NULL) {
        if (binarySearchInt(temp->data, arr, list1->count - 1))
            return true;

        temp = temp->next;
    }

    return false;
}

bool removeIntLL(IntLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return false;
    }

    IntNode current = list->begin;
    IntNode previous = NULL;
    IntNode temp = NULL;

    if (list->count == 1) {
        temp = list->begin;
        list->nodes = NULL;
        list->begin = NULL;
        list->end = NULL;
        list->count = 0;
        list->index = 0;
        free(temp);
        return true;
    }

    return removeNodeInt(list, current, previous, index);
}

void printIntLL(IntLinkedList list) {
    IntNode current = list->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->next == NULL)
            printf("%d", current->data);
        else
            printf("%d,", current->data);
        current = current->next;
    }
    printf("%s\n", "]");
}


void deleteIntLL(IntLinkedList list) {
    if (list == NULL)
        return;

    IntNode current = list->begin;
    IntNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    list->begin = NULL;
    list->end = NULL;
    list->nodes = NULL;

    free(list);
}

static void fillNodeInt(IntNode node, int num, int* index) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

static void deleteFirstNodeInt(IntLinkedList list, IntNode current) {
    IntNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->nodes = current;
    list->begin = current;
    list->count--;
    list->index--;
    free(temp);
}

static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous) {
    IntNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->end = previous;

    previous->next = current;
    list->count--;
    list->index--;
    free(temp);
}

static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeInt(list, current);
        return true;
    } else {
        previous = list->begin;
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

static void quickSortInt(int* arr, int low, int high) {
    int i = low;
    int j = high - 1;
    int temp;
    do {
        while (j > i) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quickSortInt(arr, i + 1, high);
    if (low < j - 1)
        quickSortInt(arr, low, j);
}

static bool binarySearchInt(int elem, const int* arr, int high) {
    int low, middle;
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