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
typedef struct String String;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;
typedef String* string;

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


void printIntLL(IntLinkedList);
//void printDoubleLL(DoubleLinkedList);
//void printStrLL(StrLinkedList);


void deleteIntLL(IntLinkedList);
//void deleteDoubleLL(DoubleLinkedList);
//void deleteStrLL(StrLinkedList);

void addIntElemLL(IntLinkedList, int, int*);
//void addDoubleElemLL(DoubleLinkedList, double);
//void addStrElemLL(StrLinkedList, string);

void addAllIntElemLL(IntLinkedList, IntLinkedList);
//void addDoubleElemLL(DoubleLinkedList, DoubleLinkedList);
//void addStrElemLL(StrLinkedList, StrLinkedList);

int getIntElemLL(IntLinkedList, int);
//double getDoubleElemLL(DoubleLinkedList, int);
//string getStrElemLL(StrLinkedList, int);

bool setIntElemLL(IntLinkedList, int, int);
//bool setDoubleElemLL(DoubleLinkedList, int, double);
//bool setStrElemLL(StrLinkedList, int, string);

int indexOfIntLL(IntLinkedList, int);
//double indexOfDoubleLL(DoubleLinkedList, double);
//string indexOfStrLL(StrLinkedList, int);

// toString

void sortIntLL(IntLinkedList);
//void sortDoubleLL(DoubleLinkedList);
//void sortStrLL(StrLinkedList);

void clearIntLL(IntLinkedList);
//void clearDoubleLL(DoubleLinkedList);
//void clearStrLL(StrLinkedList);

bool containsIntLL(IntLinkedList, int);
//bool containsDoubleLL(DoubleLinkedList, double);
//bool containsStrLL(StrLinkedList, string);

bool containsAllIntLL(IntLinkedList, IntLinkedList);
//bool containsAllDoubleLL(DoubleLinkedList, DoubleLinkedList);
//bool containsAllStrLL(StrLinkedList, StrLinkedList);

bool containsAnyIntLL(IntLinkedList, IntLinkedList);
//bool containsAnyDoubleLL(DoubleLinkedList, DoubleLinkedList);
//bool containsAnyStrLL(StrLinkedList, StrLinkedList);

bool removeIntLL(IntLinkedList, int);
//bool removeDoubleLL(DoubleLinkedList, int);
//bool removeStrLL(StrLinkedList, int);

// removeAll
// subtract
// isEmpty
// reverseList
// isEqualLists
// emptyIfNull

#endif
