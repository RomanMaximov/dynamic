#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include "dynamic.h"


IntLinkedList newIntLinkedList();
unsigned int sizeList(IntLinkedList);
bool isEmptyIntLinkedList(IntLinkedList);
void fillNode(LinkedListInt*, unsigned int);
void insertBegin(IntLinkedList, unsigned int);
void insertEnd(IntLinkedList, unsigned int);
IntLinkedList linkedListOf(int, ...);
void printLinkedList(IntLinkedList);
void deleteLinkedList(IntLinkedList);


#endif
