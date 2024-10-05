#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include "dynamic.h"


IntLinkedList newIntLinkedList();
// DoubleLinkedList newDoubleLinkedList();
// StringLinkedList newStrLinkedList();

IntLinkedList linkedListOfInt(IntLinkedList, int, ...);

int sizeIntLinkedList(IntLinkedList);
// int sizeDoubleLinkedList(DoubleLinkedList);
// int sizeStrLinkedList(StringLinkedList);

bool isEmptyIntLinkedList(IntLinkedList);
// bool isEmptyDoubleLinkedList(DoubleLinkedList);
// bool isEmptyStrLinkedList(StringLinkedList);


//void insertBeginInt(IntLinkedList, int);
// void insertBeginDouble(DoubleLinkedList, double );
// void insertBeginStr(StringLinkedList, string);


void insertEndInt(IntLinkedList, int);  // add
// void insertEndDouble(DoubleLinkedList, double );
// void insertEndStr(StringLinkedList, string);




void printIntLinkedList(IntLinkedList);


void deleteIntLinkedList(IntLinkedList);

// add
// addAll
// get(int index)
// set(index, elem)
// indexOf
// toString
// sort
// clear
// contains
// containsAll
// containsAny
// remove
// removeAll
// subtract
// isEmpry
// reverseList
// isEqualLists
// emptyIfNull

#endif
