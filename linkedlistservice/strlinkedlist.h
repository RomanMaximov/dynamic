//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef STRLINKEDLIST_H
#define STRLINKEDLIST_H

#include <stdio.h>
#include "../linkedlist.h"

typedef struct LinkedListStr LinkedListStr;
typedef LinkedListStr* StrLinkedList;
typedef struct String String;
typedef String* string;


int sizeStrLinkedList(StrLinkedList);    // TODO

bool isEmptyStrLinkedList(StrLinkedList);    // TODO

//void insertBeginStr(StrLinkedList, string);

void printStrLL(StrLinkedList);    // TODO

void deleteStrLL(StrLinkedList);    // TODO

void addStrElemLL(StrLinkedList, string);    // TODO

void addAllStrElemLL(StrLinkedList, StrLinkedList);    // TODO

string getStrElemLL(StrLinkedList, int);    // TODO

bool setStrElemLL(StrLinkedList, int, string);    // TODO

string indexOfStrLL(StrLinkedList, int);    // TODO

// toString

void sortStrLL(StrLinkedList);    // TODO

void clearStrLL(StrLinkedList);    // TODO

bool containsStrLL(StrLinkedList, string);    // TODO

bool containsAllStrLL(StrLinkedList, StrLinkedList);    // TODO

bool containsAnyStrLL(StrLinkedList, StrLinkedList);    // TODO

bool removeStrLL(StrLinkedList, int); // by index

bool removeAllStrLL(StrLinkedList, StrLinkedList);    // TODO

StrLinkedList subtractStrLL(StrLinkedList, StrLinkedList);    // TODO

void reverseStrLL(StrLinkedList);    // TODO

bool isEqualListsStrLL(StrLinkedList, StrLinkedList);    // TODO

StrLinkedList emptyIfNullStrLL(StrLinkedList);    // TODO


#endif
