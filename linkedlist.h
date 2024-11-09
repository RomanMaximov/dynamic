//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include "dynamic.h"


typedef struct LinkedListInt LinkedListInt;
typedef struct NodeInt NodeInt;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;


IntLinkedList newIntLinkedList();
// DoubleLinkedList newDoubleLinkedList();
// StringLinkedList newStrLinkedList();

IntLinkedList linkedListOfInt(IntLinkedList, int, ...);

int sizeIntLinkedList(IntLinkedList);
// int sizeDoubleLinkedList(DoubleLinkedList);
// int sizeStrLinkedList(StringLinkedList);

bool isEmptyIntLinkedList(IntLinkedList);
// bool isEmptyDoubleLinkedList(DoubleLinkedList);
// bool isEmptyStrLinkedList(StringLinkedList);


//void insertBeginInt(IntLinkedList, int);
// void insertBeginDouble(DoubleLinkedList, double );
// void insertBeginStr(StringLinkedList, string);


//void insertEndInt(IntLinkedList, int);  // add
// void insertEndDouble(DoubleLinkedList, double );
// void insertEndStr(StringLinkedList, string);




void printIntLL(IntLinkedList);


void deleteIntLL(IntLinkedList);


void addIntElemLL(IntLinkedList, int);
//void addDoubleElemLL(DoubleLinkedList, double);
//void addStrElemLL(StrLinkedList, string);

// addAll
// get(int index)
// set(index, elem)
// indexOf
// toString
// sort
// clear
// contains
// containsAll
// containsAny
// remove
// removeAll
// subtract
// isEmpty
// reverseList
// isEqualLists
// emptyIfNull

#endif
