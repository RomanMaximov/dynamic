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


void addStrLL(StrLinkedList, string);
void addArrCharLL(StrLinkedList, char* arr);
void addAllStrLL(StrLinkedList, void*);
string getStrLL(StrLinkedList, int);
bool setStrLL(StrLinkedList, int, string);
int indexOfStrLL(StrLinkedList, string);
void sortStrLL(StrLinkedList);
void sortStrLLReverse(StrLinkedList);
void clearStrLL(StrLinkedList);
bool containsStrLL(StrLinkedList, string);
bool containsAllStrLL(StrLinkedList, void*);
bool containsAnyStrLL(StrLinkedList, void*);
bool removeStrLL(StrLinkedList, int); // by index
bool removeAllStrLL(StrLinkedList, void*);
StrLinkedList subtractStrLL(StrLinkedList, StrLinkedList);
void reverseStrLL(StrLinkedList);
bool isEqualListsStrLL(StrLinkedList, StrLinkedList);
bool isEmptyStrLL(StrLinkedList);
int sizeStrLL(StrLinkedList);

string toStrStrLL(StrLinkedList);
void printStrLL(StrLinkedList);
void deleteStrLL(StrLinkedList*);


#endif
