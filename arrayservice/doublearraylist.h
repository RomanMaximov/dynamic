//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef DOUBLEARRAYLIST_H
#define DOUBLEARRAYLIST_H

#include "../arraylist.h"

typedef struct ArrayListDouble ArrayListDouble;
typedef struct Itr Itr;
typedef ArrayListDouble* DoubleList;
typedef Itr* Iterator;


void addDoubleElemList(DoubleList, double);
void addAllDoubleElemList(DoubleList, DoubleList);
int getDoubleElemList(DoubleList, int);
bool setDoubleElemList(DoubleList, int, double);
int indexOfDoubleList(DoubleList, double);

// toString

void sortDoubleList(DoubleList);
void sortDoubleListReverse(DoubleList);
void clearDoubleList(DoubleList);
bool containsDoubleList(DoubleList, double );
bool containsAllDoubleList(DoubleList, DoubleList);
bool containsAnyDoubleList(DoubleList, DoubleList);
bool removeDoubleList(DoubleList, double );
bool removeAllDoubleList(DoubleList, DoubleList);
DoubleList subtractDoubleList(DoubleList, DoubleList);
bool isEmptyDoubleList(DoubleList);
void reverseDoubleList(DoubleList);
bool isEqualListsDoubleList(DoubleList, DoubleList);
DoubleList emptyIfNullDoubleList(DoubleList);
int sizeDoubleList(DoubleList);
Iterator iteratorDoubleList(DoubleList);

void printDoubleList(DoubleList);
void deleteDoubleList(DoubleList*);

#endif 
