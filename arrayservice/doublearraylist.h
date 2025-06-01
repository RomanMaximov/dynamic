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


void addDoubleList(DoubleList, double);
void addAllDoubleList(DoubleList, void*);
double getDoubleList(DoubleList, int);
bool setDoubleList(DoubleList, int, double);
int indexOfDoubleList(DoubleList, double);
void sortDoubleList(DoubleList);
void sortDoubleListReverse(DoubleList);
void clearDoubleList(DoubleList);
bool containsDoubleList(DoubleList, double);
bool containsAllDoubleList(DoubleList, void*);
bool containsAnyDoubleList(DoubleList, void*);
bool removeDoubleList(DoubleList, int);
bool removeAllDoubleList(DoubleList, void*);
DoubleList subtractDoubleList(DoubleList, void*);
bool isEmptyDoubleList(DoubleList);
void reverseDoubleList(DoubleList);
bool isEqualsDoubleList(DoubleList, DoubleList);
int sizeDoubleList(DoubleList);
string toStrDoubleList(DoubleList);
Iterator iteratorDoubleList(DoubleList);

void printDoubleList(DoubleList);
void deleteDoubleList(DoubleList*);

#endif 
