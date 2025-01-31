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

// structures
/*typedef struct String {
    int count;
    char* data;
    int capacity;
} String;*/

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
    String** data;
    int capacity;
} InnerStrList;


typedef ArrayListInt* IntList;
typedef ArrayListDouble* DoubleList;
typedef ArrayListStr* StrList;
typedef String* string;
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
static void* print(Type type);
static void* delete(Type type);
static void* toString(Type type);
static void* iterator(Type type);


// funcs
IntList pr_initLi_(IntList temp) {
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

DoubleList pr_initLd_(DoubleList temp) {
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

StrList pr_initLs_(StrList temp) {
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

    return list;
}

StrList listOfStr(StrList temp, int paramCount, ...) {
    StrList list = malloc(sizeof(ArrayListStr));
    /*list->pf = malloc(sizeof(InnerStrList));
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->str = malloc(list->pf->capacity * sizeof(String*));
    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->str[i] = NULL;

    initFuncs(STR_LIST, (void*)list);

    va_list param;
    va_start(param, paramCount);
    for (int i = 0; i < paramCount; ++i) {
        addStrElemList(list, va_arg(param, string));
    }
    va_end(param);*/
    return list;
}

/*StringList listOfStrLiteral(StringList temp, char* arr, int size, ...) {
    StringList list = newStrArray(list);

    va_list counter;
    va_start(counter, size);

    unsigned long long int dataSize;

    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacityStr(list);
        }

        char* arg = va_arg(counter, char*);
        dataSize = strlen(arg);
        list->str[i] = malloc(sizeof(String));
        list->str[i]->data = malloc((dataSize + 1) * sizeof(char));
        list->str[i]->count = dataSize;
        list->str[i]->capacity = dataSize;
        strcpy(list->str[i]->data, arg);
        list->count++;
    }
    va_end(counter);

    return list;
}*/

/*StringList listOfArrChar(StringList temp, char* arr[], int size) {
    StringList list = newStrArray(list);

    unsigned long long int dataSize;
    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacityStr(list);
        }

        char* data = arr[i];
        dataSize = strlen(data);
        list->str[i] = malloc(sizeof(String));
        list->str[i]->data = malloc((dataSize + 1) * sizeof(char));
        list->str[i]->count = dataSize;
        list->str[i]->capacity = dataSize;
        strcpy(list->str[i]->data, data);
        list->count++;
    }

    return list;
}*/


// common init functions
static void* add(Type type) {
    switch (type) {
        case INT_LIST:
            return addIntList;
        case DOUBLE_LIST:
            return addDoubleList;
        case STR_LIST:
            return addStrList;
        default:
            return NULL;
    }
}

static void* addAll(Type type) {
    switch (type) {
        case INT_LIST:
            return addAllIntList;
        case DOUBLE_LIST:
            return addAllDoubleList;
        case STR_LIST:
            return addAllStrList;
        default:
            return NULL;
    }
}

static void* get(Type type) {
    switch (type) {
        case INT_LIST:
            return getIntList;
        case DOUBLE_LIST:
            return getDoubleList;
        case STR_LIST:
            return getStrList;
        default:
            return NULL;
    }
}

static void* set(Type type) {
    switch (type) {
        case INT_LIST:
            return setIntList;
        case DOUBLE_LIST:
            return setDoubleList;
        case STR_LIST:
            return setStrList;
        default:
            return NULL;
    }
}

static void* indexOf(Type type) {
    switch (type) {
        case INT_LIST:
            return indexOfIntList;
        case DOUBLE_LIST:
            return indexOfDoubleList;
        case STR_LIST:
            return indexOfStrList;
        default:
            return NULL;
    }
}

static void* sort(Type type) {
    switch (type) {
        case INT_LIST:
            return sortIntList;
        case DOUBLE_LIST:
            return sortDoubleList;
        case STR_LIST:
            return sortStrList;
        default:
            return NULL;
    }
}

static void* sortReverse(Type type) {
    switch (type) {
        case INT_LIST:
            return sortIntListReverse;
        case DOUBLE_LIST:
            return sortDoubleListReverse;
        case STR_LIST:
            return sortStrListReverse;
        default:
            return NULL;
    }
}

static void* clear(Type type) {
    switch (type) {
        case INT_LIST:
            return clearIntList;
        case DOUBLE_LIST:
            return clearDoubleList;
        case STR_LIST:
            return clearStrList;
        default:
            return NULL;
    }
}

static void* contains(Type type) {
    switch (type) {
        case INT_LIST:
            return containsIntList;
        case DOUBLE_LIST:
            return containsDoubleList;
        case STR_LIST:
            return containsStrList;
        default:
            return NULL;
    }
}

static void* containsAll(Type type) {
    switch (type) {
        case INT_LIST:
            return containsAllIntList;
        case DOUBLE_LIST:
            return containsAllDoubleList;
        case STR_LIST:
            return containsAllStrList;
        default:
            return NULL;
    }
}

static void* containsAny(Type type) {
    switch (type) {
        case INT_LIST:
            return containsAnyIntList;
        case DOUBLE_LIST:
            return containsAnyDoubleList;
        case STR_LIST:
            return containsAnyStrList;
        default:
            return NULL;
    }
}

static void* removeElem(Type type) {
    switch (type) {
        case INT_LIST:
            return removeIntList;
        case DOUBLE_LIST:
            return removeDoubleList;
        case STR_LIST:
            return removeStrList;
        default:
            return NULL;
    }
}

static void* removeAll(Type type) {
    switch (type) {
        case INT_LIST:
            return removeAllIntList;
        case DOUBLE_LIST:
            return removeAllDoubleList;
        case STR_LIST:
            return removeAllStrList;
        default:
            return NULL;
    }
}

static void* subtract(Type type) {
    switch (type) {
        case INT_LIST:
            return subtractIntList;
        case DOUBLE_LIST:
            return subtractDoubleList;
        case STR_LIST:
            return subtractStrList;
        default:
            return NULL;
    }
}

static void* isEmpty(Type type) {
    switch (type) {
        case INT_LIST:
            return isEmptyIntList;
        case DOUBLE_LIST:
            return isEmptyDoubleList;
        case STR_LIST:
            return isEmptyStrList;
        default:
            return NULL;
    }
}

static void* reverse(Type type) {
    switch (type) {
        case INT_LIST:
            return reverseIntList;
        case DOUBLE_LIST:
            return reverseDoubleList;
        case STR_LIST:
            return reverseStrList;
        default:
            return NULL;
    }
}

static void* isEquals(Type type) {
    switch (type) {
        case INT_LIST:
            return isEqualsIntList;
        case DOUBLE_LIST:
            return isEqualsDoubleList;
        case STR_LIST:
            return isEqualsStrList;
        default:
            return NULL;
    }
}

static void* size(Type type) {
    switch (type) {
        case INT_LIST:
            return sizeIntList;
        case DOUBLE_LIST:
            return sizeDoubleList;
        case STR_LIST:
            return sizeStrList;
        default:
            return NULL;
    }
}

static void* toString(Type type) {
    switch (type) {
        case INT_LIST:
            return toStrIntList;
        case DOUBLE_LIST:
            return toStrDoubleList;
        case STR_LIST:
            return toStrStrList;
        default:
            return NULL;
    }
}

static void* print(Type type) {
    switch (type) {
        case INT_LIST:
            return printIntList;
        case DOUBLE_LIST:
            return printDoubleList;
        case STR_LIST:
            return printStrList;
        default:
            return NULL;
    }
}

static void* delete(Type type) {
    switch (type) {
        case INT_LIST:
            return deleteIntList;
        case DOUBLE_LIST:
            return deleteDoubleList;
        case STR_LIST:
            return deleteStrList;
        default:
            return NULL;
    }
}

static void* iterator(Type type) {
    switch (type) {
        case INT_LIST:
            return iteratorIntList;
        case DOUBLE_LIST:
            return iteratorDoubleList;
        case STR_LIST:
            return iteratorStrList;
        default:
            return NULL;
    }
}

static void* joinList(Type type) {
    return joinStrList;
}

static void initFuncs(Type type, void* data) {
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->add = add(type) : type == DOUBLE_LIST ? ((DoubleList) data)->add = add(type) : (((StrList) data)->add = add(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->addAll = addAll(type) : type == DOUBLE_LIST ? ((DoubleList) data)->addAll = addAll(type) : (((StrList) data)->addAll = addAll(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->get = get(type) : type == DOUBLE_LIST ? ((DoubleList) data)->get = get(type) : (((StrList) data)->get = get(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->set = set(type) : type == DOUBLE_LIST ? ((DoubleList) data)->set = set(type) : (((StrList) data)->set = set(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->indexOf = indexOf(type) : type == DOUBLE_LIST ? ((DoubleList) data)->indexOf = indexOf(type) : (((StrList) data)->indexOf = indexOf(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->sort = sort(type) : type == DOUBLE_LIST ? ((DoubleList) data)->sort = sort(type) : (((StrList) data)->sort = sort(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->sortReverse = sortReverse(type) : type == DOUBLE_LIST ? ((DoubleList) data)->sortReverse = sortReverse(type) : (((StrList) data)->sortReverse = sortReverse(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->clear = clear(type) : type == DOUBLE_LIST ? ((DoubleList) data)->clear = clear(type) : (((StrList) data)->clear = clear(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->contains = contains(type) : type == DOUBLE_LIST ? ((DoubleList) data)->contains = contains(type) : (((StrList) data)->contains = contains(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->containsAll = containsAll(type) : type == DOUBLE_LIST ? ((DoubleList) data)->containsAll = containsAll(type) : (((StrList) data)->containsAll = containsAll(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->containsAny = containsAny(type) : type == DOUBLE_LIST ? ((DoubleList) data)->containsAny = containsAny(type) : (((StrList) data)->containsAny = containsAny(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->removeElem = removeElem(type) : type == DOUBLE_LIST ? ((DoubleList) data)->removeElem = removeElem(type) : (((StrList) data)->removeElem = removeElem(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->removeAll = removeAll(type) : type == DOUBLE_LIST ? ((DoubleList) data)->removeAll = removeAll(type) : (((StrList) data)->removeAll = removeAll(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->subtract = subtract(type) : type == DOUBLE_LIST ? ((DoubleList) data)->subtract = subtract(type) : (((StrList) data)->subtract = subtract(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->isEmpty = isEmpty(type) : type == DOUBLE_LIST ? ((DoubleList) data)->isEmpty = isEmpty(type) : (((StrList) data)->isEmpty = isEmpty(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->reverse = reverse(type) : type == DOUBLE_LIST ? ((DoubleList) data)->reverse = reverse(type) : (((StrList) data)->reverse = reverse(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->isEquals = isEquals(type) : type == DOUBLE_LIST ? ((DoubleList) data)->isEquals = isEquals(type) : (((StrList) data)->isEquals = isEquals(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->size = size(type) : type == DOUBLE_LIST ? ((DoubleList) data)->size = size(type) : (((StrList) data)->size = size(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->toString = toString(type) : type == DOUBLE_LIST ? ((DoubleList) data)->toString = toString(type) : (((StrList) data)->toString= toString(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->iterator = iterator(type) : type == DOUBLE_LIST ? ((DoubleList) data)->iterator = iterator(type) : (((StrList) data)->iterator = iterator(type));
    if (type == STR_LIST)
        ((StrList) data)->joinList = joinList(type);
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->print = print(type) : type == DOUBLE_LIST ? ((DoubleList) data)->print = print(type) : (((StrList) data)->print = print(type));
    type != DOUBLE_LIST && type != STR_LIST ? ((IntList) data)->delete = delete(type) : type == DOUBLE_LIST ? ((DoubleList) data)->delete = delete(type) : (((StrList) data)->delete = delete(type));
}