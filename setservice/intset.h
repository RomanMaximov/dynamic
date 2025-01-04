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

#endif
