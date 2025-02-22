//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include "string.h"
#include "collectiontypes.h"
#include "iterator.h"


// structures
typedef struct String String;

typedef struct LinkedListInt {
    struct InnerIntLL* pf;   // private field
    void* values;            // private field
    // funcs pointers
    void (*add)(struct LinkedListInt* list, int number);
    void (*addAll)(struct LinkedListInt* list1, void* list2);
    int (*get)(struct LinkedListInt* list, int index);
    bool (*set)(struct LinkedListInt* list, int index, int number);
    int (*indexOf)(struct LinkedListInt* list, int number);
    void (*sort)(struct LinkedListInt* list);
    void (*sortReverse)(struct LinkedListInt* list);
    void (*clear)(struct LinkedListInt* list);
    bool (*contains)(struct LinkedListInt* list, int number);
    bool (*containsAll)(struct LinkedListInt* list1, void* list2);
    bool (*containsAny)(struct LinkedListInt* list1, void* list2);
    bool (*removeElem)(struct LinkedListInt* list, int number);
    bool (*removeAll)(struct LinkedListInt* list1, void* list2);
    struct LinkedListInt* (*subtract)(struct LinkedListInt* list1, struct LinkedListInt* list2);
    bool (*isEmpty)(struct LinkedListInt* list);
    void (*reverse)(struct LinkedListInt* list);
    bool (*isEquals)(struct LinkedListInt* list1, struct LinkedListInt* list2);
    int (*size)(struct LinkedListInt* list);
    void (*toString)(struct LinkedListInt* list);
    void (*print)(struct LinkedListInt* list);
    void (*delete)(struct LinkedListInt** list);
} LinkedListInt;

typedef struct LinkedListDouble {
    struct InnerDoubleLL* pf;   // private field
    void* values;               // private field
    // funcs pointers
    void (*add)(struct LinkedListDouble* list, double number);
    void (*addAll)(struct LinkedListDouble* list1, void* list2);
    double (*get)(struct LinkedListDouble* list, int index);
    bool (*set)(struct LinkedListDouble* list, int index, double number);
    int (*indexOf)(struct LinkedListDouble* list, double number);
    void (*sort)(struct LinkedListDouble* list);
    void (*sortReverse)(struct LinkedListDouble* list);
    void (*clear)(struct LinkedListDouble* list);
    bool (*contains)(struct LinkedListDouble* list, double number);
    bool (*containsAll)(struct LinkedListDouble* list1, void* list2);
    bool (*containsAny)(struct LinkedListDouble* list1, void* list2);
    bool (*removeElem)(struct LinkedListDouble* list, double number);
    bool (*removeAll)(struct LinkedListDouble* list1, void* list2);
    struct LinkedListDouble* (*subtract)(struct LinkedListDouble* list1, struct LinkedListDouble* list2);
    bool (*isEmpty)(struct LinkedListDouble* list);
    void (*reverse)(struct LinkedListDouble* list);
    bool (*isEquals)(struct LinkedListDouble* list1, struct LinkedListDouble* list2);
    int (*size)(struct LinkedListDouble* list);
    void (*toString)(struct LinkedListDouble* list);
    void (*print)(struct LinkedListDouble* list);
    void (*delete)(struct LinkedListDouble** list);
} LinkedListDouble;

typedef struct LinkedListStr {
    struct InnerStrLL* pf;   // private field
    void* values;            // private field
    // funcs pointers
    void (*add)(struct LinkedListStr* list, string s);
    void (*addAll)(struct LinkedListStr* list1, void* list2);
    String* (*get)(struct LinkedListStr* list, int index);
    bool (*set)(struct LinkedListStr* list, int index, String* s);
    int (*indexOf)(struct LinkedListStr* list, String* s);
    void (*sort)(struct LinkedListStr* list);
    void (*sortReverse)(struct LinkedListStr* list);
    void (*clear)(struct LinkedListStr* list);
    bool (*contains)(struct LinkedListStr* list, String* s);
    bool (*containsAll)(struct LinkedListStr* list1, void* list2);
    bool (*containsAny)(struct LinkedListStr* list1, void* list2);
    bool (*removeElem)(struct LinkedListStr* list, String* s);
    bool (*removeAll)(struct LinkedListStr* list1, void* list2);
    struct LinkedListStr* (*subtract)(struct LinkedListStr* list1, struct LinkedListStr* list2);
    bool (*isEmpty)(struct LinkedListStr* list);
    void (*reverse)(struct LinkedListStr* list);
    bool (*isEquals)(struct LinkedListStr* list1, struct LinkedListStr* list2);
    int (*size)(struct LinkedListStr* list);
    void (*toString)(struct LinkedListStr* list);
    void (*print)(struct LinkedListStr* list);
    void (*delete)(struct LinkedListStr** list);
} LinkedListStr;

typedef LinkedListInt* IntLinkedList;
typedef LinkedListDouble* DoubleLinkedList;
typedef LinkedListStr* StrLinkedList;
typedef String* string;



// func prototypes
IntLinkedList pr_initLLi_(IntLinkedList, void*);
DoubleLinkedList pr_initLLd_(DoubleLinkedList, void*);
StrLinkedList pr_initLLs_(StrLinkedList, void*);

IntLinkedList pr_initLLi_lo_(IntLinkedList, int, ...);
DoubleLinkedList pr_initLLd_lo_(DoubleLinkedList, int, ...);
StrLinkedList pr_initLLs_lo_(StrLinkedList, int, ...);

IntLinkedList pr_initLLi_loa_(IntLinkedList, int*, int);
DoubleLinkedList pr_initLLd_loa_(DoubleLinkedList, double*, int);
StrLinkedList pr_initLLs_loa_(StrLinkedList, char* [], int);

#endif
