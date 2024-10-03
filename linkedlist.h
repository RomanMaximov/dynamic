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

int sizeIntLinkedList(IntLinkedList);
// int sizeDoubleLinkedList(DoubleLinkedList);
// int sizeStrLinkedList(StringLinkedList);

bool isEmptyIntLinkedList(IntLinkedList);
// bool isEmptyDoubleLinkedList(DoubleLinkedList);
// bool isEmptyStrLinkedList(StringLinkedList);

void fillNode(IntNode, int);


void insertBegin(IntLinkedList, int);
void insertEnd(IntLinkedList, unsigned int);
IntLinkedList linkedListOf(int, ...);
void printLinkedList(IntLinkedList);
void deleteLinkedList(IntLinkedList);


#endif
