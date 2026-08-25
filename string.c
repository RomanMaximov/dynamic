//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "string.h"
#include "arraylist.h"
#include "arrayservice/strarraylist.h"

// structures
typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;

// ArrayList data encapsulation
typedef struct InnerStrList {
    int count;
    struct String** data;
    int capacity;
} InnerStrList;


// prototypes private funcs
static int countStrEmbbeded(string s, char* sub);
static int indexOfSub(char* source, char* sub, int offset);
static void copyInArr(char* dest, int destIndex, char* source, int tempIndex, int size);


// private prototypes funcs for pointers initialization
static void initFuncs(string str);


// funcs
string strOf(char* s) {
    if (s == NULL) return NULL;

    int length = (int) strlen(s);
    if (length == 0)
        return emptyStr();

    string str = malloc(sizeof(String));
    str->pf = malloc(sizeof(InnerStr));
    str->pf->data = malloc((length + 1) * sizeof(char));
    strcpy(str->pf->data, s);

    str->pf->count = length;
    str->pf->capacity = length;
    initFuncs(str);

    return str;
}

string emptyStr() {
    string str = malloc(sizeof(String));
    str->pf = malloc(sizeof(InnerStr));
    str->pf->count = 0;
    str->pf->capacity = 2;
    str->pf->data = malloc(2 * sizeof(char));

    strcpy(str->pf->data, "");
    initFuncs(str);

    return str;
}

int lengthStr(string s) {
    return s->pf->count;
}

void concatStr(string s1, string s2) {
    if (s1 == NULL || s2 == NULL || s2->pf->data == NULL) {
        return;
    }

    int count = s1->pf->count + s2->pf->count + 1;
    s1->pf->data = realloc(s1->pf->data, count * sizeof(char));
    assert(s1->pf->data != NULL);

    strcat(s1->pf->data, s2->pf->data);
    s1->pf->count += s2->pf->count;
    s1->pf->capacity = count;
}

void replaceStr(string s, char* ch1, char* ch2) {
    if (s == NULL || s->pf->data == NULL || ch1 == NULL || ch2 == NULL) {
        printf("Error: string is empty or null \n");
        return;
    }

    int lenS1 = (int) strlen(ch1);
    int lenS2 = (int) strlen(ch2);

    if (lenS1 == 1 && lenS2 == 1) {
        for (int i = 0; i < s->pf->count; ++i) {
            if (s->pf->data[i] == ch1[0])
                s->pf->data[i] = ch2[0];
        }
        return;
    }

    int counterEmbbeded = countStrEmbbeded(s, ch1);
    if (counterEmbbeded == 0) return;

    int newSize = s->pf->count - (lenS1 * counterEmbbeded) + (lenS2 * counterEmbbeded);
    char temp[s->pf->count + 1];
    strcpy(temp, s->pf->data);

    free(s->pf->data);
    s->pf->data = malloc((newSize + 1) * sizeof(char));
    assert(s->pf->data != NULL);

    s->pf->count = newSize;
    s->pf->capacity = newSize + 1;

    int lenTemp = (int) strlen(temp);
    int tempIndex = 0;
    int destIndex = 0;
    int currentIndex = 0;
    int counter = 0;
    while(counter < lenTemp) {
        currentIndex = indexOfSub(temp, ch1, tempIndex);
        if (currentIndex != 0 && currentIndex != -1) {
            int size = currentIndex - tempIndex;
            copyInArr(s->pf->data, destIndex, temp, tempIndex, size);
            tempIndex = currentIndex;
            destIndex += size;
        }

        if (currentIndex != -1) {
            copyInArr(s->pf->data, destIndex, ch2, 0, lenS2);
            destIndex += lenS2;
            tempIndex += lenS1;
        }

        if (currentIndex == -1 && (lenTemp-tempIndex != 0)) {
            copyInArr(s->pf->data, destIndex, temp, tempIndex, lenTemp-tempIndex);
            tempIndex += lenTemp-tempIndex;
        }

        counter = tempIndex;
    }
    s->pf->data[newSize] = '\0';
}

void toLowerCaseStr(String* s) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return;
    }

    for (char *p = s->pf->data; *p; ++p)
        *p = (char)tolower((unsigned char)*p);
}

void toUpperCaseStr(String* s) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return;
    }

    for (char *p = s->pf->data; *p; ++p)
        *p = (char)toupper((unsigned char)*p);
}

string join(char* delimeter, int countParams, ...) {
    va_list counter;
    va_start(counter, countParams);

    int count = 0;
    int number = 0;
    for (int i = 0; i < countParams; ++i) {
        char* tempStr = va_arg(counter, char*);
        if (i > 0)
            count += (int) strlen(delimeter);

        count += (int) strlen(tempStr);
        ++number;
    }
    va_end(counter);

    char temp[count + 1];

    va_list params;
    va_start(params, countParams);

    for (int i = 0; i < number; ++i) {
        char* tempStr = va_arg(params, char*);
        if (i == 0) {
            strcpy(temp, tempStr);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, tempStr);
    }
    temp[count] = '\0';
    va_end(params);

    return strOf(temp);
}

string joinFromList(StrList list, char* delimeter) {
    int count = 0;
    int number = 0;
    for (int i = 0; i < list->pf->count; ++i) {
        if (i > 0)
            count += (int) strlen(delimeter);

        count += list->pf->data[i]->pf->count;
        ++number;
    }

    char temp[count + 1];
    for (int i = 0; i < number; ++i) {
        if (i == 0) {
            strcpy(temp, list->pf->data[i]->pf->data);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, list->pf->data[i]->pf->data);
    }
    temp[count] = '\0';

    return strOf(temp);
}

char charAtStr(String* s, int index) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return '1';
    }

    int length = s->pf->count - 1;
    if (index < 0 || index >= length) {
        puts("Error: Index value out of bound.");
        return '1';
    }

    const char* str = s->pf->data;
    char ch = *(str + index);
    return ch;
}

bool containsSubString(String* str, String* substr) {
    if (str == NULL || substr == NULL)
        return false;

    char *substring = strstr(str->pf->data, substr->pf->data);

    if(substring)
        return true;
    else
        return false;
}

bool startsWithStr(string str, char* substr) {
    if (str == NULL || substr == NULL || strlen(substr) > str->pf->count)
        return false;

    const char* text = str->pf->data;
    const char* sub = substr;
    while(*sub != '\0') {
        if (*text != *sub)
            return false;

        ++text;
        ++sub;
    }
    return true;
}

bool endsWithStr(string str, char* substr) {
    if (str == NULL || substr == NULL || strlen(substr) > str->pf->count)
        return false;

    const char* text = str->pf->data;
    const char* sub = substr;
    while(*text != '\0')
        ++text;

    text -= strlen(substr);

    while(*sub != '\0') {
        if (*text != *sub)
            return false;

        ++text;
        ++sub;
    }
    return true;
}

void reverseStr(string s) {
    char* start = s->pf->data;
    char* end = s->pf->data;

    while(*end != '\0')
        ++end;

    --end;
    char ch;
    while(start < end) {
        ch = *start;
        *start = *end;
        *end = ch;
        ++start;
        --end;
    }
}

int indexOfStr(string s, char ch) {
    if (s == NULL || s->pf->count == 0)
        return -1;

    const char* text = s->pf->data;

    int index = 0;
    while(*text != '\0') {
        if (*text == ch)
            return index;

        ++text;
        ++index;
    }
    return -1;
}

int indexOfSubString(string str, string sub) {
    if (str == NULL || sub == NULL || sub->pf->count > str->pf->count)
        return -1;

    char* text = str->pf->data;
    char* textCurrent = str->pf->data;
    char* subStr = sub->pf->data;
    char* currentSubStr = sub->pf->data;
    int subLength = (int) strlen(sub->pf->data);
    int index = 0;
    int foundIndex = -1;
    int counter = subLength;

    while(*text != '\0') {
        if (*textCurrent == *currentSubStr) {
            if (counter == subLength)
                foundIndex = index;

            --counter;
            ++textCurrent;
            ++currentSubStr;
            ++text;
        } else {
            ++text;
            textCurrent = text;
            currentSubStr = subStr;
            counter = subLength;
            foundIndex = -1;
        }


        if (counter == 0) {
            return foundIndex;
        }

        ++index;
    }

    return foundIndex;
}

StrList splitStr(string s, const char* delimeter) {
    if (s == NULL || delimeter == NULL) {
        StrList strList = pr_initLs_(strList, NULL);
        return strList;
    }

    StrList list = pr_initLs_(list, NULL);

    char* text = s->pf->data;
    char temp[s->pf->count];
    int counter = 0;
    bool lastStr = false;

    while(*text != '\0') {
        if (*text != *delimeter) {
            temp[counter] = *text;
            ++counter;
        } else {
            temp[counter] = '\0';
            addCharArrList(list, temp);
            counter = 0;
        }

        ++text;

        if (*text == '\0')
            lastStr = true;

        if (lastStr) {
            temp[counter] = '\0';
            addCharArrList(list, temp);
        }
    }

    return list;
}

void trimStr(string s) {
    if (s == NULL) {
        return;
    }

    const char* start = s->pf->data;
    while (*start && isspace((unsigned char)*start)) {
        ++start;
    }

    const char* end = s->pf->data + strlen(s->pf->data) - 1;
    while (*end && isspace((unsigned char)*end)) {
        --end;
    }

    int length = (int) (end - start + 1);

    strncpy(s->pf->data, start, length);
    s->pf->data[length] = '\0';
    s->pf->count = length;
    s->pf->capacity = length + 1;
}

bool isEmptyStr(string s) {
    return  s == NULL || s->pf->count == 0;
}

bool isBlankStr(string s) {
    if (s == NULL || s->pf->count == 0)
        return false;

    char* text = s->pf->data;
    while (*text != '\0') {
        if (*text != ' ')
            return false;

        ++text;
    }
    return true;
}

string defaultIfNull(string s1, char* s2) {
    return s1 == NULL ? strOf(s2) : s1;
}

byte* getBytesStr(string s) {
    byte* bytes = malloc(s->pf->count * sizeof(char));
    for (int i = 0; i < s->pf->count; ++i) {
        bytes[i] = s->pf->data[i];
    }
    return bytes;
}

void printStr(string s) {
    if (s == NULL)
        return;

    if (s->pf->count == 0) {
        printf("%s\n", "[]");
        return;
    }

    printf("%s", "[");
    if (s->pf->data == NULL) {
        puts("null");
    } else {
        printf("%s", s->pf->data);
    }
    printf("%s\n", "]");
}

void deleteStr(string* s) {
    if (s == NULL || *s == NULL) return;

    if ((*s)->pf->data != NULL) {
        free((*s)->pf->data);
    }
    free((*s)->pf);
    free(*s);
    *s = NULL;
}

char* toCharArr(string s) {
    return strdup(s->pf->data);
}

// =================  private funcs  ===================

static int countStrEmbbeded(string s, char* sub) {
    int embbeded = 0;
    char* text = s->pf->data;
    char* textCurrent = s->pf->data;
    char* subStr = sub;
    char* currentSubStr = sub;
    int subLength = (int) strlen(sub);
    int counter = 0;

    while(*text != '\0') {
        if (*textCurrent == *currentSubStr) {
            ++counter;
            if (counter == subLength) {
                ++embbeded;
                counter = 0;
                ++textCurrent;
                currentSubStr = subStr;
                ++text;
            } else {
                ++textCurrent;
                ++currentSubStr;
                ++text;
            }
        } else {
            ++text;
            textCurrent = text;
            currentSubStr = subStr;
            counter = 0;
        }
    }

    return embbeded;
}

static int indexOfSub(char* source, char* sub, int offset) {
    char* text = source + offset;
    char* textCurrent = source + offset;
    char* subStr = sub;
    char* currentSubStr = sub;
    int subLength = (int) strlen(sub);
    int index = offset;
    int foundIndex = -1;
    int counter = subLength;

    while(*text != '\0') {
        if (*textCurrent == *currentSubStr) {
            if (counter == subLength)
                foundIndex = index;

            --counter;
            ++textCurrent;
            ++currentSubStr;
            ++text;
        } else {
            ++text;
            textCurrent = text;
            currentSubStr = subStr;
            counter = subLength;
            foundIndex = -1;
        }

        if (counter == 0) {
            return foundIndex;
        }

        ++index;
    }

    return foundIndex;
}

static void copyInArr(char* dest, int destIndex, char* source, int tempIndex, int size) {
    while (size != 0) {
        dest[destIndex++] = source[tempIndex++];
        --size;
    }
}

// funcs pointers initialization
static void initFuncs(string str) {
    str->length = lengthStr;
    str->concat = concatStr;
    str->replace = replaceStr;
    str->toLowerCase = toLowerCaseStr;
    str->toUpperCase = toUpperCaseStr;
    str->charAt = charAtStr;
    str->containsSubStr = containsSubString;
    str->startsWith = startsWithStr;
    str->endsWith = endsWithStr;
    str->reverse = reverseStr;
    str->indexOf = indexOfStr;
    str->indexOfSubStr = indexOfSubString;
    str->split = splitStr;
    str->trim = trimStr;
    str->isEmpty = isEmptyStr;
    str->isBlank = isBlankStr;
    str->getBytes = getBytesStr;
    str->print = printStr;
    str->delete = deleteStr;
}