//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef INTARRAYLIST_H
#define INTARRAYLIST_H

#include "../arraylist.h"

typedef struct ArrayListInt ArrayListInt;
typedef struct Itr Itr;
typedef ArrayListInt* IntList;
typedef Itr* Iterator;


void addIntList(IntList, int);
void addAllIntList(IntList, IntList);
int getIntList(IntList, int);
bool setIntList(IntList, int, int);
int indexOfIntList(IntList, int);
void sortIntList(IntList);
void sortIntListReverse(IntList);
void clearIntList(IntList);
bool containsIntList(IntList, int);
bool containsAllIntList(IntList, IntList);
bool containsAnyIntList(IntList, IntList);
bool removeIntList(IntList, int);
bool removeAllIntList(IntList, IntList);
IntList subtractIntList(IntList, IntList);
bool isEmptyIntList(IntList);
void reverseIntList(IntList);
bool isEqualsIntList(IntList, IntList);
IntList emptyIfNullIntList(IntList);
int sizeIntList(IntList);
string toStringIntList(IntList);
Iterator iteratorIntList(IntList);

void printIntList(IntList);
void deleteIntList(IntList*);

#endif 
