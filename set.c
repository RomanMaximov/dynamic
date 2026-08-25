//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include "set.h"
#include "setservice/intset.h"
#include "setservice/doubleset.h"
#include "setservice/strset.h"
#include "collectiontypes.h"


// structures
typedef struct Collection {
    void* data;
    Type type;
} Collection;

typedef struct NodeSetInt {
    int data;
    struct NodeSetInt* left;
    struct NodeSetInt* right;
} NodeSetInt;

// Set data encapsulation
typedef struct InnerIntSet {
    int count;
    int capacity;
    int capacityCounter;
    struct NodeInt** bucket;
} InnerIntSet;

typedef struct NodeSetDouble {
    double data;
    struct NodeSetDouble* left;
    struct NodeSetDouble* right;
} NodeSetDouble;

// Set data encapsulation
typedef struct InnerDoubleSet {
    int count;
    int capacity;
    int capacityCounter;
    struct NodeInt** bucket;
} InnerDoubleSet;

typedef struct NodeSetStr {
    string data;
    struct NodeSetStr* left;
    struct NodeSetStr* right;
} NodeSetStr;

// Set data encapsulation
typedef struct InnerStrSet {
    int count;
    int capacity;
    int capacityCounter;
    struct NodeStr** bucket;
} InnerStrSet;

typedef SetInt* IntSet;
typedef NodeSetInt* IntSetNode;
typedef SetDouble* DoubleSet;
typedef NodeSetDouble* DoubleSetNode;
typedef SetStr* StrSet;
typedef NodeSetStr* StrSetNode;
typedef String* string;

// prototypes common funcs
static void initFuncs(Type type, void* data);

// funcs
IntSet pr_initSi_(IntSet temp, void* collection) {
    IntSet set = malloc(sizeof(SetInt));
    set->pf = malloc(sizeof(InnerIntSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetInt*));

    initFuncs(INT_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    if (collection == NULL) return set;
    addAllIntSet(set, collection);

    return set;
}

IntSet pr_initSi_so_(IntSet temp, int paramCount, ...) {
    IntSet set = malloc(sizeof(SetInt));
    set->pf = malloc(sizeof(InnerIntSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetInt*));

    initFuncs(INT_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntSet(set, va_arg(param, int));
    }
    va_end(param);

    return set;
}

IntSet pr_initSi_soa_(IntSet temp, int* arr, int size) {
    IntSet set = malloc(sizeof(SetInt));
    set->pf = malloc(sizeof(InnerIntSet));
    set->pf->count = 0;
    set->pf->capacity = 64 + size;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetInt*));

    initFuncs(INT_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = INT_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addIntSet(set, arr[i]);
    }

    return set;
}

DoubleSet pr_initSd_(DoubleSet temp, void* collection) {
    DoubleSet set = malloc(sizeof(SetDouble));
    set->pf = malloc(sizeof(InnerDoubleSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));

    initFuncs(DOUBLE_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    if (collection == NULL) return set;
    addAllDoubleSet(set, collection);

    return set;
}

DoubleSet pr_initSd_so_(DoubleSet temp, int paramCount, ...) {
    DoubleSet set = malloc(sizeof(SetDouble));
    set->pf = malloc(sizeof(InnerDoubleSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));

    initFuncs(DOUBLE_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addDoubleSet(set, va_arg(param, double ));
    }
    va_end(param);

    return set;
}

DoubleSet pr_initSd_soa_(DoubleSet temp, double* arr, int size) {
    DoubleSet set = malloc(sizeof(SetDouble));
    set->pf = malloc(sizeof(InnerDoubleSet));
    set->pf->count = 0;
    set->pf->capacity = 64 + size;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetDouble*));

    initFuncs(DOUBLE_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addDoubleSet(set, arr[i]);
    }

    return set;
}

StrSet pr_initSs_(StrSet temp, void* collection) {
    StrSet set = malloc(sizeof(SetStr));
    set->pf = malloc(sizeof(InnerStrSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));

    initFuncs(STR_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    if (collection == NULL) return set;
    addAllStrSet(set, collection);

    return set;
}

StrSet pr_initSs_so_(StrSet temp, int paramCount, ...) {
    StrSet set = malloc(sizeof(SetStr));
    set->pf = malloc(sizeof(InnerStrSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));

    initFuncs(STR_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addCharArrSet(set, va_arg(param, char*));
    }
    va_end(param);

    return set;
}

StrSet pr_initSs_soa_(StrSet temp, char* arr[], int size) {
    StrSet set = malloc(sizeof(SetStr));
    set->pf = malloc(sizeof(InnerStrSet));
    set->pf->count = 0;
    set->pf->capacity = 64 + size;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetStr*));

    initFuncs(STR_SET, set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addCharArrSet(set, arr[i]);
    }

    return set;
}

static void initFuncs(Type type, void* data) {
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->add = addIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->add = addDoubleSet : (((StrSet) data)->addStr = addStrSet);
    if (type == STR_SET)
        ((StrSet) data)->addLiteral = addCharArrSet;
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->addAll = addAllIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->addAll = addAllDoubleSet : (((StrSet) data)->addAll = addAllStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->clear = clearIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->clear = clearDoubleSet : (((StrSet) data)->clear = clearStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->contains = containsIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->contains = containsDoubleSet : (((StrSet) data)->contains = containsStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAll = containsAllIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->containsAll = containsAllDoubleSet : (((StrSet) data)->containsAll = containsAllStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAny = containsAnyIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->containsAny = containsAnyDoubleSet : (((StrSet) data)->containsAny = containsAnyStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeElem = removeIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->removeElem = removeDoubleSet : (((StrSet) data)->removeElem = removeStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeAll = removeAllIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->removeAll = removeAllDoubleSet : (((StrSet) data)->removeAll = removeAllStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->subtract = subtractIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->subtract = subtractDoubleSet : (((StrSet) data)->subtract = subtractStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->isEmpty = isEmptyIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->isEmpty = isEmptyDoubleSet : (((StrSet) data)->isEmpty = isEmptyStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->size = sizeIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->size = sizeDoubleSet : (((StrSet) data)->size = sizeDoubleSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->toString = toStrIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->toString = toStrDoubleSet : (((StrSet) data)->toString = toStrStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->print = printIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->print = printDoubleSet : (((StrSet) data)->print = printStrSet);
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->delete = deleteIntSet : type == DOUBLE_SET ? ((DoubleSet) data)->delete = deleteDoubleSet : (((StrSet) data)->delete = deleteStrSet);
}