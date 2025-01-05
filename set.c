//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include "set.h"
#include "setservice/intset.h"
#include "collectiontypes.h"


// structures
typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct NodeInt {
    int data;
    struct NodeInt* left;
    struct NodeInt* right;
} NodeInt;

// Set data encapsulation
typedef struct InnerIntSet {
    int count;
    int capacity;
    NodeInt** bucket;
} InnerIntSet;

typedef SetInt* IntSet;
typedef NodeInt* IntNode;

// prototypes common funcs
static void initFuncs(Type type, void* data);
static void* add(Type type);
static void* addAll(Type type);
static void* clear(Type type);
static void* contains(Type type);
static void* containsAll(Type type);
static void* containsAny(Type type);
static void* removeElem(Type type);
static void* removeAll(Type type);
static void* isEmpty(Type type);
static void* isEquals(Type type);
static void* emptyIfNull(Type type);

static void* size(Type type);
static void* printList(Type type);
static void* deleteList(Type type);
static void* iterator(Type type);

// funcs
IntSet newIntSet(IntSet temp) {
    IntSet set = malloc(sizeof(SetInt));
    set->inner = malloc(sizeof(InnerIntSet));
    set->inner->count = 0;
    set->inner->capacity = 16;
    set->inner->bucket = malloc(set->inner->capacity * sizeof(NodeInt*));
    for (int i = 0; i < set->inner->capacity; ++i)
        set->inner->bucket[i] = NULL;
    
    initFuncs(INT_SET, (void*)set);

    return set;
}


// common init functions
static void* add(Type type) {
    switch (type) {
        case INT_SET:
            return addIntElemSet;
        /*case DOUBLE_SET:
            return addDoubleElemSet;
        case STR_SET:
            return addStrElemSet;*/
        default:
            return NULL;
    }
}

static void* addAll(Type type) {
    /*switch (type) {
        case INT_SET:
            return addAllIntElemSet;
        case DOUBLE_SET:
            return addAllDoubleElemSet;
        case STR_SET:
            return addAllStrElemSet;
        default:
            return NULL;
    }*/
}

static void* clear(Type type) {
    /*switch (type) {
        case INT_SET:
            return clearIntSet;
        case DOUBLE_SET:
            return clearDoubleSet;
        case STR_SET:
            return clearStrSet;
        default:
            return NULL;
    }*/
}

static void* contains(Type type) {
    /*switch (type) {
        case INT_SET:
            return containsIntSet;
        case DOUBLE_SET:
            return containsDoubleSet;
        case STR_SET:
            return containsStrSet;
        default:
            return NULL;
    }*/
}

static void* containsAll(Type type) {
    /*switch (type) {
        case INT_SET:
            return containsAllIntSet;
        case DOUBLE_SET:
            return containsAllDoubleSet;
        case STR_SET:
            return containsAllStrSet;
        default:
            return NULL;
    }*/
}

static void* containsAny(Type type) {
    /*switch (type) {
        case INT_SET:
            return containsAnyIntSet;
        case DOUBLE_SET:
            return containsAnyDoubleSet;
        case STR_SET:
            return containsAnyStrSet;
        default:
            return NULL;
    }*/
}

static void* removeElem(Type type) {
    /*switch (type) {
        case INT_SET:
            return removeIntSet;
        case DOUBLE_SET:
            return removeDoubleSet;
        case STR_SET:
            return removeStrSet;
        default:
            return NULL;
    }*/
}

static void* removeAll(Type type) {
    /*switch (type) {
        case INT_SET:
            return removeAllIntSet;
        case DOUBLE_SET:
            return removeAllDoubleSet;
        case STR_SET:
            return removeAllStrSet;
        default:
            return NULL;
    }*/
}

static void* isEmpty(Type type) {
    /*switch (type) {
        case INT_SET:
            return isEmptyIntSet;
        case DOUBLE_SET:
            return isEmptyDoubleSet;
        case STR_SET:
            return isEmptyStrSet;
        default:
            return NULL;
    }*/
}

static void* isEquals(Type type) {
    /*switch (type) {
        case INT_SET:
            return isEqualListsIntSet;
        case DOUBLE_SET:
            return isEqualListsDoubleSet;
        case STR_SET:
            return isEqualListsStrSet;
        default:
            return NULL;
    }*/
}

static void* emptyIfNull(Type type) {
    /*switch (type) {
        case INT_SET:
            return emptyIfNullIntSet;
        case DOUBLE_SET:
            return emptyIfNullDoubleSet;
        case STR_SET:
            return emptyIfNullStrSet;
        default:
            return NULL;
    }*/
}

static void* size(Type type) {
    /*switch (type) {
        case INT_SET:
            return sizeIntSet;
        case DOUBLE_SET:
            return sizeDoubleSet;
        case STR_SET:
            return sizeStrSet;
        default:
            return NULL;
    }*/
}

static void* iterator(Type type) {
    /*switch (type) {
        case INT_SET:
            return iteratorIntSet;
        case DOUBLE_SET:
            //return iteratorDoubleSet;
        case STR_SET:
            //return iteratorStrSet;
        default:
            return NULL;
    }*/
}

static void initFuncs(Type type, void* data) {
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->add = add(type) : type == DOUBLE_SET ? ((DoubleSet) data)->add = add(type) : (((StrSet) data)->add = add(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->addAll = addAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->addAll = addAll(type) : (((StrSet) data)->addAll = addAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->clear = clear(type) : type == DOUBLE_SET ? ((DoubleSet) data)->clear = clear(type) : (((StrSet) data)->clear = clear(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->contains = contains(type) : type == DOUBLE_SET ? ((DoubleSet) data)->contains = contains(type) : (((StrSet) data)->contains = contains(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAll = containsAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->containsAll = containsAll(type) : (((StrSet) data)->containsAll = containsAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->containsAny = containsAny(type) : type == DOUBLE_SET ? ((DoubleSet) data)->containsAny = containsAny(type) : (((StrSet) data)->containsAny = containsAny(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeElem = removeElem(type) : type == DOUBLE_SET ? ((DoubleSet) data)->removeElem = removeElem(type) : (((StrSet) data)->removeElem = removeElem(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->removeAll = removeAll(type) : type == DOUBLE_SET ? ((DoubleSet) data)->removeAll = removeAll(type) : (((StrSet) data)->removeAll = removeAll(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->isEmpty = isEmpty(type) : type == DOUBLE_SET ? ((DoubleSet) data)->isEmpty = isEmpty(type) : (((StrSet) data)->isEmpty = isEmpty(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->isEquals = isEquals(type) : type == DOUBLE_SET ? ((DoubleSet) data)->isEquals = isEquals(type) : (((StrSet) data)->isEquals = isEquals(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->emptyIfNull = emptyIfNull(type) : type == DOUBLE_SET ? ((DoubleSet) data)->emptyIfNull = emptyIfNull(type) : (((StrSet) data)->emptyIfNull = emptyIfNull(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->size = size(type) : type == DOUBLE_SET ? ((DoubleSet) data)->size = size(type) : (((StrSet) data)->size = size(type));
    type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->iterator = iterator(type) : type == DOUBLE_SET ? ((DoubleSet) data)->iterator = iterator(type) : (((StrSet) data)->iterator = iterator(type));
    //type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->printList = printList(type) : type == DOUBLE_SET ? ((DoubleLinkedList) data)->printList = printList(type) : (((StrLinkedList) data)->printList = printList(type));
    //type != DOUBLE_SET && type != STR_SET ? ((IntSet) data)->deleteList = deleteList(type) : type == DOUBLE_SET ? ((DoubleLinkedList) data)->deleteList = deleteList(type) : (((StrLinkedList) data)->deleteList = deleteList(type));
}