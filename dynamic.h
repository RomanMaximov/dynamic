/*
 * MIT License
 *
 * Created by Roman Maximov on 09.11.2024
 *
 * Copyright (c) 2024 Roman Maximov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <stdbool.h>
#include "dynamicarray.h"
#include "string.h"
#include "map.h"
#include "linkedlist.h"


typedef struct LinkedListInt LinkedListInt;
typedef struct NodeInt NodeInt;
typedef struct IntArray IntArray;
typedef struct DoubleArray DoubleArray;
typedef struct String String;
typedef struct StringArray StringArray;
typedef struct StrStrTree StrStrTree;
typedef struct StrStrTreeMap StrStrTreeMap;


/**
 *  через дженерики создаем и удаляем коллекции
 */

#define newList(T) _Generic((T), \
    DoubleList : newDoubleArray,\
    IntList : newIntArray, \
    StringList : newStrArray,     \
    IntLinkedList : newIntLinkedList  \
)(T)

#define listOf(T, V, ...) _Generic((T), \
    DoubleList : listOfDouble, \
    IntList : listOfInt, \
    StringList : _Generic((V),      \
        char* : listOfStrLiteral,  \
        char* arr[] : listOfArrChar,  \
        default : listOfStr,  \
    ), \
    IntLinkedList : linkedListOfInt          \
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

/*#define add(T, V) _Generic((T), \
    IntList: addIntElem, \
    DoubleList: addDoubleElem, \
    string: addStrElem, \
    char* : addCharArrElem \
)(T, V)*/

#define addAll(T, V) _Generic((T), \
    DoubleList : addAllDouble,\
    IntList : addAllInt, \
    StringList : addAllStr         \
)(T, V)
//  IntList:   _Generic((V),\
//        IntLinkedList:   addAllIntListLL,\
//        IntSet: addAllIntListSet
//    ),\                                   \


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
    StringList : deleteStrList \
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

/*#define subtract(T, V) _Generic((T), \
    DoubleList : subtractDouble,\
    IntList : subtractInt,  \
    StringList : subtractStr \
)(T, V)*/

#define isEqualLists(T, V) _Generic((T), \
    DoubleList : isEqualDoubleLists,\
    IntList : isEqualIntLists,  \
    StringList : isEqualStrLists \
)(T, V)


#endif



