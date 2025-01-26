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
    void (*replace)(struct String* str, char ch1, char ch2);
    void (*toLowerCase)(struct String* str);
    void (*toUpperCase)(struct String* str);
    char (*charAt)(struct String* str, int index);
    bool (*containsSubStr)(struct String* str, struct String* subStr);
    bool (*startsWith)(struct String* str, struct String* subStr);
    bool (*endsWith)(struct String* str, struct String* subStr);
    void (*reverse)(struct String* str);
    int (*indexOf)(struct String* str, char ch);
    int (*indexOfSubStr)(struct String* str, struct String* subStr);
    struct ArrayListStr* (*split)(struct String* str, char* delimeter);
    void (*trim)(struct String* str);
    bool (*isEmpty)(struct String* str);
    bool (*isBlank)(struct String* str);
    bool (*isNotBlank)(struct String* str);
    struct String* (*defaultIfNull)(struct String* str1, struct String* str2);
    byte* (*getBytes)(struct String* str);
    void (*print)(struct String* str);
    void (*delete)(struct String** str);
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

//void printString(string s);
//oid deleteString(string* s);


#endif
