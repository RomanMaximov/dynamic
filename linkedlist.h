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
//#include "dynamic.h"


//typedef struct LinkedListInt LinkedListInt;
typedef struct LinkedListInt {
    struct InnnerIntLL* inner;   // private field
    // funcs pointers
    void (*add)(struct LinkedListInt* list, int number);
    void (*addAll)(struct LinkedListInt* list1, struct LinkedListInt* list2);
    int (*get)(struct LinkedListInt* list, int index);
    bool (*set)(struct LinkedListInt* list, int index, int number);
    int (*indexOf)(struct LinkedListInt* list, int number);
    void (*sort)(struct LinkedListInt* list);
    void (*clear)(struct LinkedListInt* list);
    bool (*contains)(struct LinkedListInt* list, int number);
    bool (*containsAll)(struct LinkedListInt* list1, struct LinkedListInt* list2);
    bool (*containsAny)(struct LinkedListInt* list1, struct LinkedListInt* list2);
    bool (*removeElem)(struct LinkedListInt* list, int number);

    int (*size)(struct LinkedListInt* list);
    bool (*isEmpty)(struct LinkedListInt* list);
    void (*print)(struct LinkedListInt* list);
    void (*delete)(struct LinkedListInt* list);
} LinkedListInt;

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

void addIntElemLL(IntLinkedList, int);  // done
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
