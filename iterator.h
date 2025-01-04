//
// Created by Roman Maximov on 04.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include "collectiontypes.h"

#define nextValue(T) _Generic((T), \
    Iterator : getNextInt \
)(T)

typedef struct Itr {
    int count;
    int collectionSize;
    void* data;
    Type type;
    bool (*hasNext)(struct Itr* iter);
} Itr;

typedef struct LinkedListInt LinkedListInt;
typedef struct LinkedListDouble LinkedListDouble;
typedef struct LinkedListStr LinkedListStr;

typedef LinkedListInt* IntLinkedList;
typedef LinkedListDouble* DoubleLinkedList;
typedef LinkedListStr* StrLinkedList;
typedef Itr* Iterator;



static int getNextInt(Iterator iter) {
    if (iter->type == INT_LL) {
        if (iter->hasNext) {
            IntLinkedList list = (IntLinkedList) iter->data;
            int number = getIntElemLL(list, iter->count);
            iter->count++;
            return number;
        }
    }

    return -INT_MAX;
}

#endif
