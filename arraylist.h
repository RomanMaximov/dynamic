//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include "string.h"
#include "arrayservice/intarraylist.h"
#include "arrayservice/doublearraylist.h"
#include "arrayservice/strarraylist.h"
#include "collectiontypes.h"
#include "iterator.h"


// structures
typedef struct String String;

typedef struct ArrayListInt {
    struct InnerIntList* inner;   // private field
    // funcs pointers
    void (*add)(struct ArrayListInt* list, int number);
    void (*addAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    int (*get)(struct ArrayListInt* list, int index);
    bool (*set)(struct ArrayListInt* list, int index, int number);
    int (*indexOf)(struct ArrayListInt* list, int number);
    void (*sort)(struct ArrayListInt* list);
    void (*sortReverse)(struct ArrayListInt* list);
    void (*clear)(struct ArrayListInt* list);
    bool (*contains)(struct ArrayListInt* list, int number);
    bool (*containsAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*containsAny)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*removeElem)(struct ArrayListInt* list, int number);
    bool (*removeAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    struct ArrayListInt* (*subtract)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*isEmpty)(struct ArrayListInt* list);
    void (*reverse)(struct ArrayListInt* list);
    bool (*isEquals)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    struct ArrayListInt* (*emptyIfNull)(struct ArrayListInt* list);
    int (*size)(struct ArrayListInt* list);
    struct Itr* (*iterator)(struct ArrayListInt* list);
    //void (*printList)(struct ArrayListInt* list);
    //void (*deleteList)(struct ArrayListInt* list);
} ArrayListInt;

typedef struct ArrayListDouble {
    struct InnerDoubleList* inner;   // private field
    // funcs pointers
    void (*add)(struct ArrayListDouble* list, double number);
    void (*addAll)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    double (*get)(struct ArrayListDouble* list, int index);
    bool (*set)(struct ArrayListDouble* list, int index, double number);
    int (*indexOf)(struct ArrayListDouble* list, double number);
    void (*sort)(struct ArrayListDouble* list);
    void (*sortReverse)(struct ArrayListDouble* list);
    void (*clear)(struct ArrayListDouble* list);
    bool (*contains)(struct ArrayListDouble* list, double number);
    bool (*containsAll)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    bool (*containsAny)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    bool (*removeElem)(struct ArrayListDouble* list, int number);
    bool (*removeAll)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    struct ArrayListDouble* (*subtract)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    bool (*isEmpty)(struct ArrayListDouble* list);
    void (*reverse)(struct ArrayListDouble* list);
    bool (*isEquals)(struct ArrayListDouble* list1, struct ArrayListDouble* list2);
    struct ArrayListDouble* (*emptyIfNull)(struct ArrayListDouble* list);
    int (*size)(struct ArrayListDouble* list);
    struct Itr* (*iterator)(struct ArrayListDouble* list);
    //void (*printList)(struct ArrayListInt* list);
    //void (*deleteList)(struct ArrayListInt* list);
} ArrayListDouble;

typedef struct ArrayListStr {
    struct InnerStrList* inner;   // private field
    // funcs pointers
    void (*add)(struct ArrayListStr* list, string s);
    void (*addAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    int (*get)(struct ArrayListInt* list, int index);
    bool (*set)(struct ArrayListInt* list, int index, int number);
    int (*indexOf)(struct ArrayListInt* list, int number);
    void (*sort)(struct ArrayListInt* list);
    void (*sortReverse)(struct ArrayListInt* list);
    void (*clear)(struct ArrayListInt* list);
    bool (*contains)(struct ArrayListInt* list, int number);
    bool (*containsAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*containsAny)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*removeElem)(struct ArrayListInt* list, int number);
    bool (*removeAll)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    struct ArrayListInt* (*subtract)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    bool (*isEmpty)(struct ArrayListInt* list);
    void (*reverse)(struct ArrayListInt* list);
    bool (*isEquals)(struct ArrayListInt* list1, struct ArrayListInt* list2);
    struct ArrayListInt* (*emptyIfNull)(struct ArrayListInt* list);
    int (*size)(struct ArrayListInt* list);
    struct Itr* (*iterator)(struct ArrayListInt* list);
    //void (*printList)(struct ArrayListInt* list);
    //void (*deleteList)(struct ArrayListInt* list);
} ArrayListStr;


typedef ArrayListInt* IntList;
typedef ArrayListDouble* DoubleList;
typedef ArrayListStr* StrList;
typedef String* string;
typedef Itr* Iterator;

// func prototypes
IntList newIntList(IntList);
DoubleList newDoubleList(DoubleList);
StrList newStrList(StrList);

IntList listOfInt(IntList, int, ...);
DoubleList listOfDouble(DoubleList, int, ...);
StrList listOfStr(StrList, int, ...);

#endif
