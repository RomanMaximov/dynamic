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
static void* add(Type type);
static void* addStr();
static void* addLiteral();
static void* addAll(Type type);
static void* clear(Type type);
static void* contains(Type type);
static void* containsAll(Type type);
static void* containsAny(Type type);
static void* removeElem(Type type);
static void* removeAll(Type type);
static void* isEmpty(Type type);

static void* size(Type type);
static void* toString(Type type);
static void* print(Type type);
static void* delete(Type type);

// funcs
IntSet pr_initSi_(IntSet temp, void* collection) {
    IntSet set = malloc(sizeof(SetInt));
    set->pf = malloc(sizeof(InnerIntSet));
    set->pf->count = 0;
    set->pf->capacity = 64;
    set->pf->capacityCounter = 0;
    set->pf->bucket = calloc(set->pf->capacity, sizeof(NodeSetInt*));

    initFuncs(INT_SET, (void*)set);

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

    initFuncs(INT_SET, (void*)set);

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

    initFuncs(INT_SET, (void*)set);

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

    initFuncs(DOUBLE_SET, (void*)set);

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

    initFuncs(DOUBLE_SET, (void*)set);

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

    initFuncs(DOUBLE_SET, (void*)set);

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

    initFuncs(STR_SET, (void*)set);

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

    initFuncs(STR_SET, (void*)set);

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

    initFuncs(STR_SET, (void*)set);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_SET;
    ctx->collection = (void*) set;

    set->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addCharArrSet(set, arr[i]);
    }

    return set;
}


// common init functions
static void* add(Type type) {
    switch (type) {
        case INT_SET:
            return addIntSet;
        case DOUBLE_SET:
            return addDoubleSet;
        default:
            return NULL;
    }
}

static void* addStr() {
    return addStrSet;
}

static void* addLiteral() {
    return addCharArrSet;
}

static void* addAll(Type type) {
    switch (type) {
        case INT_SET:
            return addAllIntSet;
        case DOUBLE_SET:
            return addAllDoubleSet;
        case STR_SET:
            return addAllStrSet;
        default:
            return NULL;
    }
}

static void* clear(Type type) {
    switch (type) {
        case INT_SET:
            return clearIntSet;
        case DOUBLE_SET:
            return clearDoubleSet;
        case STR_SET:
            return clearStrSet;
        default:
            return NULL;
    }
}

static void* contains(Type type) {
    switch (type) {
        case INT_SET:
            return containsIntSet;
        case DOUBLE_SET:
            return containsDoubleSet;
        case STR_SET:
            return containsStrSet;
        default:
            return NULL;
    }
}

static void* containsAll(Type type) {
    switch (type) {
        case INT_SET:
            return containsAllIntSet;
        case DOUBLE_SET:
            return containsAllDoubleSet;
        case STR_SET:
            return containsAllStrSet;
        default:
            return NULL;
    }
}

static void* containsAny(Type type) {
    switch (type) {
        case INT_SET:
            return containsAnyIntSet;
        case DOUBLE_SET:
            return containsAnyDoubleSet;
        case STR_SET:
            return containsAnyStrSet;
        default:
            return NULL;
    }
}

static void* removeElem(Type type) {
    switch (type) {
        case INT_SET:
            return removeIntSet;
        case DOUBLE_SET:
            return removeDoubleSet;
        case STR_SET:
            return removeStrSet;
        default:
            return NULL;
    }
}

static void* removeAll(Type type) {
    switch (type) {
        case INT_SET:
            return removeAllIntSet;
        case DOUBLE_SET:
            return removeAllDoubleSet;
        case STR_SET:
            return removeAllStrSet;
        default:
            return NULL;
    }
}

static void* subtract(Type type) {
    switch (type) {
        case INT_SET:
            return subtractIntSet;
        case DOUBLE_SET:
            return subtractDoubleSet;
        case STR_SET:
            return subtractStrSet;
        default:
            return NULL;
    }
}

static void* isEmpty(Type type) {
    switch (type) {
        case INT_SET:
            return isEmptyIntSet;
        case DOUBLE_SET:
            return isEmptyDoubleSet;
        case STR_SET:
            return isEmptyStrSet;
        default:
            return NULL;
    }
}

static void* size(Type type) {
    switch (type) {
        case INT_SET:
            return sizeIntSet;
        case DOUBLE_SET:
            return sizeDoubleSet;
        case STR_SET:
            return sizeStrSet;
        default:
            return NULL;
    }
}

static void* toString(Type type) {
    switch (type) {
        case INT_SET:
            return toStrIntSet;
        case DOUBLE_SET:
            return toStrDoubleSet;
        case STR_SET:
            return toStrStrSet;
        default:
            return NULL;
    }
}

static void* print(Type type) {
    switch (type) {
        case INT_SET:
            return printIntSet;
        case DOUBLE_SET:
            return printDoubleSet;
        case STR_SET:
            return printStrSet;
        default:
            return NULL;
    }
}

static void* delete(Type type) {
    switch (type) {
        case INT_SET:
            return deleteIntSet;
        case DOUBLE_SET:
            return deleteDoubleSet;
        case STR_SET:
            return deleteStrSet;
        default:
            return NULL;
    }
}

static void initFuncs(Type type, void* data) {
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->add = add(type) : type == DOUBLE_SET ? ((DoubleSet) data)->add = add(type) : (((StrSet) data)->addStr = addStr());
    if (type == STR_SET)
        ((StrSet) data)->addLiteral = addLiteral();
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->addAll = addAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->addAll = addAll(type) : (((StrSet) data)->addAll = addAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->clear = clear(type) : type == DOUBLE_SET ? ((DoubleSet) data)->clear = clear(type) : (((StrSet) data)->clear = clear(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->contains = contains(type) : type == DOUBLE_SET ? ((DoubleSet) data)->contains = contains(type) : (((StrSet) data)->contains = contains(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAll = containsAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->containsAll = containsAll(type) : (((StrSet) data)->containsAll = containsAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAny = containsAny(type) : type == DOUBLE_SET ? ((DoubleSet) data)->containsAny = containsAny(type) : (((StrSet) data)->containsAny = containsAny(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeElem = removeElem(type) : type == DOUBLE_SET ? ((DoubleSet) data)->removeElem = removeElem(type) : (((StrSet) data)->removeElem = removeElem(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeAll = removeAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->removeAll = removeAll(type) : (((StrSet) data)->removeAll = removeAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->subtract = subtract(type) : type == DOUBLE_SET ? ((DoubleSet) data)->subtract = subtract(type) : (((StrSet) data)->subtract = subtract(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->isEmpty = isEmpty(type) : type == DOUBLE_SET ? ((DoubleSet) data)->isEmpty = isEmpty(type) : (((StrSet) data)->isEmpty = isEmpty(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->size = size(type) : type == DOUBLE_SET ? ((DoubleSet) data)->size = size(type) : (((StrSet) data)->size = size(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->toString = toString(type) : type == DOUBLE_SET ? ((DoubleSet) data)->toString = toString(type) : (((StrSet) data)->toString = toString(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->print = print(type) : type == DOUBLE_SET ? ((DoubleSet) data)->print = print(type) : (((StrSet) data)->print = print(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->delete = delete(type) : type == DOUBLE_SET ? ((DoubleSet) data)->delete = delete(type) : (((StrSet) data)->delete = delete(type));
}