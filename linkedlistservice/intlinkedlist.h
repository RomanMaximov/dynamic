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


void addIntLL(IntLinkedList, int);
void addAllIntLL(IntLinkedList, void*);
int getIntLL(IntLinkedList, int);
bool setIntLL(IntLinkedList, int, int);
int indexOfIntLL(IntLinkedList, int);
void sortIntLL(IntLinkedList);
void sortIntLLReverse(IntLinkedList);
void clearIntLL(IntLinkedList);
bool containsIntLL(IntLinkedList, int);
bool containsAllIntLL(IntLinkedList, void*);
bool containsAnyIntLL(IntLinkedList, void*);
bool removeIntLL(IntLinkedList, int);
bool removeAllIntLL(IntLinkedList, void*);
IntLinkedList subtractIntLL(IntLinkedList, IntLinkedList);
bool isEmptyIntLL(IntLinkedList);
void reverseIntLL(IntLinkedList);
bool isEqualListsIntLL(IntLinkedList, IntLinkedList);
int sizeIntLL(IntLinkedList);
Iterator iteratorIntLL(IntLinkedList);

string toStrIntLL(IntLinkedList);
void printIntLL(IntLinkedList);
void deleteIntLL(IntLinkedList*);


#endif
