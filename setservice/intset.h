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


void addIntSet(IntSet, int);
void addAllIntSet(IntSet, void*);
void clearIntSet(IntSet);
bool containsIntSet(IntSet, int);
bool containsAllIntSet(IntSet, void*);
bool containsAnyIntSet(IntSet, void*);
bool removeIntSet(IntSet, int);
bool removeAllIntSet(IntSet, void*);
IntSet subtractIntSet(IntSet, void*);
bool isEmptyIntSet(IntSet);
bool isEqualsIntSet(IntSet, IntSet);
IntSet emptyIfNullIntSet(IntSet);
int sizeIntSet(IntSet);
string toStrIntSet(IntSet);
Iterator iteratorIntSet(IntSet);

void printIntSet(IntSet);
void deleteIntSet(IntSet*);

// for debugging
void printTree(IntSet set);

#endif
