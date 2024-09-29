#ifndef DYNAMIC_H
#define DYNAMIC_H

#define true 1
#define false 0


typedef struct LinkedListInt {
    unsigned int number;
    struct LinkedListInt* next;
    struct LinkedListInt* prev;
} LinkedListInt;

typedef struct intLinkedList {
    unsigned int count;
    struct LinkedListInt* linkedList;
    struct LinkedListInt* begin;
    struct LinkedListInt* end;
} intLinkedList;

typedef struct IntArray {
    unsigned int count;
    int* data;
    unsigned int capacity;
} IntArray;

typedef struct DoubleArray {
    unsigned int count;
    double* data;
    unsigned int capacity;
} DoubleArray;

typedef struct String {
    unsigned int count;
    char* data;
    unsigned int capacity;
} String;

typedef struct StringArray {
    unsigned int count;
    String** str;
    unsigned int capacity;
} StringArray;

typedef struct StrStrTree {
    String* key;
    String* value;
    struct StrStrTree* left;
    struct StrStrTree* right;
} StrStrTree;

typedef struct StrStrTreeMap {
    unsigned int count;
    struct StrStrTree* data;
} StrStrTreeMap;

#define newList(T) _Generic((T), \
    DoubleList : newDoubleArray,\
    IntList : newIntArray, \
    StringList : newStringArray \
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
    StringList : listOfCharArr  \
)(T, V, K)

#define printList(T) _Generic((T), \
    DoubleList : printArrayDouble,\
    IntList : printArrayInt, \
    StringList : printArrayString \
)(T)

#define size(T) _Generic((T), \
    DoubleList : sizeDoubleArray, \
    IntList : sizeIntArray, \
    StringList : sizeStringArray, \
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
    IntList : addAllInt \
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
    IntList : containsInt \
)(T, V)

#define isEmpty(T) _Generic((T), \
    DoubleList : isEmptyDouble,\
    IntList : isEmptyInt \
)(T)

#define reverseArray(T) _Generic((T), \
    DoubleList : reverseArrayDouble,\
    IntList : reverseArrayInt \
)(T)


typedef intLinkedList* IntLinkedList;
typedef String* string;
typedef StringArray* StringList;
typedef IntArray* IntList;
typedef DoubleArray* DoubleList;
typedef StrStrTreeMap* StrStrMap;


#endif



