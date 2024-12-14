//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include "linkedlist.h"
#include "linkedlistservice/intlinkedlist.h"
#include "linkedlistservice/doublelinkedlist.h"
#include "linkedlistservice/strlinkedlist.h"

// structures
typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

// LinkedList data encapsulation
typedef struct InnerIntLL {
    int count;
    int index;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
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
    NodeDouble* nodes;
    NodeDouble* begin;
    NodeDouble* end;
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
    NodeStr* nodes;
    NodeStr* begin;
    NodeStr* end;
} InnerStrLL;

typedef struct IteratorInner {
    int count;
    bool (*hasNext)(void* data);
    void* (*next)(void* data);
} IteratorInner;

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;
typedef LinkedListDouble* DoubleLinkedList;
typedef NodeDouble* DoubleNode;
typedef LinkedListStr* StrLinkedList;
typedef NodeStr* StrNode;
typedef Itr* Iterator;


// custom types
typedef enum TypeLL {
    INT_LL,
    DOUBLE_LL,
    STR_LL
} TypeLL;


// prototypes common funcs
static void initFuncs(TypeLL type, void* data);
static void* add(TypeLL type);
static void* addAll(TypeLL type);
static void* get(TypeLL type);
static void* set(TypeLL type);
static void* indexOf(TypeLL type);
static void* sort(TypeLL type);
static void* sortReverse(TypeLL type);
static void* clear(TypeLL type);
static void* contains(TypeLL type);
static void* containsAll(TypeLL type);
static void* containsAny(TypeLL type);
static void* removeElem(TypeLL type);
static void* removeAll(TypeLL type);
static void* subtract(TypeLL type);
static void* isEmpty(TypeLL type);
static void* reverse(TypeLL type);
static void* isEquals(TypeLL type);
static void* emptyIfNull(TypeLL type);

static void* size(TypeLL type);
static void* printList(TypeLL type);
static void* deleteList(TypeLL type);


// funcs
Iterator iterator(void* list) {
    
}


IntLinkedList newIntLinkedList(IntLinkedList temp) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(INT_LL, (void*)list);

    return list;
}

IntLinkedList linkedListOfInt(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(INT_LL, (void*)list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntElemLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

DoubleLinkedList newDoubleLinkedList(DoubleLinkedList temp) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->inner = malloc(sizeof(InnerDoubleLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(DOUBLE_LL, (void*)list);

    return list;
}

DoubleLinkedList linkedListOfDouble(DoubleLinkedList temp, int paramCount, ...) {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->inner = malloc(sizeof(InnerDoubleLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(DOUBLE_LL, (void*)list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addDoubleElemLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

StrLinkedList newStrLinkedList(StrLinkedList temp) {
    StrLinkedList list = malloc(sizeof(LinkedListStr));
    list->inner = malloc(sizeof(InnerStrLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(STR_LL, (void*)list);

    return list;
}

StrLinkedList linkedListOfStr(StrLinkedList temp, int paramCount, ...) {
    StrLinkedList list = malloc(sizeof(LinkedListStr));
    list->inner = malloc(sizeof(InnerStrLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    list->inner->begin = NULL;
    list->inner->end = NULL;
    initFuncs(STR_LL, (void*)list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addStrElemLL(list, va_arg(param, string));
    }
    va_end(param);
    return list;
}

// common init functions
static void* add(TypeLL type) {
    switch (type) {
        case INT_LL:
            return addIntElemLL;
        case DOUBLE_LL:
            return addDoubleElemLL;
        case STR_LL:
            return addStrElemLL;
        default:
            return NULL;
    }
}

static void* addAll(TypeLL type) {
    switch (type) {
        case INT_LL:
            return addAllIntElemLL;
        case DOUBLE_LL:
            return addAllDoubleElemLL;
        case STR_LL:
            return addAllStrElemLL;
        default:
            return NULL;
    }
}

static void* get(TypeLL type) {
    switch (type) {
        case INT_LL:
            return getIntElemLL;
        case DOUBLE_LL:
            return getDoubleElemLL;
        case STR_LL:
            return getStrElemLL;
        default:
            return NULL;
    }
}

static void* set(TypeLL type) {
    switch (type) {
        case INT_LL:
            return setIntElemLL;
        case DOUBLE_LL:
            return setDoubleElemLL;
        case STR_LL:
            return setStrElemLL;
        default:
            return NULL;
    }
}

static void* indexOf(TypeLL type) {
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

static void* sort(TypeLL type) {
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

static void* sortReverse(TypeLL type) {
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

static void* clear(TypeLL type) {
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

static void* contains(TypeLL type) {
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

static void* containsAll(TypeLL type) {
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

static void* containsAny(TypeLL type) {
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

static void* removeElem(TypeLL type) {
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

static void* removeAll(TypeLL type) {
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

static void* subtract(TypeLL type) {
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

static void* isEmpty(TypeLL type) {
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

static void* reverse(TypeLL type) {
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

static void* isEquals(TypeLL type) {
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

static void* emptyIfNull(TypeLL type) {
    switch (type) {
        case INT_LL:
            return emptyIfNullIntLL;
        case DOUBLE_LL:
            return emptyIfNullDoubleLL;
        case STR_LL:
            return emptyIfNullStrLL;
        default:
            return NULL;
    }
}

static void* size(TypeLL type) {
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

 static void initFuncs(TypeLL type, void* data) {
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
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->emptyIfNull = emptyIfNull(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->emptyIfNull = emptyIfNull(type) : (((StrLinkedList) data)->emptyIfNull = emptyIfNull(type));
     type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->size = size(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->size = size(type) : (((StrLinkedList) data)->size = size(type));
     //type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->printList = printList(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->printList = printList(type) : (((StrLinkedList) data)->printList = printList(type));
     //type != DOUBLE_LL && type != STR_LL ? ((IntLinkedList) data)->deleteList = deleteList(type) : type == DOUBLE_LL ? ((DoubleLinkedList) data)->deleteList = deleteList(type) : (((StrLinkedList) data)->deleteList = deleteList(type));
}

