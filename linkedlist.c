#include "linkedlist.h"


IntLinkedList newIntLinkedList() {
    IntLinkedList list = malloc(sizeof(IntLinkedList));
    list->count = 0;
    list->nodes = NULL;
    return list;
}

int sizeList(IntLinkedList list) {
    return (int)list->count;
}

bool isEmptyIntLinkedList(IntLinkedList list) {
    return list == NULL || list->count == 0;
}

void fillNode(IntNode node, int num) {
    node->data = num;
    node->next = NULL;
    node->prev = NULL;
}

void insertBegin(IntLinkedList list, int num) {
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

/*void insertEnd(IntLinkedList list, unsigned int num) {
    LinkedListInt* newNodeEnd = NULL;
    LinkedListInt* newNode = NULL;
    LinkedListInt* current = list->end;

    if (list->count == 0) {
        newNode = malloc(sizeof(LinkedListInt));
        if (newNode != NULL) {
            fillNode(newNode, num);
        }

        newNode->next = list->linkedList;
        list->linkedList = newNode;
        list->begin = list->linkedList;
        list->end = newNode;
    }
    else {
        newNodeEnd = malloc(sizeof(LinkedListInt));
        if (newNodeEnd != NULL) {
            fillNode(newNodeEnd, num);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->end = newNodeEnd;
    }

    list->count++;
}*/

/*IntLinkedList linkedListOf(int paramCount, ...) {
    IntLinkedList data = malloc(sizeof(intLinkedList));
    data->count = 0;
    data->linkedList = NULL;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        insertEnd(data, va_arg(param, int));
    }
    va_end(param);
    return data;
}*/

/*void printLinkedList(IntLinkedList list) {
    LinkedListInt* current = list->linkedList;
    printf("%s", "[");
    while (current != NULL) {
        if (current->next == NULL)
            printf("%d", current->number);
        else
            printf("%d,", current->number);
        current = current->next;
    }
    printf("%s\n", "]");
}*/

/*
void deleteLinkedList(IntLinkedList list) {
    if (list != NULL) {
        list->begin = NULL;
        list->end = NULL;
        if (list->linkedList != NULL) {
            free(list->linkedList);
        }
        free(list);
    }
}*/
