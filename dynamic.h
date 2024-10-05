#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <stdbool.h>
#include "dynamicarray.h"
#include "string.h"
#include "map.h"


typedef struct NodeInt {
    int data;
    struct NodeInt* next;
    struct NodeInt* prev;
} NodeInt;

typedef struct LinkedListInt {
    unsigned int count;
    NodeInt* nodes;
    NodeInt* begin;
    NodeInt* end;
} LinkedListInt;

typedef struct IntArray IntArray;
typedef struct DoubleArray DoubleArray;
typedef struct String String;
typedef struct StringArray StringArray;
typedef struct StrStrTree StrStrTree;
typedef struct StrStrTreeMap StrStrTreeMap;

#define newList(T) _Generic((T), \
    DoubleList : newDoubleArray,\
    IntList : newIntArray, \
    StringList : newStrArray \
)(T)

#define listOf(T, V, ...) _Generic((T), \
    DoubleList : listOfDouble, \
    IntList : listOfInt, \
    StringList : listOfStr,  \
    char* : listOfStrLiteral \
)(T, V, __VA_ARGS__)

#define listOfArr(T, V, K) _Generic((T), \
    DoubleList : listOfArrDouble,\
    IntList : listOfArrInt,              \
    StringList : listOfArrChar  \
)(T, V, K)

#define printList(T) _Generic((T), \
    DoubleList : printArrayDouble,\
    IntList : printArrayInt, \
    StringList : printArrayString \
)(T)

#define size(T) _Generic((T), \
    DoubleList : sizeDoubleList, \
    IntList : sizeIntList, \
    StringList : sizeStrList, \
    StrStrMap : sizeStrStrMap \
)(T)

#define add(T, V) _Generic((T), \
    IntList: addIntElem, \
    DoubleList: addDoubleElem, \
    string: addStrElem, \
    char* : addCharArrElem \
)(T, V)

#define addAll(T, V) _Generic((T), \
    DoubleList : addAllDouble,\
    IntList : addAllInt, \
    StringList : addAllStr  \
)(T, V)

#define getElem(T, V) _Generic((T), \
    DoubleList : getElemDouble,\
    IntList : getElemInt \
)(T, V)

#define setElem(T, V, K) _Generic((T), \
    DoubleList : setElemDouble,\
    IntList : setElemInt, \
    string : setElemStr,  \
    char* : setElemCharArr \
)(T, V, K)

#define toString(T) _Generic((T), \
    DoubleList : toStringDouble,\
    IntList : toStringInt \
)(T)

#define indexOf(T, V) _Generic((T), \
    DoubleList : indexOfDouble,\
    IntList : indexOfInt, \
    StringList : indexOfStrList,    \
    string : indexOfStr  \
)(T, V)

#define removeElem(T, V) _Generic((T), \
    DoubleList : removeElemDouble,\
    IntList : removeElemInt,  \
    StringList : removeElemStr \
)(T, V)

#define clear(T) _Generic((T), \
    DoubleList : clearDouble,\
    IntList : clearInt, \
    StringList : clearStrList, \
    StrStrMap : clearStrStrMap \
)(T)

#define deleteList(T) _Generic((T), \
    DoubleList : deleteArrayDouble,\
    IntList : deleteArrayInt, \
    StringList : deleteArrayString \
)(T)

#define sort(T) _Generic((T), \
    DoubleList : sortDouble, \
    IntList : sortInt, \
    StringList : sortStrList \
)(T)

#define contains(T, V) _Generic((T), \
    DoubleList : containsDouble,\
    IntList : containsInt,  \
    StringList : containsStr \
)(T, V)

#define containsAll(T, V) _Generic((T), \
    DoubleList : containsAllDouble,\
    IntList : containsAllInt,  \
    StringList : containsAllStr \
)(T, V)

#define containsAny(T, V) _Generic((T), \
    DoubleList : containsAnyDouble,\
    IntList : containsAnyInt,  \
    StringList : containsAnyStr \
)(T, V)

#define isEmpty(T) _Generic((T), \
    DoubleList : isEmptyDouble,\
    IntList : isEmptyInt, \
    StringList : isEmptyStrList, \
    string : isEmptyStr  \
)(T)

#define reverseList(T) _Generic((T), \
    DoubleList : reverseListDouble,\
    IntList : reverseListInt, \
    StringList : reverseListStr  \
)(T)

#define emptyIfNull(T) _Generic((T), \
    DoubleList : emptyIfNullDouble, \
    IntList : emptyIfNullInt, \
    StringList : emptyIfNullStr \
)(T)

#define subtract(T, V) _Generic((T), \
    DoubleList : subtractDouble,\
    IntList : subtractInt,  \
    StringList : subtractStr \
)(T, V)


typedef LinkedListInt* IntLinkedList;
typedef NodeInt* IntNode;

#endif



