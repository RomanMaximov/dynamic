//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "../linkedlist.h"

typedef struct LinkedListDouble LinkedListDouble;
typedef LinkedListDouble* DoubleLinkedList;


void addDoubleLL(DoubleLinkedList, double);
void addAllDoubleLL(DoubleLinkedList, DoubleLinkedList);
double getDoubleLL(DoubleLinkedList, int);
bool setDoubleLL(DoubleLinkedList, int, double);
int indexOfDoubleLL(DoubleLinkedList, double);
void sortDoubleLL(DoubleLinkedList);
void sortDoubleLLReverse(DoubleLinkedList);
void clearDoubleLL(DoubleLinkedList);
bool containsDoubleLL(DoubleLinkedList, double);
bool containsAllDoubleLL(DoubleLinkedList, DoubleLinkedList);
bool containsAnyDoubleLL(DoubleLinkedList, DoubleLinkedList);
bool removeDoubleLL(DoubleLinkedList, int);
bool removeAllDoubleLL(DoubleLinkedList, DoubleLinkedList);
DoubleLinkedList subtractDoubleLL(DoubleLinkedList, DoubleLinkedList);
bool isEmptyDoubleLL(DoubleLinkedList);
void reverseDoubleLL(DoubleLinkedList);
bool isEqualListsDoubleLL(DoubleLinkedList, DoubleLinkedList);
DoubleLinkedList emptyIfNullDoubleLL(DoubleLinkedList);

int sizeDoubleLL(DoubleLinkedList);
string toStrDoubleLL(DoubleLinkedList);
void printDoubleLL(DoubleLinkedList);
void deleteDoubleLL(DoubleLinkedList*);

#endif
