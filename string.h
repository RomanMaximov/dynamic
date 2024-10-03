#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include "dynamic.h"


string stringOf(char* s);
string emptyStr();
int compareTo(string s1, string s2);
int length(string s);
string concat(string s1, string s2);
string replace(string s1, char ch1, char ch2);
string toLowerCase(string s1);
string toUpperCase(string s1);
string join(char* delimeter, int countParams, ...);
void printString(string s);
void deleteString(string s);
char charAt(string s, int index);
int containsSubStr(string str, string substr);
bool startsWith(string str, string substr);
bool endsWith(string str, string substr);
string reverseStr(string s);
long indexOfStr(string s, char ch);
long indexOfSubStr(string str, string sub);
StringArray* split(string s, char delimeter);
string trim(string s);
bool isEmptyStr(string s);
bool isBlank(string s);
bool isNotBlank(string s);
string joinStrList(char* delimeter, StringList list);
String** increaseCapacity(StringList list);


#endif
