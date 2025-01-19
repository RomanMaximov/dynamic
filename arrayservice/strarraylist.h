//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef STRARRAYLIST_H
#define STRARRAYLIST_H

#include "../arraylist.h"

typedef struct ArrayListStr ArrayListStr;
typedef struct String String;
typedef struct Itr Itr;

typedef ArrayListStr* StrList;
typedef String* string;
typedef Itr* Iterator;


void addStrList(StrList, string);
void addCharArrList(StrList list, char* str);
void addAllStrList(StrList, StrList);
string getStrList(StrList, int);
bool setStrList(StrList, int, string);
int indexOfStrList(StrList, string);
void sortStrList(StrList);
void sortStrListReverse(StrList);
void clearStrList(StrList);
bool containsStrList(StrList, string);
bool containsAllStrList(StrList, StrList);
bool containsAnyStrList(StrList, StrList);
bool removeStrList(StrList, int);
bool removeAllStrList(StrList, StrList);
StrList subtractStrList(StrList, StrList);
bool isEmptyStrList(StrList);
void reverseStrList(StrList);
bool isEqualsStrList(StrList, StrList);
StrList emptyIfNullStrList(StrList);
int sizeStrList(StrList);
string toStringStrList(StrList list);
Iterator iteratorStrList(StrList);

void printStrList(StrList);
void deleteStrList(StrList*);

#endif 
