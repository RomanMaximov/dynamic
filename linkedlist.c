//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "linkedlist.h"
#include "linkedlistservice/intlinkedlist.h"

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

// LinkedList data encapsulation
typedef struct InnerIntLL {
    int count;
    int index;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} InnerIntLL;

typedef struct NodeDouble {
    double data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;

// LinkedList data encapsulation
typedef struct InnerDoubleLL {
    int count;
    int index;
    NodeDouble* nodes;
    NodeDouble* begin;
    NodeDouble* end;
} InnerDoubleLL;

typedef struct NodeStr {
    string data;
    struct NodeStr* next;
    struct NodeStr* prev;
} NodeStr;

// LinkedList data encapsulation
typedef struct InnerStrLL {
    int count;
    int index;
    NodeStr* nodes;
    NodeStr* begin;
    NodeStr* end;
} InnerStrLL;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;
typedef LinkedListDouble* DoubleLinkedList;
typedef NodeDouble* DoubleNode;
typedef LinkedListStr* StrLinkedList;
typedef NodeStr* StrNode;


// custom types
typedef enum TypeLL {
    INT_LL,
    DOUBLE_LL,
    STR_LL
} TypeLL;


// prototypes service funcs
static void insertBeginInt(IntLinkedList list, int num, int* index);
static void quickSortInt(int* arr, int low, int high);
static bool binarySearchInt(int elem, const int* arr, int high);
static void fillNodeInt(IntNode node, int num, int* index);
static void deleteNodeInt(IntLinkedList list, IntNode current, IntNode previous);
static void deleteFirstNodeInt(IntLinkedList list, IntNode current);
static bool removeNodeInt(IntLinkedList list, IntNode current, IntNode previous, int index);
static void toArrAndSort(IntLinkedList list, int* arr);
static void _initFuncs_(IntLinkedList list);

// prototypes common funcs
static void* add(TypeLL type);
static void* addAll(TypeLL type);
static void* get(TypeLL type);
static void* set(TypeLL type);
static void* indexOf(TypeLL type);
static void* sort(TypeLL type);
static void* clear(TypeLL type);
static void* contains(TypeLL type);
static void* containsAll(TypeLL type);
static void* containsAny(TypeLL type);
static void* removeElem(TypeLL type);

static void* size(TypeLL type);
static void* isEmpty(TypeLL type);
static void* print(TypeLL type);
static void* delete(TypeLL type);


// funcs
IntLinkedList newIntLinkedList() {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    _initFuncs_(list);
    return list;
}

IntLinkedList linkedListOfInt(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    _initFuncs_(list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntElemLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

int sizeList(IntLinkedList list) {
    return list->inner->count;
}

bool isEmptyIntLinkedList(IntLinkedList list) {
    return list == NULL || list->inner->count == 0;
}

/*static void insertBeginInt(IntLinkedList list, int num, int* index) {
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
}*/

/*void addIntElemLL(IntLinkedList list, int num) {
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
}*/

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

    quickSortInt(arr, 0, list->inner->count);

    index = 0;
    while (temp != NULL) {
        temp->data = arr[index++];
        temp = temp->next;
    }
}

/*bool setIntElemLL(IntLinkedList list, int index, int num) {
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
}*/

int indexOfIntLL(IntLinkedList list, int num) {
    if (list == NULL)
        return -1;

    IntNode current = list->inner->begin;
    while (current != NULL) {
        if (num == current->data)
            return list->inner->index;

        current = current->next;
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
    if (list1 == NULL || list2 == NULL) return false;

    int arr[list1->inner->count];
    IntNode temp = list2->inner->begin;

    toArrAndSort(list1, arr);

    while (temp != NULL) {
        if (!binarySearchInt(temp->data, arr, list1->inner->count - 1))
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
        if (binarySearchInt(temp->data, arr, list1->inner->count - 1))
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

void printIntLL(IntLinkedList list) {
    IntNode current = list->inner->begin;
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

    if (list->inner != NULL) {
        IntNode current = list->inner->begin;
        IntNode temp = NULL;

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }

        list->inner->begin = NULL;
        list->inner->end = NULL;
        list->inner->nodes = NULL;

        free(list->inner);
    }

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

static void toArrAndSort(IntLinkedList list, int* arr) {
    IntNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }

    quickSortInt(arr, 0, list->inner->count);
}

// common functions
static void* add(TypeLL type) {
    switch (type) {
        case INT_LL:
            return addIntElemLL;
    }

    return NULL;
}

static void* set(TypeLL type) {
    switch (type) {
        case INT_LL:
            return setIntElemLL;
    }

    return NULL;
}

 static void _initFuncs_(IntLinkedList list) {
    list->add = add(INT_LL);
    list->set = set(INT_LL);
}