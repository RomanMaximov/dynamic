//
// Created by Roman Maximov on 11.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef STRSET_H
#define STRSET_H

#include "../set.h"
#include "../arraylist.h"

typedef struct SetStr SetStr;
typedef struct Itr Itr;
typedef SetStr* StrSet;
typedef Itr* Iterator;


void addStrElemSet(StrSet, string);
void addCharElemSet(StrSet, char*);
void addAllStrElemSet(StrSet, StrSet);
void clearStrSet(StrSet);
bool containsStrSet(StrSet, string);
bool containsAllStrSet(StrSet, StrSet);
bool containsAnyStrSet(StrSet, StrSet);
bool removeStrSet(StrSet, string);
bool removeAllStrSet(StrSet, StrSet);
bool isEmptyStrSet(StrSet);
bool isEqualsStrSet(StrSet, StrSet);
StrSet emptyIfNullStrSet(StrSet);
int sizeStrSet(StrSet);
Iterator iteratorStrSet(StrSet);

void printStrSet(StrSet);
void deleteStrSet(StrSet*);

void printStrTree(StrSet set);

#endif 
