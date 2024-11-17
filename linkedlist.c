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

typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;
typedef LinkedListDouble* DoubleLinkedList;
typedef NodeDouble* DoubleNode;
typedef LinkedListStr* StrLinkedList;
typedef NodeStr* StrNode;


// custom types
typedef enum TypeLL {
    INT_LL,
    DOUBLE_LL,
    STR_LL
} TypeLL;

#define getType(T, V) _Generic((T), \
    IntLinkedList : getIntLLType, \
    DoubleLinkedList : getDoubleLLType, \
    StrLinkedList : getStrLLType \
)(T, V)



// prototypes common funcs
static void _initFuncs_(TypeLL type, void* data);
static void initInt(IntLinkedList list, TypeLL type);
static void* add(TypeLL type);
static void* addAll(TypeLL type);
static void* get(TypeLL type);
static void* set(TypeLL type);
static void* indexOf(TypeLL type);
static void* sort(TypeLL type);
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
IntLinkedList newIntLinkedList() {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    _initFuncs_(INT_LL, (void*)list);
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;

    return list;
}

DoubleLinkedList newDoubleLinkedList() {
    DoubleLinkedList list = malloc(sizeof(LinkedListDouble));
    list->inner = malloc(sizeof(InnerDoubleLL));
    _initFuncs_(DOUBLE_LL, (void*)list);
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;

    return list;
}

IntLinkedList linkedListOfInt(IntLinkedList temp, int paramCount, ...) {
    IntLinkedList list = malloc(sizeof(LinkedListInt));
    list->inner = malloc(sizeof(InnerIntLL));
    list->inner->count = 0;
    list->inner->index = 0;
    list->inner->nodes = NULL;
    _initFuncs_(INT_LL, (void*)list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addIntElemLL(list, va_arg(param, int));
    }
    va_end(param);
    return list;
}

// common functions
static void* add(TypeLL type) {
    switch (type) {
        case INT_LL:
            return addIntElemLL;
        /*case DOUBLE_LL:
            return addDoubleElemLL;
        case STR_LL:
            return addStrElemLL;*/
        default:
            return NULL;
    }
}

static void* set(TypeLL type) {
    switch (type) {
        case INT_LL:
            return setIntElemLL;
    }

    return NULL;
}



/*IntLinkedList getIntLLType(IntLinkedList temp, void* data) {
    IntLinkedList list = (IntLinkedList) data;
    return list;
}

DoubleLinkedList getDoubleLLType(DoubleLinkedList temp, void* data) {
    DoubleLinkedList list = (DoubleLinkedList) data;
    return list;
}

StrLinkedList getStrLLType(StrLinkedList temp, void* data) {
    StrLinkedList list = (StrLinkedList) data;
    return list;
}*/

 static void _initFuncs_(TypeLL type, void* data) {
     IntLinkedList intList;
     // DoubleLinkedList list
     // StrLinkedList list

     void* list;
     switch (type) {
         case INT_LL:
             intList = (IntLinkedList) data;
             initInt(intList, type);
     }


}

static void initInt(IntLinkedList list, TypeLL type) {
    list->add = add(type);
    //list->addAll = addAll(type);
    //list->get = get(type);
    list->set = set(type);
    //list->indexOf = indexOf(type);
    //list->sort = sort(type);
    //list->clear = clear(type);
    //list->contains = contains(type);
    //list->containsAll = containsAll(type);
    //list->containsAny = containsAny(type);
    //list->removeElem = removeElem(type);
    //list->removeAll = removeAll(type);
    //list->subtract = subtract(type);
    //list->isEmpty = isEmpty(type);
    //list->reverse = reverse(type);
    //list->isEquals = isEquals(type);
    //list->emptyIfNull = emptyIfNull(type);

    //list->size = size(type);
    //list->printList = printList(type);
    //list->deleteList = deleteList(type);
}

