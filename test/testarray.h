#ifndef TESTARRAY_H
#define TESTARRAY_H

#include "../dynamiccollection.h"
#define true 1
#define false 0

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN  "\033[1;32m"


void assertInt(int, int);
void assertDouble(double , double);
void assertStr(string , string);
void assertChar(char, char);
void testArrayList();
void testLinkedList();
void testSet();
void testString();


#endif
