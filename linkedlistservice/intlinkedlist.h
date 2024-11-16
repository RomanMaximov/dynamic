//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef INTLINKEDLIST_H
#define INTLINKEDLIST_H

#include <stdio.h>
#include "../linkedlist.h"

typedef struct LinkedListInt LinkedListInt;
typedef LinkedListInt* IntLinkedList;


int sizeIntLinkedList(IntLinkedList);

bool isEmptyIntLinkedList(IntLinkedList);

void printIntLL(IntLinkedList);

void deleteIntLL(IntLinkedList);

void addIntElemLL(IntLinkedList, int);

void addAllIntElemLL(IntLinkedList, IntLinkedList);

int getIntElemLL(IntLinkedList, int);

bool setIntElemLL(IntLinkedList, int, int);

int indexOfIntLL(IntLinkedList, int);

// toString

void sortIntLL(IntLinkedList);

void clearIntLL(IntLinkedList);

bool containsIntLL(IntLinkedList, int);

bool containsAllIntLL(IntLinkedList, IntLinkedList);

bool containsAnyIntLL(IntLinkedList, IntLinkedList);

bool removeIntLL(IntLinkedList, int);

bool removeAllIntLL(IntLinkedList, IntLinkedList);  // TODO

IntLinkedList subtractIntLL(IntLinkedList, IntLinkedList);  // TODO

bool isEmptyIntLL(IntLinkedList);  // TODO

void reverseIntLL(IntLinkedList);  // TODO

bool isEqualListsIntLL(IntLinkedList, IntLinkedList);  // TODO

IntLinkedList emptyIfNullIntLL(IntLinkedList);  // TODO


#endif
