//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef INTSET_H
#define INTSET_H

#include "../set.h"

typedef struct SetInt SetInt;
typedef struct Itr Itr;
typedef SetInt* IntSet;
typedef Itr* Iterator;


void addIntElemSet(IntSet, int);
void addAllIntElemSet(IntSet, IntSet);
void clearIntSet(IntSet);
bool containsIntSet(IntSet, int);
bool containsAllIntSet(IntSet, IntSet);
bool containsAnyIntSet(IntSet, IntSet);
bool removeIntSet(IntSet, int);
bool removeAllIntSet(IntSet, IntSet);
bool isEmptyIntSet(IntSet);
bool isEqualsIntSet(IntSet, IntSet);
IntSet emptyIfNullIntSet(IntSet);
int sizeIntSet(IntSet);
Iterator iteratorIntSet(IntSet);

void printIntSet(IntSet);
void deleteIntSet(IntSet*);

void printTree(IntSet set);

#endif
