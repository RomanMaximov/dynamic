//
// Created by Roman Maximov on 10.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef DOUBLESET_H
#define DOUBLESET_H

#include "../set.h"

typedef struct SetDouble SetDouble;
typedef struct Itr Itr;
typedef SetDouble* DoubleSet;
typedef Itr* Iterator;


void addDoubleElemSet(DoubleSet, double);
void addAllDoubleElemSet(DoubleSet, DoubleSet);
void clearDoubleSet(DoubleSet);
bool containsDoubleSet(DoubleSet, double);
bool containsAllDoubleSet(DoubleSet, DoubleSet);
bool containsAnyDoubleSet(DoubleSet, DoubleSet);
bool removeDoubleSet(DoubleSet, double);
bool removeAllDoubleSet(DoubleSet, DoubleSet);
bool isEmptyDoubleSet(DoubleSet);
bool isEqualsDoubleSet(DoubleSet, DoubleSet);
DoubleSet emptyIfNullDoubleSet(DoubleSet);
int sizeDoubleSet(DoubleSet);
Iterator iteratorDoubleSet(DoubleSet);

void printDoubleSet(DoubleSet);
void deleteDoubleSet(DoubleSet*);

void printDoubleTree(DoubleSet set);

#endif
