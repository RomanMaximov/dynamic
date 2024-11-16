//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdio.h>
#include "../linkedlist.h"

typedef struct LinkedListDouble LinkedListDouble;
typedef LinkedListDouble* DoubleLinkedList;


int sizeDoubleLinkedList(DoubleLinkedList);    // TODO

bool isEmptyDoubleLinkedList(DoubleLinkedList);    // TODO

//void insertBeginDouble(DoubleLinkedList, double );    // TODO

void printDoubleLL(DoubleLinkedList);    // TODO

void deleteDoubleLL(DoubleLinkedList);    // TODO

void addDoubleElemLL(DoubleLinkedList, double);    // TODO

void addAllDoubleElemLL(DoubleLinkedList, DoubleLinkedList);    // TODO

double getDoubleElemLL(DoubleLinkedList, int);    // TODO

bool setDoubleElemLL(DoubleLinkedList, int, double);    // TODO

double indexOfDoubleLL(DoubleLinkedList, double);    // TODO

// toString

void sortDoubleLL(DoubleLinkedList);    // TODO

void clearDoubleLL(DoubleLinkedList);    // TODO

bool containsDoubleLL(DoubleLinkedList, double);    // TODO

bool containsAllDoubleLL(DoubleLinkedList, DoubleLinkedList);    // TODO

bool containsAnyDoubleLL(DoubleLinkedList, DoubleLinkedList);    // TODO

bool removeDoubleLL(DoubleLinkedList, int); // by index   // TODO

bool removeAllDoubleLL(DoubleLinkedList, DoubleLinkedList);    // TODO

DoubleLinkedList subtractDoubleLL(DoubleLinkedList, DoubleLinkedList);    // TODO

bool isEmptyDoubleLL(DoubleLinkedList);    // TODO

void reverseDoubleLL(DoubleLinkedList);    // TODO

bool isEqualListsDoubleLL(DoubleLinkedList, DoubleLinkedList);    // TODO

DoubleLinkedList emptyIfNullDoubleLL(DoubleLinkedList);    // TODO


#endif
