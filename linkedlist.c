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
    int index;
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
    int index;
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
    int index;
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
static void* add(Type type);
static void* addAll(Type type);
static void* get(Type type);
static void* set(Type type);
static void* indexOf(Type type);
static void* sort(Type type);
static void* sortReverse(Type type);
static void* clear(Type type);
static void* contains(Type type);
static void* containsAll(Type type);
static void* containsAny(Type type);
static void* removeElem(Type type);
static void* removeAll(Type type);
static void* subtract(Type type);
static void* isEmpty(Type type);
static void* reverse(Type type);
static void* isEquals(Type type);

static void* size(Type type);
static void* toString(Type type);
static void* print(Type type);
static void* delete(Type type);


// funcs
IntLinkedList pr_initLLi_(IntLinkedList temp, void* collection) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->pf = malloc(sizeof(InnerIntLL));
    list->pf->count = 0;
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(INT_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = DOUBLE_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addDoubleLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

DoubleLinkedList pr_initLLd_loa_(DoubleLinkedList temp, double* arr, int size) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->pf = malloc(sizeof(InnerDoubleLL));
    list->pf->count = 0;
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(DOUBLE_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, (void*)list);

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
    list->pf->index = 0;
    list->pf->nodes = NULL;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    initFuncs(STR_LL, (void*)list);

    Ctx ctx = malloc(sizeof(Context));
    ctx->type = STR_LL;
    ctx->collection = (void*) list;

    list->values = (void*) ctx;

    for (int i = 0; i < size; ++i) {
        addArrCharLL(list, arr[i]);
    }
    return list;
}

// common init functions
static void* add(Type type) {
    switch (type) {
        case INT_LL:
            return addIntLL;
        case DOUBLE_LL:
            return addDoubleLL;
        case STR_LL:
            return addStrLL;
        default:
            return NULL;
    }
}

static void* addAll(Type type) {
    switch (type) {
        case INT_LL:
            return addAllIntLL;
        case DOUBLE_LL:
            return addAllDoubleLL;
        case STR_LL:
            return addAllStrLL;
        default:
            return NULL;
    }
}

static void* get(Type type) {
    switch (type) {
        case INT_LL:
            return getIntLL;
        case DOUBLE_LL:
            return getDoubleLL;
        case STR_LL:
            return getStrLL;
        default:
            return NULL;
    }
}

static void* set(Type type) {
    switch (type) {
        case INT_LL:
            return setIntLL;
        case DOUBLE_LL:
            return setDoubleLL;
        case STR_LL:
            return setStrLL;
        default:
            return NULL;
    }
}

static void* indexOf(Type type) {
    switch (type) {
        case INT_LL:
            return indexOfIntLL;
        case DOUBLE_LL:
            return indexOfDoubleLL;
        case STR_LL:
            return indexOfStrLL;
        default:
            return NULL;
    }
}

static void* sort(Type type) {
    switch (type) {
        case INT_LL:
            return sortIntLL;
        case DOUBLE_LL:
            return sortDoubleLL;
        case STR_LL:
            return sortStrLL;
        default:
            return NULL;
    }
}

static void* sortReverse(Type type) {
    switch (type) {
        case INT_LL:
            return sortIntLLReverse;
        case DOUBLE_LL:
            return sortDoubleLLReverse;
        case STR_LL:
            return sortStrLLReverse;
        default:
            return NULL;
    }
}

static void* clear(Type type) {
    switch (type) {
        case INT_LL:
            return clearIntLL;
        case DOUBLE_LL:
            return clearDoubleLL;
        case STR_LL:
            return clearStrLL;
        default:
            return NULL;
    }
}

static void* contains(Type type) {
    switch (type) {
        case INT_LL:
            return containsIntLL;
        case DOUBLE_LL:
            return containsDoubleLL;
        case STR_LL:
            return containsStrLL;
        default:
            return NULL;
    }
}

static void* containsAll(Type type) {
    switch (type) {
        case INT_LL:
            return containsAllIntLL;
        case DOUBLE_LL:
            return containsAllDoubleLL;
        case STR_LL:
            return containsAllStrLL;
        default:
            return NULL;
    }
}

static void* containsAny(Type type) {
    switch (type) {
        case INT_LL:
            return containsAnyIntLL;
        case DOUBLE_LL:
            return containsAnyDoubleLL;
        case STR_LL:
            return containsAnyStrLL;
        default:
            return NULL;
    }
}

static void* removeElem(Type type) {
    switch (type) {
        case INT_LL:
            return removeIntLL;
        case DOUBLE_LL:
            return removeDoubleLL;
        case STR_LL:
            return removeStrLL;
        default:
            return NULL;
    }
}

static void* removeAll(Type type) {
    switch (type) {
        case INT_LL:
            return removeAllIntLL;
        case DOUBLE_LL:
            return removeAllDoubleLL;
        case STR_LL:
            return removeAllStrLL;
        default:
            return NULL;
    }
}

static void* subtract(Type type) {
    switch (type) {
        case INT_LL:
            return subtractIntLL;
        case DOUBLE_LL:
            return subtractDoubleLL;
        case STR_LL:
            return subtractStrLL;
        default:
            return NULL;
    }
}

static void* isEmpty(Type type) {
    switch (type) {
        case INT_LL:
            return isEmptyIntLL;
        case DOUBLE_LL:
            return isEmptyDoubleLL;
        case STR_LL:
            return isEmptyStrLL;
        default:
            return NULL;
    }
}

static void* reverse(Type type) {
    switch (type) {
        case INT_LL:
            return reverseIntLL;
        case DOUBLE_LL:
            return reverseDoubleLL;
        case STR_LL:
            return reverseStrLL;
        default:
            return NULL;
    }
}

static void* isEquals(Type type) {
    switch (type) {
        case INT_LL:
            return isEqualListsIntLL;
        case DOUBLE_LL:
            return isEqualListsDoubleLL;
        case STR_LL:
            return isEqualListsStrLL;
        default:
            return NULL;
    }
}

static void* size(Type type) {
    switch (type) {
        case INT_LL:
            return sizeIntLL;
        case DOUBLE_LL:
            return sizeDoubleLL;
        case STR_LL:
            return sizeStrLL;
        default:
            return NULL;
    }
}

static void* toString(Type type) {
    switch (type) {
        case INT_LL:
            return toStrIntLL;
        case DOUBLE_LL:
            return toStrDoubleLL;
        case STR_LL:
            return toStrStrLL;
        default:
            return NULL;
    }
}

static void* print(Type type) {
    switch (type) {
        case INT_LL:
            return printIntLL;
        case DOUBLE_LL:
            return printDoubleLL;
        case STR_LL:
            return printStrLL;
        default:
            return NULL;
    }
}

static void* delete(Type type) {
    switch (type) {
        case INT_LL:
            return deleteIntLL;
        case DOUBLE_LL:
            return deleteDoubleLL;
        case STR_LL:
            return deleteStrLL;
        default:
            return NULL;
    }
}

 static void initFuncs(Type type, void* data) {
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->add = add(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->add = add(type) : (((StrLinkedList) data)->add = add(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->addAll = addAll(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->addAll = addAll(type) : (((StrLinkedList) data)->addAll = addAll(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->get = get(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->get = get(type) : (((StrLinkedList) data)->get = get(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->set = set(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->set = set(type) : (((StrLinkedList) data)->set = set(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->indexOf = indexOf(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->indexOf = indexOf(type) : (((StrLinkedList) data)->indexOf = indexOf(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->sort = sort(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->sort = sort(type) : (((StrLinkedList) data)->sort = sort(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->sortReverse = sortReverse(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->sortReverse = sortReverse(type) : (((StrLinkedList) data)->sortReverse = sortReverse(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->clear = clear(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->clear = clear(type) : (((StrLinkedList) data)->clear = clear(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->contains = contains(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->contains = contains(type) : (((StrLinkedList) data)->contains = contains(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->containsAll = containsAll(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->containsAll = containsAll(type) : (((StrLinkedList) data)->containsAll = containsAll(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->containsAny = containsAny(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->containsAny = containsAny(type) : (((StrLinkedList) data)->containsAny = containsAny(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->removeElem = removeElem(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->removeElem = removeElem(type) : (((StrLinkedList) data)->removeElem = removeElem(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->removeAll = removeAll(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->removeAll = removeAll(type) : (((StrLinkedList) data)->removeAll = removeAll(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->subtract = subtract(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->subtract = subtract(type) : (((StrLinkedList) data)->subtract = subtract(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->isEmpty = isEmpty(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->isEmpty = isEmpty(type) : (((StrLinkedList) data)->isEmpty = isEmpty(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->reverse = reverse(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->reverse = reverse(type) : (((StrLinkedList) data)->reverse = reverse(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->isEquals = isEquals(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->isEquals = isEquals(type) : (((StrLinkedList) data)->isEquals = isEquals(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->size = size(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->size = size(type) : (((StrLinkedList) data)->size = size(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->toString = toString(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->toString = toString(type) : (((StrLinkedList) data)->toString = toString(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->print = print(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->print = print(type) : (((StrLinkedList) data)->print = print(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->delete = delete(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->delete = delete(type) : (((StrLinkedList) data)->delete = delete(type));
}

