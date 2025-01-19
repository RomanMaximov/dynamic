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
    struct String* (*strOf)(char* s);
    struct String* (*emptyStr)();
    int (*length)(struct String* s);
    struct String* (*concat)(struct String* s1, struct String* s2);
    struct String* (*replace)(struct String* s, char ch1, char ch2);
    struct String* (*toLowerCase)(struct String* s);
    struct String* (*toUpperCase)(struct String* s);
    struct String* (*join)(char* delimeter, int countParams, ...);
    char (*charAt)(struct String* s, int index);
    bool (*containsSubStr)(struct String* str, struct String* subStr);
    bool (*startsWith)(struct String* str, struct String* subStr);
    bool (*endsWith)(struct String* str, struct String* subStr);
    struct String* (*reverseStr)(struct String* s);
    int (*indexOfStr)(struct String* s, char ch);
    int (*indexOfSubStr)(struct String* str, struct String* subStr);
    struct ArrayListStr* (*split)(struct String* str, char delimeter);
    struct String* (*trim)(struct String* s);
    struct String* (*isEmpty)(struct String* s);
    struct String* (*isBlank)(struct String* s);
    struct String* (*isNotBlank)(struct String* s);
    struct String* (*joinStrList)(struct ArrayListStr* str, char delimeter);
    struct String* (*defaultIfNull)(struct String* str1, struct String* str2);
    //void (*printString)(struct String* list);
    //void (*deleteString)(struct String* list);
} String;

typedef String* string;
typedef struct ArrayListStr ArrayListStr;
typedef ArrayListStr* StrList;


string stringOf(char* s);
string emptyStr();
int length(string s);
string concat(string s1, string s2);
string replace(string s, char ch1, char ch2);
string toLowerCase(string s);
string toUpperCase(string s);
string join(char* delimeter, int countParams, ...);
char charAt(string s, int index);
bool containsSubStr(string str, string substr);
bool startsWith(string str, string substr);
bool endsWith(string str, string substr);
string reverseStr(string s);
int indexOfStr(string s, char ch);
int indexOfSubStr(string str, string sub);
StrList split(string s, char delimeter);
string trim(string s);
bool isEmptyStr(string s);
bool isBlank(string s);
bool isNotBlank(string s);
string joinStrList(StrList list, char* delimeter);
string defaultIfNull(string, string);

void printString(string s);
void deleteString(string* s);


#endif
