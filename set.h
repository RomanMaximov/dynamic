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
#include "iterator.h"

// structures
typedef struct String String;
typedef struct Collection Collection;

typedef struct SetInt {
    struct InnerIntSet* pf;   // private field
    void* values;             // private field
    // funcs pointers
    void (*add)(struct SetInt* set, int number);
    void (*addAll)(struct SetInt* set1, struct SetInt* set2);
    void (*clear)(struct SetInt* set);
    bool (*contains)(struct SetInt* set, int number);
    bool (*containsAll)(struct SetInt* set1, struct SetInt* set2);
    bool (*containsAny)(struct SetInt* set1, struct SetInt* set2);
    bool (*removeElem)(struct SetInt* set, int number);
    bool (*removeAll)(struct SetInt* set1, struct SetInt* set2);
    struct SetInt* (*subtract)(struct SetInt* set1, void* source);
    bool (*isEmpty)(struct SetInt* set);
    int (*size)(struct SetInt* set);
    string (*toString)(struct SetInt* set);
    void (*print)(struct SetInt* set);
    void (*delete)(struct SetInt**set);
} SetInt;

typedef struct SetDouble {
    struct InnerDoubleSet* pf;   // private field
    void* values;                // private field
    // funcs pointers
    void (*add)(struct SetDouble* set, double number);
    void (*addAll)(struct SetDouble* set1, struct SetDouble* set2);
    void (*clear)(struct SetDouble* set);
    bool (*contains)(struct SetDouble* set, double number);
    bool (*containsAll)(struct SetDouble* set1, struct SetDouble* set2);
    bool (*containsAny)(struct SetDouble* set1, struct SetDouble* set2);
    bool (*removeElem)(struct SetDouble* set, double number);
    bool (*removeAll)(struct SetDouble* set1, struct SetDouble* set2);
    struct SetDouble* (*subtract)(struct SetDouble* set1, void* source);
    bool (*isEmpty)(struct SetDouble* set);
    int (*size)(struct SetDouble* set);
    string (*toString)(struct SetDouble* set);
    void (*print)(struct SetDouble* set);
    void (*delete)(struct SetDouble** set);
} SetDouble;

typedef struct SetStr {
    struct InnerStrSet* pf;   // private field
    void* values;             // private field
    // funcs pointers
    void (*add)(struct SetStr* set, string s);
    void (*addAll)(struct SetStr* set1, struct SetStr* set2);
    void (*clear)(struct SetStr* set);
    bool (*contains)(struct SetStr* set, string s);
    bool (*containsAll)(struct SetStr* set1, struct SetStr* set2);
    bool (*containsAny)(struct SetStr* set1, struct SetStr* set2);
    bool (*removeElem)(struct SetStr* set, string s);
    bool (*removeAll)(struct SetStr* set1, struct SetStr* set2);
    struct SetStr* (*subtract)(struct SetStr* set1, void* source);
    bool (*isEmpty)(struct SetStr* set);
    int (*size)(struct SetStr* set);
    string (*toString)(struct SetStr* set);
    void (*print)(struct SetStr* set);
    void (*delete)(struct SetStr** set);
} SetStr;

typedef SetInt* IntSet;
typedef SetDouble* DoubleSet;
typedef SetStr* StrSet;
typedef String* string;

// func prototypes
IntSet pr_initSi_(IntSet, void*);
DoubleSet pr_initSd_(DoubleSet, void*);
StrSet pr_initSs_(StrSet, void*);

IntSet pr_initSi_so_(IntSet, int, ...);
DoubleSet pr_initSd_so_(DoubleSet, int, ...);
StrSet pr_initSs_so_(StrSet, int, ...);

IntSet pr_initSi_soa_(IntSet, int*, int);
DoubleSet pr_initSd_soa_(DoubleSet, double*, int);
StrSet pr_initSs_soa_(StrSet, char* [], int);

#endif
