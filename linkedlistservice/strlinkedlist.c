//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include "strlinkedlist.h"
#include "../dynamicarray.h"

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

typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct StringArray {
    int count;
    String** str;
    int capacity;
} StringArray;

typedef struct NodeStr NodeStr;
typedef NodeStr* StrNode;
typedef String* string;
typedef StringArray* StringList;


// prototypes
static void fillNodeStr(StrNode node, char* s, int* index);
static void quickSortStr(String** strList, int low, int high);
int indexOfStrLL(StrLinkedList list, string s);
static bool binarySearchStr(string s, String** strList, int high);
static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index);
static void deleteFirstNodeStr(StrLinkedList list, StrNode current);
static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous);


// funcs
void addStrElemLL(StrLinkedList list, string s) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->inner->end;
    int* index = &list->inner->index;

    if (list->inner->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, s->data, index);
        }

        newNode->next = list->inner->nodes;
        list->inner->nodes = newNode;
        list->inner->begin = list->inner->nodes;
        list->inner->end = newNode;
        list->inner->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, s->data, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->inner->end = newNodeEnd;
    }

    list->inner->count++;
}

void addArrCharLL(StrLinkedList list, char* arr) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->inner->end;
    int* index = &list->inner->index;

    if (list->inner->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, arr, index);
        }

        newNode->next = list->inner->nodes;
        list->inner->nodes = newNode;
        list->inner->begin = list->inner->nodes;
        list->inner->end = newNode;
        list->inner->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, arr, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->inner->end = newNodeEnd;
    }

    list->inner->count++;
}

bool setStrElemLL(StrLinkedList list, int index, string s) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    int tempIndex = 0;
    StrNode current = list->inner->begin;
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

void addAllStrElemLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return;

    StrNode current = list2->inner->nodes;
    while (current != NULL) {
        addStrElemLL(list1, current->data);
        current = current->next;
    }
}

string getStrElemLL(StrLinkedList list, int index) {
    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return NULL;
    }

    int tempIndex = 0;
    StrNode current = list->inner->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return NULL;
}

void sortStrLL(StrLinkedList list) {
    StringList strList = newStrArray(strList);
    StrNode current = list->inner->begin;
    StrNode temp = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        addStrElem(strList, current->data);
        current = current->next;
    }

    quickSortStr(strList->str, 0, strList->count);

    index = 0;
    while (temp != NULL) {
        temp->data = stringOf((*(strList->str + index++))->data);
        temp = temp->next;
    }
    deleteArrayString(strList);
}

int indexOfStrLL(StrLinkedList list, string s) {
    if (list == NULL)
        return -1;

    StrNode current = list->inner->begin;
    int index = 0;
    while (current != NULL) {
        if (compareTo(s, current->data) == 1)
            return index;

        current = current->next;
        ++index;
    }
    return -1;
}

void clearStrLL(StrLinkedList list) {
    if (list == NULL)
        return;

    StrNode current = list->inner->begin;
    StrNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;

        deleteString(temp->data);
        free(temp);
    }

    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    list->inner->nodes = NULL;
}

bool containsStrLL(StrLinkedList list, string s) {
    if (list == NULL) return false;

    StrNode current = list->inner->begin;
    while (current != NULL) {
        if (compareTo(s, current->data) == 1)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count) return false;

    StringList tempList = newStrArray(tempList);
    StrNode current = list1->inner->begin;
    StrNode current2 = list2->inner->begin;

    while (current != NULL) {
        addStrElem(tempList, current->data);
        current = current->next;
    }

    quickSortStr(tempList->str, 0, tempList->count);

    while (current2 != NULL) {
        if (!binarySearchStr(current2->data, tempList->str, list1->inner->count)) {
            deleteArrayString(tempList);
            return false;
        }

        current2 = current2->next;
    }

    deleteArrayString(tempList);
    return true;
}

bool containsAnyStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    StringList tempList = newStrArray(tempList);
    StrNode current = list1->inner->begin;
    StrNode current2 = list2->inner->begin;

    while (current != NULL) {
        addStrElem(tempList, current->data);
        current = current->next;
    }

    quickSortStr(tempList->str, 0, tempList->count);

    while (current2 != NULL) {
        if (binarySearchStr(current2->data, tempList->str, list1->inner->count)) {
            deleteArrayString(tempList);
            return true;
        }

        current2 = current2->next;
    }

    deleteArrayString(tempList);
    return false;
}

bool removeStrLL(StrLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    StrNode current = list->inner->begin;
    StrNode previous = NULL;
    StrNode temp = NULL;

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

    return removeNodeStr(list, current, previous, index);
}

static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeStr(list, current);
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

        deleteNodeStr(list, current, previous);

        return true;
    }
}

static void deleteFirstNodeStr(StrLinkedList list, StrNode current) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->inner->nodes = current;
    list->inner->begin = current;
    list->inner->count--;
    list->inner->index--;
    deleteString(temp->data);
    free(temp);
}

static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->inner->end = previous;

    previous->next = current;
    list->inner->count--;
    list->inner->index--;
    deleteString(temp->data);
    free(temp);
}

static void quickSortStr(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareTo(*(strList + i), *(strList + j)) > 0) {
                temp = *(strList + i);
                *(strList + i) = *(strList + j);
                *(strList + j) = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareTo(*(strList + i), *(strList + j)) > 0) {
                temp = *(strList + i);
                *(strList + i) = *(strList + j);
                *(strList + j) = temp;
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

static bool binarySearchStr(string s, String** strList, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (compareTo(s, *(strList + middle)) < 0)
            high = middle - 1;
        else if (compareTo(s, *(strList + middle)) > 0)
            low = middle + 1;
        else
            return true;
    }
    return false;
}

static void fillNodeStr(StrNode node, char* s, int* index) {
    string temp = stringOf(s);
    node->data = temp;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}
