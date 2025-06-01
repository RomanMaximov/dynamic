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


void addDoubleSet(DoubleSet, double);
void addAllDoubleSet(DoubleSet, DoubleSet);
void clearDoubleSet(DoubleSet);
bool containsDoubleSet(DoubleSet, double);
bool containsAllDoubleSet(DoubleSet, DoubleSet);
bool containsAnyDoubleSet(DoubleSet, DoubleSet);
bool removeDoubleSet(DoubleSet, double);
bool removeAllDoubleSet(DoubleSet, DoubleSet);
DoubleSet subtractDoubleSet(DoubleSet, void*);
bool isEmptyDoubleSet(DoubleSet);
int sizeDoubleSet(DoubleSet);
string toStrDoubleSet(DoubleSet);

void printDoubleSet(DoubleSet);
void deleteDoubleSet(DoubleSet*);

// for debugging
void printDoubleTree(DoubleSet set);

#endif
