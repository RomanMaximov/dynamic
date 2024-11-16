//
// Created by Roman Maximov on 14.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ARRCUSTOM_H
#define ARRCUSTOM_H


typedef struct IntArraySS {
    struct InnerIntArray* inner;
    bool (*add)(struct IntArraySS* list, int num);
} IntArraySS;


typedef struct InnerIntArray InnerIntArray;
typedef IntArraySS* IntListSS;

IntListSS newIntArraySS(IntListSS temp);

#endif
