//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>
#include "collectiontypes.h"


typedef struct Itr Itr;
typedef struct String String;

typedef String* string;
typedef Itr* Iterator;

Iterator iterator(void*);
bool hasNext(Iterator);
int nextInt(Iterator);
double nextDouble(Iterator);
string nextStr(Iterator);
void deleteItr(Iterator*);

#endif
