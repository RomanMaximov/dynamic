//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include "arraylist.h"

// structures
typedef struct String {
    struct InnerStr* pf;   // private field
    int (*length)(struct String* str);
    struct String* (*concat)(struct String* str1, struct String* str2);
    struct String* (*replace)(struct String* str, char ch1, char ch2);
    struct String* (*toLowerCase)(struct String* str);
    struct String* (*toUpperCase)(struct String* str);
    struct String* (*join)(char* delimeter, int countParams, ...); // TODO
    char (*charAt)(struct String* str, int index);
    bool (*containsSubStr)(struct String* str, struct String* subStr);
    bool (*startsWith)(struct String* str, struct String* subStr);
    bool (*endsWith)(struct String* str, struct String* subStr);
    struct String* (*reverse)(struct String* str);
    int (*indexOf)(struct String* str, char ch);
    int (*indexOfSubStr)(struct String* str, struct String* subStr);
    struct ArrayListStr* (*split)(struct String* str, char delimeter);
    struct String* (*trim)(struct String* str);
    struct String* (*isEmpty)(struct String* str);
    struct String* (*isBlank)(struct String* str);
    struct String* (*isNotBlank)(struct String* str);
    //struct String* (*joinStrList)(struct ArrayListStr* str, char delimeter);
    struct String* (*defaultIfNull)(struct String* str1, struct String* str2);
    //void (*printString)(struct String* list);
    //void (*deleteString)(struct String* list);
} String;

typedef String* string;
typedef struct ArrayListStr ArrayListStr;
typedef ArrayListStr* StrList;


string strOf(char* s);
string emptyStr();
//int length(string s);
//string concat(string s1, string s2);
//string replace(string s, char ch1, char ch2);
//string toLowerCase(string s);
//string toUpperCase(string s);
string joinStr(char* delimeter, int countParams, ...);
//char charAt(string s, int index);
//bool containsSubStr(string str, string substr);
//bool startsWith(string str, string substr);
//bool endsWith(string str, string substr);
//string reverseStr(string s);
//int indexOfStr(string s, char ch);
//int indexOfSubStr(string str, string sub);
//StrList split(string s, char delimeter);
//string trim(string s);
//bool isEmptyStr(string s);
//bool isBlank(string s);
//bool isNotBlank(string s);
//string joinStrList(StrList list, char* delimeter);
//string defaultIfNull(string, string);

void printString(string s);
void deleteString(string* s);


#endif
