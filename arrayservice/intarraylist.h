//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef INTARRAYLIST_H
#define INTARRAYLIST_H

#include "../arraylist.h"
#include "../string.h"

typedef struct ArrayListInt ArrayListInt;
typedef struct Itr Itr;
typedef ArrayListInt* IntList;
typedef Itr* Iterator;
typedef struct String* string;


void addIntList(IntList, int);
void addAllIntList(IntList, void*);
int getIntList(IntList, int);
bool setIntList(IntList, int, int);
int indexOfIntList(IntList, int);
void sortIntList(IntList);
void sortIntListReverse(IntList);
void clearIntList(IntList);
bool containsIntList(IntList, int);
bool containsAllIntList(IntList, void*);
bool containsAnyIntList(IntList, void*);
bool removeIntList(IntList, int);
bool removeAllIntList(IntList, void*);
void* subtractIntList(IntList, void*);
bool isEmptyIntList(IntList);
void reverseIntList(IntList);
bool isEqualsIntList(IntList, IntList);
int sizeIntList(IntList);
void* toStrIntList(IntList);

void printIntList(IntList);
void deleteIntList(IntList*);

#endif 
