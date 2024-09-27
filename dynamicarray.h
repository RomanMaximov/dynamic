#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "string.h"
#include "dynamic.h"
#include "map.h"




IntList newIntArray(IntList);
DoubleList newDoubleArray(DoubleList);
StringList newStringArray(StringList);

int sizeIntArray(IntList);
int sizeDoubleArray(DoubleArray*);
int sizeStringArray(StringList);

void addIntElem(IntList, int);
void addDoubleElem(DoubleList, double);
void addStringElem(StringList, string);

IntList intArrayOf(IntList, int [], int);
DoubleList doubleArrayOf(DoubleList, double [], int);
StringList stringListOf(int, ...);

void addAllInt(IntList, IntList);
void addAllDouble(DoubleList, DoubleList);

unsigned int getElemInt(IntList, int);
double getElemDouble(DoubleList, int);

void setElemInt(IntList, int, int);
void setElemDouble(DoubleList, int, double);

void removeElemInt(IntList, int);
void removeElemDouble(DoubleList, int);

char* toStringInt(IntList);
char* toStringDouble(DoubleList);

void printArrayInt(IntList);
void printArrayDouble(DoubleList);
void printArrayString(StringList);

void clearInt(IntList);
void clearDouble(DoubleList);

void deleteArrayInt(IntList);
void deleteArrayDouble(DoubleList);
void deleteArrayString(StringList);

void sortInt(IntList);
void sortDouble(DoubleList);

bool containsInt(IntList, int);
bool containsDouble(DoubleList, double);

int isEmptyInt(IntList);
int isEmptyDouble(DoubleList);

void reverseArrayInt(IntList);
void reverseArrayDouble(DoubleList);


#endif

