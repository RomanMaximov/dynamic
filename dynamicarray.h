#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "string.h"
#include "map.h"


typedef struct IntArray IntArray;
typedef struct DoubleArray DoubleArray;
typedef struct StringArray StringArray;
typedef struct String String;

typedef IntArray* IntList;
typedef DoubleArray* DoubleList;
typedef StringArray* StringList;
typedef String* string;

IntList newIntArray(IntList);
DoubleList newDoubleArray(DoubleList);
StringList newStrArray(StringList);

int sizeIntList(IntList);
int sizeDoubleList(DoubleList);
int sizeStrList(StringList);

void addIntElem(IntList, int);
void addDoubleElem(DoubleList, double);
void addStrElem(string, StringList);
void addCharArrElem(char*, StringList);

IntList listOfArrInt(IntList, int*, int);
DoubleList listOfArrDouble(DoubleList, double*, int);
StringList listOfArrChar(StringList, char* arr[], int);

IntList listOfInt(IntList, int, ...);
DoubleList listOfDouble(DoubleList, int, ...);
StringList listOfStr(StringList, int, ...);
StringList listOfStrLiteral(char*, int, ...);

void addAllInt(IntList, IntList);
void addAllDouble(DoubleList, DoubleList);
void addAllStr(StringList, StringList);

int getElemInt(IntList, int);
double getElemDouble(DoubleList, int);
string getElemStr(StringList, int);

void setElemInt(IntList, int, int);
void setElemDouble(DoubleList, int, double);
bool setElemStr(string, StringList, int);
bool setElemCharArr(char*, StringList, int);

void removeElemInt(IntList, int);
void removeElemDouble(DoubleList, int);
void removeElemStr(StringList, int);

bool removeAllInt(IntList, IntList);
bool removeAllDouble(DoubleList, DoubleList);
bool removeAllStr(StringList, StringList);

char* toStringInt(IntList);
char* toStringDouble(DoubleList);

void printArrayInt(IntList);
void printArrayDouble(DoubleList);
void printArrayString(StringList);

void clearInt(IntList);
void clearDouble(DoubleList);
void clearStrList(StringList);

void deleteArrayInt(IntList);
void deleteArrayDouble(DoubleList);
void deleteArrayString(StringList);

void sortInt(IntList);
void sortDouble(DoubleList);
void sortStrList(StringList);
void sortReverseStrList(StringList);

bool containsInt(IntList, int);
bool containsDouble(DoubleList, double);
bool containsStr(StringList, string);

bool containsAllInt(IntList, IntList);
bool containsAllDouble(DoubleList, DoubleList);
bool containsAllStr(StringList, StringList);

bool containsAnyInt(IntList, IntList);
bool containsAnyDouble(DoubleList, DoubleList);
bool containsAnyStr(StringList, StringList);

IntList subtractInt(IntList, IntList);
DoubleList subtractDouble(DoubleList, DoubleList);
StringList subtractStr(StringList, StringList);

bool isEmptyInt(IntList);
bool isEmptyDouble(DoubleList);
bool isEmptyStrList(StringList);

void reverseListInt(IntList);
void reverseListDouble(DoubleList);
void reverseListStr(StringList);

int indexOfInt(IntList, int);
int indexOfDouble(DoubleList, double);
int indexOfStrList(StringList, string);

bool isEqualStrLists(StringList, StringList);
// bool isEqualIntLists(IntList, IntList);
// bool isEqualDoubleLists(DoubleList, DoubleList);

IntList emptyIfNullInt(IntList);
DoubleList emptyIfNullDouble(DoubleList);
StringList emptyIfNullStr(StringList);

#endif

