//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "arraylist.h"
#include "arrayservice/intarraylist.h"
#include "arrayservice/doublearraylist.h"
#include "arrayservice/strarraylist.h"
#include "context.h"

// ArrayList data encapsulation
typedef struct InnerIntList {
    int count;
    int* data;
    int capacity;
} InnerIntList;

// ArrayList data encapsulation
typedef struct InnerDoubleList {
    int count;
    double* data;
    int capacity;
} InnerDoubleList;

// ArrayList data encapsulation
typedef struct InnerStrList {
    int count;
    struct String** data;
    int capacity;
} InnerStrList;


typedef ArrayListInt* IntList;
typedef ArrayListDouble* DoubleList;
typedef ArrayListStr* StrList;
typedef String* string;
typedef Itr* Iterator;


// prototypes common funcs
static void initFuncs(Type type, void* data);


// funcs
IntList pr_initLi_(IntList temp, void* collection) {
    IntList list = malloc(sizeof(ArrayListInt));
    list->pf = malloc(sizeof(InnerIntList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(int));
    initFuncs(INT_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    if (collection == NULL) return list;
    addAllIntList(list, collection);

    return list;
}

IntList pr_initLi_lo_(IntList temp, int paramCount, ...) {
    IntList list = malloc(sizeof(ArrayListInt));
    list->pf = malloc(sizeof(InnerIntList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(int));
    initFuncs(INT_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntList(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

IntList pr_initLi_loa_(IntList temp, int* arr, int size) {
    IntList list = malloc(sizeof(ArrayListInt));
    list->pf = malloc(sizeof(InnerIntList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(int));
    initFuncs(INT_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addIntList(list, arr[i]);
    }

    return list;
}

DoubleList pr_initLd_(DoubleList temp, void* collection) {
    DoubleList list = malloc(sizeof(ArrayListDouble));
    list->pf = malloc(sizeof(InnerDoubleList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(double));
    initFuncs(DOUBLE_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    if (collection == NULL) return list;
    addAllDoubleList(list, collection);

    return list;
}

DoubleList pr_initLd_lo_(DoubleList temp, int paramCount, ...) {
    DoubleList list = malloc(sizeof(ArrayListDouble));
    list->pf = malloc(sizeof(InnerDoubleList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(double));
    initFuncs(DOUBLE_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addDoubleList(list, va_arg(param, double));
    }
    va_end(param);
    return list;
}

DoubleList pr_initLd_loa_(DoubleList temp, double* arr, int size) {
    DoubleList list = malloc(sizeof(ArrayListDouble));
    list->pf = malloc(sizeof(InnerDoubleList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(double));
    initFuncs(DOUBLE_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;


    for (int i = 0; i < size; ++i) {
        addDoubleList(list, arr[i]);
    }
    return list;
}

StrList pr_initLs_(StrList temp, void* collection) {
    StrList list = malloc(sizeof(ArrayListStr));
    list->pf = malloc(sizeof(InnerStrList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->data[i] = NULL;

    initFuncs(STR_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    if (collection == NULL) return list;
    addAllStrList(list, collection);

    return list;
}

StrList pr_initLs_lo_(StrList temp, int paramCount, ...) {
    StrList list = malloc(sizeof(ArrayListStr));
    list->pf = malloc(sizeof(InnerStrList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->data[i] = NULL;

    initFuncs(STR_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addCharArrList(list, va_arg(param, char*));
    }
    va_end(param);
    return list;
}

StrList pr_initLs_loa_(StrList temp, char* arr[], int size) {
    StrList list = malloc(sizeof(ArrayListStr));
    list->pf = malloc(sizeof(InnerStrList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->data[i] = NULL;

    initFuncs(STR_LIST, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LIST;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addCharArrList(list, arr[i]);
    }

    return list;
}

static void initFuncs(Type type, void* data) {
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->add = addIntList : type == DOUBLE_LIST ? ((DoubleList) data)->add = addDoubleList : (((StrList) data)->add = addStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->addAll = addAllIntList : type == DOUBLE_LIST ? ((DoubleList) data)->addAll = addAllDoubleList : (((StrList) data)->addAll = addAllStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->get = getIntList : type == DOUBLE_LIST ? ((DoubleList) data)->get = getDoubleList : (((StrList) data)->get = getStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->set = setIntList : type == DOUBLE_LIST ? ((DoubleList) data)->set = setDoubleList : (((StrList) data)->set = setStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->indexOf = indexOfIntList : type == DOUBLE_LIST ? ((DoubleList) data)->indexOf = indexOfDoubleList : (((StrList) data)->indexOf = indexOfStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->sort = sortIntList : type == DOUBLE_LIST ? ((DoubleList) data)->sort = sortDoubleList : (((StrList) data)->sort = sortStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->sortReverse = sortIntListReverse : type == DOUBLE_LIST ? ((DoubleList) data)->sortReverse = sortDoubleListReverse : (((StrList) data)->sortReverse = sortStrListReverse);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->clear = clearIntList : type == DOUBLE_LIST ? ((DoubleList) data)->clear = clearDoubleList : (((StrList) data)->clear = clearStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->contains = containsIntList : type == DOUBLE_LIST ? ((DoubleList) data)->contains = containsDoubleList : (((StrList) data)->contains = containsStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->containsAll = containsAllIntList : type == DOUBLE_LIST ? ((DoubleList) data)->containsAll = containsAllDoubleList : (((StrList) data)->containsAll = containsAllStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->containsAny = containsAnyIntList : type == DOUBLE_LIST ? ((DoubleList) data)->containsAny = containsAnyDoubleList : (((StrList) data)->containsAny = containsAnyStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->removeElem = removeIntList : type == DOUBLE_LIST ? ((DoubleList) data)->removeElem = removeDoubleList : (((StrList) data)->removeElem = removeStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->removeAll = removeAllIntList : type == DOUBLE_LIST ? ((DoubleList) data)->removeAll = removeAllDoubleList : (((StrList) data)->removeAll = removeAllStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->subtract = subtractIntList : type == DOUBLE_LIST ? ((DoubleList) data)->subtract = subtractDoubleList : (((StrList) data)->subtract = subtractStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->isEmpty = isEmptyIntList : type == DOUBLE_LIST ? ((DoubleList) data)->isEmpty = isEmptyDoubleList : (((StrList) data)->isEmpty = isEmptyStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->reverse = reverseIntList : type == DOUBLE_LIST ? ((DoubleList) data)->reverse = reverseDoubleList : (((StrList) data)->reverse = reverseStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->isEquals = isEqualsIntList : type == DOUBLE_LIST ? ((DoubleList) data)->isEquals = isEqualsDoubleList : (((StrList) data)->isEquals = isEqualsStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->size = sizeIntList : type == DOUBLE_LIST ? ((DoubleList) data)->size = sizeDoubleList : (((StrList) data)->size = sizeStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->toString = toStrIntList : type == DOUBLE_LIST ? ((DoubleList) data)->toString = toStrDoubleList : (((StrList) data)->toString= toStrStrList);
    if (type == STR_LIST) ((StrList) data)->joinList = joinStrList;
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->print = printIntList : type == DOUBLE_LIST ? ((DoubleList) data)->print = printDoubleList : (((StrList) data)->print = printStrList);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->delete = deleteIntList : type == DOUBLE_LIST ? ((DoubleList) data)->delete = deleteDoubleList : (((StrList) data)->delete = deleteStrList);
}