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


void addIntElemList(IntList, int);
void addAllIntElemList(IntList, IntList);
int getIntElemList(IntList, int);
bool setIntElemList(IntList, int, int);
int indexOfIntList(IntList, int);

// toString

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
bool isEqualListsIntList(IntList, IntList);
IntList emptyIfNullIntList(IntList);
int sizeIntList(IntList);
Iterator iteratorIntList(IntList);

void printIntList(IntList);
void deleteIntList(IntList*);

#endif 
