//
// Created by Roman Maximov on 22.02.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdlib.h>
#include "iterator.h"
#include "arraylist.h"
#include "linkedlist.h"
#include "set.h"
#include "util/arraylistutil.h"

typedef struct Itr {
    int count;
    int collectionSize;
    void* collection;
    void* elemValue;
    void* array;
    Type type;
} Itr;

typedef struct ArrayListInt ArrayListInt;
typedef struct LinkedListInt LinkedListInt;
typedef struct LinkedListDouble LinkedListDouble;
typedef struct LinkedListStr LinkedListStr;
typedef struct String String;
typedef struct SetInt SetInt;
typedef struct SetDouble SetDouble;
typedef struct SetStr SetStr;
typedef SetInt* IntSet;

typedef ArrayListInt* IntList;
typedef LinkedListInt* IntLinkedList;
typedef LinkedListDouble* DoubleLinkedList;
typedef LinkedListStr* StrLinkedList;
typedef String* string;
typedef SetInt* IntSet;
typedef SetDouble* DoubleSet;
typedef SetStr* StrSet;
typedef Itr* Iterator;

typedef struct InnerIntList {
    int count;
    int* data;
    int capacity;
} InnerIntList;

typedef struct InnerDoubleList {
    int count;
    double* data;
    int capacity;
} InnerDoubleList;

typedef struct InnerStrList {
    int count;
    String** data;
    int capacity;
} InnerStrList;


Iterator iterator(void* source){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->elemValue = NULL;
    iter->array = NULL;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList collection = (IntList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = INT_LIST;
    }

    if (ctx->type == DOUBLE_LIST) {
        DoubleList collection = (DoubleList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = DOUBLE_LIST;
    }

    if (ctx->type == STR_LIST) {
        StrList collection = (StrList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = STR_LIST;
    }

    if (ctx->type == INT_LL) {
        IntLinkedList collection = (IntLinkedList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = INT_LL;
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList collection = (DoubleLinkedList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = DOUBLE_LL;
    }

    if (ctx->type == STR_LL) {
        StrLinkedList collection = (StrLinkedList) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        iter->type = STR_LL;
    }

    if (ctx->type == INT_SET) {
        IntSet collection = (IntSet) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        int* arr = malloc(collection->pf->count * sizeof(int));
        setToArrInt(collection, arr);
        iter->array = (void*) arr;
        iter->type = INT_SET;
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet collection = (DoubleSet) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        double* arr = malloc(collection->pf->count * sizeof(double));
        setToArrDouble(collection, arr);
        iter->array = (void*) arr;
        iter->type = DOUBLE_SET;
    }

    if (ctx->type == STR_SET) {
        StrSet collection = (StrSet) ctx->collection;
        iter->collection = collection;
        iter->collectionSize = collection->pf->count;
        StrList list = pr_initLs_(list, NULL);
        setToStrList(collection, list);
        iter->array = (void*) list;
        iter->type = STR_SET;
    }

    return iter;
}

bool hasNext(Iterator iter) {
    if (iter->count < iter->collectionSize) {
        iter->count++;
        return true;
    }

    return false;
}

int nextInt(Iterator iter) {
    if (iter->type == INT_LIST) {
        IntList collection = (IntList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == INT_LL) {
        IntLinkedList collection = (IntLinkedList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == INT_SET) {
        int* arr = (int*) iter->array;
        return arr[iter->count - 1];
    }

    return 0;
}

double nextDouble(Iterator iter) {
    if (iter->type == DOUBLE_LIST) {
        DoubleList collection = (DoubleList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == DOUBLE_LL) {
        DoubleLinkedList collection = (DoubleLinkedList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == DOUBLE_SET) {
        double* arr = (double*) iter->array;
        return arr[iter->count - 1];
    }

    return 0;
}

string nextStr(Iterator iter) {
    if (iter->type == STR_LIST) {
        StrList collection = (StrList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == STR_LL) {
        StrLinkedList collection = (StrLinkedList) iter->collection;
        return collection->get(collection, iter->count - 1);
    }

    if (iter->type == STR_SET) {
        StrList list = (StrList) iter->array;
        return list->pf->data[iter->count - 1];
    }

    return 0;
}

void deleteItr(Iterator* iter) {
    if (iter == NULL || *iter == NULL) return;

    free(*iter);
    *iter = NULL;
}