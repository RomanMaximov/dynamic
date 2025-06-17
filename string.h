//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include "arraylist.h"

typedef unsigned char byte;

// structures
typedef struct String {
    struct InnerStr* pf;   // private field
    int (*length)(struct String* str);
    void (*concat)(struct String* str1, struct String* str2);
    void (*replace)(struct String* str, char* ch1, char* ch2);
    void (*toLowerCase)(struct String* str);
    void (*toUpperCase)(struct String* str);
    char (*charAt)(struct String* str, int index);
    bool (*containsSubStr)(struct String* str, struct String* subStr);
    bool (*startsWith)(struct String* str, char* subStr);
    bool (*endsWith)(struct String* str, char* subStr);
    void (*reverse)(struct String* str);
    int (*indexOf)(struct String* str, char ch);
    int (*indexOfSubStr)(struct String* str, struct String* subStr);
    struct ArrayListStr* (*split)(struct String* str, char* delimeter);
    void (*trim)(struct String* str);
    bool (*isEmpty)(struct String* str);
    bool (*isBlank)(struct String* str);
    byte* (*getBytes)(struct String* str);
    void (*print)(struct String* str);
    void (*delete)(struct String** str);
} String;

typedef String* string;
typedef struct ArrayListStr ArrayListStr;
typedef ArrayListStr* StrList;


string strOf(char* s);
string emptyStr();
string defaultIfNull(string str, char* defaultStr);
string join(char* delimeter, int countParams, ...);
string joinFromList(StrList list, char* delimeter);
char* toCharArr(string s);


#endif
