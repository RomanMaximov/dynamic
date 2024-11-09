//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "linkedlist.h"

// structures
typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct LinkedListInt {
    int count;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} LinkedListInt;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;


// prototypes
void static fillNode(IntNode node, int num);
void static insertBeginInt(IntLinkedList list, int num);


// funcs
IntLinkedList newIntLinkedList() {
    IntLinkedList list = malloc(sizeof(IntLinkedList));
    list->count = 0;
    list->nodes = NULL;
    return list;
}

IntLinkedList linkedListOfInt(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(IntLinkedList));
    list->count = 0;
    list->nodes = NULL;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntElemLL(list, va_arg(param, int));
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

void static insertBeginInt(IntLinkedList list, int num) {
    IntNode newNodeStart = NULL;
    IntNode newNodeEnd = NULL;
    IntNode current = NULL;

    if (list->count == 0) {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNode(newNodeEnd, num);
        }

        newNodeEnd = list->nodes;
        list->nodes = newNodeEnd;
        list->begin = list->nodes;
        list->end = newNodeEnd;
    } else {
        newNodeStart = malloc(sizeof(NodeInt));
        if (newNodeStart != NULL) {
            fillNode(newNodeStart, num);
        }

        newNodeStart->next = list->nodes;
        list->nodes->prev = newNodeStart;
        list->nodes = newNodeStart;
        list->begin = list->nodes;
    }

    list->count++;
}

void addIntElemLL(IntLinkedList list, int num) {
    IntNode newNodeEnd = NULL;
    IntNode newNode = NULL;
    IntNode current = list->end;

    if (list->count == 0) {
        newNode = malloc(sizeof(NodeInt));
        if (newNode != NULL) {
            fillNode(newNode, num);
        }

        newNode->next = list->nodes;
        list->nodes = newNode;
        list->begin = list->nodes;
        list->end = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeInt));
        if (newNodeEnd != NULL) {
            fillNode(newNodeEnd, num);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->end = newNodeEnd;
    }

    list->count++;
}

void printIntLL(IntLinkedList list) {
    IntNode current = list->nodes;
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
    IntNode current = list->nodes;
    IntNode temp = NULL;

    if (list != NULL) {
        list->count = 0;
        list->begin = NULL;
        list->end = NULL;
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(list);
}

void static fillNode(IntNode node, int num) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
}