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


void addStrElemLL(StrLinkedList, string);
void addArrCharLL(StrLinkedList, char* arr);

void addAllStrElemLL(StrLinkedList, StrLinkedList);

string getStrElemLL(StrLinkedList, int);

bool setStrElemLL(StrLinkedList, int, string);

int indexOfStrLL(StrLinkedList, string);

// toString

void sortStrLL(StrLinkedList);

void clearStrLL(StrLinkedList);

bool containsStrLL(StrLinkedList, string);

bool containsAllStrLL(StrLinkedList, StrLinkedList);

bool containsAnyStrLL(StrLinkedList, StrLinkedList);

bool removeStrLL(StrLinkedList, int); // by index

bool removeAllStrLL(StrLinkedList, StrLinkedList);    // TODO

StrLinkedList subtractStrLL(StrLinkedList, StrLinkedList);    // TODO

void reverseStrLL(StrLinkedList);    // TODO

bool isEqualListsStrLL(StrLinkedList, StrLinkedList);    // TODO

StrLinkedList emptyIfNullStrLL(StrLinkedList);    // TODO

int sizeStrLinkedList(StrLinkedList);    // TODO

bool isEmptyStrLinkedList(StrLinkedList);    // TODO

void printStrLL(StrLinkedList);    // TODO

void deleteStrLL(StrLinkedList);    // TODO


#endif
