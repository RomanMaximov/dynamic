#ifndef STRING_H
#define STRING_H

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
/////
char charAt(string s, int index);
int containsStr(string str, string substr);
int startsWith(string str, string substr);
int endsWith(string str, string substr);
string reverseStr(string s);
long indexOf(string s, char ch);
long indexOfStr(string str, string sub);
StringArray* split(string s, char delimeter);
string trim(string s);
int isEmptyStr(string s);
int isBlank(string s);
string joinStrList(char* delimeter, StringList list);
String** increaseCapacity(StringList list);


#endif
