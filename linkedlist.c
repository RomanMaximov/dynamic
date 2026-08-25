//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "linkedlist.h"
#include "linkedlistservice/intlinkedlist.h"
#include "linkedlistservice/doublelinkedlist.h"
#include "linkedlistservice/strlinkedlist.h"
#include "context.h"

// structures
typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

// LinkedList data encapsulation
typedef struct InnerIntLL {
    int count;
    struct NodeInt* nodes;
    struct NodeInt* begin;
    struct NodeInt* end;
} InnerIntLL;

typedef struct NodeDouble {
    double data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;

// LinkedList data encapsulation
typedef struct InnerDoubleLL {
    int count;
    struct NodeDouble* nodes;
    struct NodeDouble* begin;
    struct NodeDouble* end;
} InnerDoubleLL;

typedef struct NodeStr {
    string data;
    struct NodeStr* next;
    struct NodeStr* prev;
} NodeStr;

// LinkedList data encapsulation
typedef struct InnerStrLL {
    int count;
    struct NodeStr* nodes;
    struct NodeStr* begin;
    struct NodeStr* end;
} InnerStrLL;


typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;
typedef LinkedListDouble* DoubleLinkedList;
typedef NodeDouble* DoubleNode;
typedef LinkedListStr* StrLinkedList;
typedef NodeStr* StrNode;
typedef Itr* Iterator;


// prototypes common funcs
static void initFuncs(Type type, void* data);

// funcs
IntLinkedList pr_initLLi_(IntLinkedList temp, void* collection) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->pf = malloc(sizeof(InnerIntLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    if (collection == NULL) return list;
    addAllIntLL(list, collection);

    return list;
}

IntLinkedList pr_initLLi_lo_(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->pf = malloc(sizeof(InnerIntLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

IntLinkedList pr_initLLi_loa_(IntLinkedList temp, int* arr, int size) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->pf = malloc(sizeof(InnerIntLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addIntLL(list, arr[i]);
    }

    return list;
}

DoubleLinkedList pr_initLLd_(DoubleLinkedList temp, void* collection) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->pf = malloc(sizeof(InnerDoubleLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    if (collection == NULL) return list;
    addAllDoubleLL(list, collection);

    return list;
}

DoubleLinkedList pr_initLLd_lo_(DoubleLinkedList temp, int paramCount, ...) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->pf = malloc(sizeof(InnerDoubleLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addDoubleLL(list, va_arg(param, double));
    }
    va_end(param);
    return list;
}

DoubleLinkedList pr_initLLd_loa_(DoubleLinkedList temp, double* arr, int size) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->pf = malloc(sizeof(InnerDoubleLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addDoubleLL(list, arr[i]);
    }

    return list;
}

StrLinkedList pr_initLLs_(StrLinkedList temp, void* collection) {
    StrLinkedList list = malloc(sizeof(LinkedListStr));
    list->pf = malloc(sizeof(InnerStrLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    return list;
}

StrLinkedList pr_initLLs_lo_(StrLinkedList temp, int paramCount, ...) {
    StrLinkedList list = malloc(sizeof(LinkedListStr));
    list->pf = malloc(sizeof(InnerStrLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addArrCharLL(list, va_arg(param, char*));
    }
    va_end(param);
    return list;
}

StrLinkedList pr_initLLs_loa_(StrLinkedList temp, char* arr[], int size) {
    StrLinkedList list = malloc(sizeof(LinkedListStr));
    list->pf = malloc(sizeof(InnerStrLL));
    list->pf->count = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addArrCharLL(list, arr[i]);
    }
    return list;
}

 static void initFuncs(Type type, void* data) {
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->add = addIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->add = addDoubleLL : (((StrLinkedList) data)->add = addStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->addAll = addAllIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->addAll = addAllDoubleLL : (((StrLinkedList) data)->addAll = addAllStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->get = getIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->get = getDoubleLL : (((StrLinkedList) data)->get = getStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->set = setIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->set = setDoubleLL : (((StrLinkedList) data)->set = setStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->indexOf = indexOfIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->indexOf = indexOfDoubleLL : (((StrLinkedList) data)->indexOf = indexOfStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->sort = sortIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->sort = sortDoubleLL : (((StrLinkedList) data)->sort = sortStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->sortReverse = sortIntLLReverse : type == DOUBLE_LL ? ((DoubleLinkedList) data)->sortReverse = sortDoubleLLReverse : (((StrLinkedList) data)->sortReverse = sortStrLLReverse);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->clear = clearIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->clear = clearDoubleLL : (((StrLinkedList) data)->clear = clearStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->contains = containsIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->contains = containsDoubleLL : (((StrLinkedList) data)->contains = containsStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->containsAll = containsAllIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->containsAll = containsAllDoubleLL : (((StrLinkedList) data)->containsAll = containsAllStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->containsAny = containsAnyIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->containsAny = containsAnyDoubleLL : (((StrLinkedList) data)->containsAny = containsAnyStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->removeElem = removeIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->removeElem = removeDoubleLL : (((StrLinkedList) data)->removeElem = removeStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->removeAll = removeAllIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->removeAll = removeAllDoubleLL : (((StrLinkedList) data)->removeAll = removeAllStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->subtract = subtractIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->subtract = subtractDoubleLL : (((StrLinkedList) data)->subtract = subtractStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->isEmpty = isEmptyIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->isEmpty = isEmptyDoubleLL : (((StrLinkedList) data)->isEmpty = isEmptyStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->reverse = reverseIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->reverse = reverseDoubleLL : (((StrLinkedList) data)->reverse = reverseStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->isEquals = isEqualListsIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->isEquals = isEqualListsDoubleLL : (((StrLinkedList) data)->isEquals = isEqualListsStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->size = sizeIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->size = sizeDoubleLL : (((StrLinkedList) data)->size = sizeStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->toString = toStrIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->toString = toStrDoubleLL : (((StrLinkedList) data)->toString = toStrStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->print = printIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->print = printDoubleLL : (((StrLinkedList) data)->print = printStrLL);
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->delete = deleteIntLL : type == DOUBLE_LL ? ((DoubleLinkedList) data)->delete = deleteDoubleLL : (((StrLinkedList) data)->delete = deleteStrLL);
}

