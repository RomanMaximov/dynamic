//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "setservice/intset.h"

// structures
typedef struct String String;

typedef struct SetInt {
    struct InnerIntSet* inner;   // private field
    // funcs pointers
    void (*add)(struct SetInt* set, int number);
    void (*addAll)(struct SetInt* set1, struct SetInt* set2);
    void (*clear)(struct SetInt* set);
    bool (*contains)(struct SetInt* set, int number);
    bool (*containsAll)(struct SetInt* set1, struct SetInt* set2);
    bool (*containsAny)(struct SetInt* set1, struct SetInt* set2);
    bool (*removeElem)(struct SetInt* set, int number);
    bool (*removeAll)(struct SetInt* set1, struct SetInt* set2);
    bool (*isEmpty)(struct SetInt* set);
    bool (*isEquals)(struct SetInt* set1, struct SetInt* set2);
    struct SetInt* (*emptyIfNull)(struct SetInt* set);
    int (*size)(struct SetInt* set);
    struct Itr* (*iterator)(struct SetInt* set);
    //void (*printset)(struct LinkedsetInt* set);
    //void (*deleteset)(struct LinkedsetInt* set);
} SetInt;

typedef struct SetDouble {
    struct InnerDoubleSet* inner;   // private field
    // funcs pointers
    void (*add)(struct SetDouble* set, double number);
    void (*addAll)(struct SetDouble* set1, struct SetDouble* set2);
    void (*clear)(struct SetDouble* set);
    bool (*contains)(struct SetDouble* set, double number);
    bool (*containsAll)(struct SetDouble* set1, struct SetDouble* set2);
    bool (*containsAny)(struct SetDouble* set1, struct SetDouble* set2);
    bool (*removeElem)(struct SetDouble* set, double number);
    bool (*removeAll)(struct SetDouble* set1, struct SetDouble* set2);
    bool (*isEmpty)(struct SetDouble* set);
    bool (*isEquals)(struct SetDouble* set1, struct SetDouble* set2);
    struct SetDouble* (*emptyIfNull)(struct SetDouble* set);
    int (*size)(struct SetDouble* set);
    struct Itr* (*iterator)(struct SetDouble* set);
    //void (*printset)(struct LinkedsetInt* set);
    //void (*deleteset)(struct LinkedsetInt* set);
} SetDouble;

typedef struct SetStr {
    struct InnerStrSet* inner;   // private field
    // funcs pointers
    void (*add)(struct SetStr* set, string s);
    void (*addAll)(struct SetStr* set1, struct SetStr* set2);
    void (*clear)(struct SetStr* set);
    bool (*contains)(struct SetStr* set, string s);
    bool (*containsAll)(struct SetStr* set1, struct SetStr* set2);
    bool (*containsAny)(struct SetStr* set1, struct SetStr* set2);
    bool (*removeElem)(struct SetStr* set, string s);
    bool (*removeAll)(struct SetStr* set1, struct SetStr* set2);
    bool (*isEmpty)(struct SetStr* set);
    bool (*isEquals)(struct SetStr* set1, struct SetStr* set2);
    struct SetStr* (*emptyIfNull)(struct SetStr* set);
    int (*size)(struct SetStr* set);
    struct Itr* (*iterator)(struct SetStr* set);
    //void (*printset)(struct LinkedsetInt* set);
    //void (*deleteset)(struct LinkedsetInt* set);
} SetStr;

typedef SetInt* IntSet;
typedef SetDouble* DoubleSet;
typedef SetStr* StrSet;
typedef String* string;


IntSet newIntSet(IntSet);
DoubleSet newDoubleSet(DoubleSet);

#endif
