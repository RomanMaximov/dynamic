//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef INTLINKEDLIST_H
#define INTLINKEDLIST_H

#include "../linkedlist.h"

typedef struct LinkedListInt LinkedListInt;
typedef struct Itr Itr;
typedef LinkedListInt* IntLinkedList;
typedef Itr* Iterator;


void addIntElemLL(IntLinkedList, int);
void addAllIntElemLL(IntLinkedList, IntLinkedList);
int getIntElemLL(IntLinkedList, int);
bool setIntElemLL(IntLinkedList, int, int);
int indexOfIntLL(IntLinkedList, int);

// toString

void sortIntLL(IntLinkedList);
void sortIntLLReverse(IntLinkedList);
void clearIntLL(IntLinkedList);
bool containsIntLL(IntLinkedList, int);
bool containsAllIntLL(IntLinkedList, IntLinkedList);
bool containsAnyIntLL(IntLinkedList, IntLinkedList);
bool removeIntLL(IntLinkedList, int);
bool removeAllIntLL(IntLinkedList, IntLinkedList);
IntLinkedList subtractIntLL(IntLinkedList, IntLinkedList);
bool isEmptyIntLL(IntLinkedList);
void reverseIntLL(IntLinkedList);
bool isEqualListsIntLL(IntLinkedList, IntLinkedList);
IntLinkedList emptyIfNullIntLL(IntLinkedList);
int sizeIntLL(IntLinkedList);
Iterator iteratorIntLL(IntLinkedList);

void printIntLL(IntLinkedList);
void deleteIntLL(IntLinkedList*);


#endif
