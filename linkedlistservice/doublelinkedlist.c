//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
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

static void fillNodeDouble(DoubleNode node, double num, int* index) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

