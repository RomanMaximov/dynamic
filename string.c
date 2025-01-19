//
// Created by Roman Maximov on 09.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string.h"
#include "arraylist.h"

// structures
typedef struct InnerStr {
    int count;
    char* data;
    int capacity;
} InnerStr;

// ArrayList data encapsulation
typedef struct InnerStrList {
    int count;
    String** data;
    int capacity;
} InnerStrList;

//typedef ArrayListStr* StrList;


// prototypes
static String** increaseCapacity(StrList list);
static int compareTo(string s1, string s2);

// funcs
string stringOf(char* s) {
    if (s == NULL) return NULL;

    string str = malloc(sizeof(String));
    str->pf->data = NULL;
    str->pf->count = 0;
    str->pf->capacity = 0;
    int length = 0;
    char* start = s;
    while(*start != '\0') {
        ++length;
        ++start;
    }
    if (length != 0) {
        str->pf->data = malloc((length + 1) * sizeof(char));
        strcpy(str->pf->data, s);
    } else {
        str->pf->data = NULL;
        return str;
    }

    str->pf->count = length;
    str->pf->capacity = length;
    return str;
}

string emptyStr() {
    string str = malloc(sizeof(String));
    str->pf->count = 0;
    str->pf->capacity = 0;
    str->pf->data = NULL;
    return str;
}

int length(string s) {
    return s->pf->count;
}

static int compareTo(string s1, string s2) {
    int result = strcmp(s1->pf->data, s2->pf->data);
    return result;
}

int binarySearch(char ch, const char* arr, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (ch < arr[middle])
            high = middle - 1;
        else if (ch > arr[middle])
            low = middle + 1;
        else
            return middle;
    }
    return -1;
}

String* toLowerCase(String* s) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return NULL;
    }

    int index;
    int count = s->pf->count;

    char temp[count];
    strcpy(temp, s->pf->data);

    strlwr(temp);

    if (strcmp(temp, s->pf->data) == 0)
        return s;

    free(s->pf->data);
    free(s);

    return stringOf(temp);
}

String* toUpperCase(String* s) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return NULL;
    }

    int index;
    int count = s->pf->count;
    char temp[count];

    strcpy(temp, s->pf->data);
    strupr(temp);

    if (strcmp(temp, s->pf->data) == 0)
        return s;

    free(s->pf->data);
    free(s);

    return stringOf(temp);
}

void printString(string s) {
    if (s == NULL || s->pf->data == NULL) {
        printf("Error: string is empty or null \n");
        return;
    }

    printf("%s\n", s->pf->data);
}

String* concat(String* s1, String* s2) {
    if (s1 == NULL || s1->pf->data == NULL) {
        printf("Error: first string is empty or null \n");
        return NULL;
    }
    if (s2 == NULL || s2->pf->data == NULL) {
        printf("Error: second string is empty or null \n");
        return NULL;
    }

    int count = s1->pf->count + s2->pf->count;
    char temp[count];
    strcpy(temp, s1->pf->data);
    strcat(temp, s2->pf->data);

    free(s1->pf->data);
    free(s2->pf->data);
    free(s1);
    free(s2);
    return stringOf(temp);
}

String* replace(String* s1, char ch1, char ch2) {
    if (s1 == NULL || s1->pf->data == NULL) {
        printf("Error: first string is empty or null \n");
        return NULL;
    }

    int count = s1->pf->count;
    char temp[count];
    strcpy(temp, s1->pf->data);

    for (int i = 0; i < count; ++i) {
        if (s1->pf->data[i] == ch1)
            temp[i] = ch2;
        else
            temp[i] = s1->pf->data[i];
    }
    free(s1->pf->data);
    free(s1);
    return stringOf(temp);
}

string join(char* delimeter, int countParams, ...) {
    va_list counter;
    va_start(counter, countParams);

    int count = 0;
    int number = 0;
    for (int i = 0; i < countParams; ++i) {
        String* tempStr = va_arg(counter, String*);
        if (i > 0)
            count += (int) strlen(delimeter);

        count += tempStr->pf->count;
        ++number;
    }
    va_end(counter);

    char temp[count + 1];

    va_list params;
    va_start(params, countParams);

    for (int i = 0; i < number; ++i) {
        String* tempStr = va_arg(params, String*);
        if (i == 0) {
            strcpy(temp, tempStr->pf->data);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, tempStr->pf->data);
    }
    temp[count] = '\0';
    va_end(params);

    String* s = stringOf(temp);
    return s;
}

void deleteString(string* s) {
    if (s != NULL || *s != NULL) {
        if ((*s)->pf->data != NULL) {
            free((*s)->pf->data);
        }
        free((*s)->pf);
    }
    free(*s);
    *s = NULL;
}

char charAt(String* s, int index) {
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

bool containsSubStr(String* str, String* substr) {
    if (str == NULL || substr == NULL)
        return false;

    char *substring = strstr(str->pf->data, substr->pf->data);

    if(substring)
        return true;
    else
        return false;
}

bool startsWith(string str, string substr) {
    if (str == NULL || substr == NULL || substr->pf->count > str->pf->count)
        return false;

    const char* text = str->pf->data;
    const char* sub = substr->pf->data;
    while(*sub != '\0') {
        if (*text != *sub)
            return false;

        ++text;
        ++sub;
    }
    return true;
}

bool endsWith(string str, string substr) {
    if (str == NULL || substr == NULL || substr->pf->count > str->pf->count)
        return false;

    const char* text = str->pf->data;
    const char* sub = substr->pf->data;
    while(*text != '\0')
        ++text;

    text -= substr->pf->count - 1;

    while(*sub != '\0') {
        if (*text != *sub)
            return false;

        ++text;
        ++sub;
    }
    return true;
}

string reverseStr(string s) {
    int count = s->pf->count;
    char temp[count + 1];

    strcpy(temp, s->pf->data);
    char* start = temp;
    char* end = temp;

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

    free(s->pf->data);
    free(s);

    return stringOf(temp);
}

int indexOfStr(string s, char ch) {
    if (s == NULL || s->pf->count == 0)
        return -1;

    const char* text = s->pf->data;

    int counter = 0;
    while(*text != '\0') {
        if (*text == ch)
            return counter;

        ++text;
        ++counter;
    }
    return -1;
}

int indexOfSubStr(string str, string sub) {
    if (str == NULL || sub == NULL || sub->pf->count > str->pf->count)
        return -1;

    char* text = str->pf->data;
    char* textCurrent = text;
    char* substr = sub->pf->data;
    char* subCurrent = substr;
    int counter = 0;

    while(*text != '\0') {
        ++counter;
        if (*text == *subCurrent) {
            int isEqual = sub->pf->count - 2;
            textCurrent = text;
            ++textCurrent;
            ++subCurrent;

            for (int i = 0; i < sub->pf->count - 1; ++i) {
                if (*textCurrent != *subCurrent)
                    break;
                --isEqual;
                ++textCurrent;
                ++subCurrent;
            }

            if (isEqual == 0) {
                return counter - 1;
            } else {
                ++text;
                subCurrent = substr;
            }
        } else {
            ++text;
        }
    }

    return -1;
}

StrList split(string s, char delimeter) {
    StrList list = newStrList(list);

    char* text = s->pf->data;
    char* current = text;

    int letterNumber = 0;
    int maxStringSize = 0;

    while(*current != '\0') {
        if (*current == delimeter) {

            if (letterNumber > maxStringSize) {
                maxStringSize = letterNumber;
            }
            letterNumber = 0;
        }

        if (letterNumber > maxStringSize) {
            maxStringSize = letterNumber + 1;
        }

        ++current;
        ++letterNumber;
    }

    if (letterNumber > maxStringSize) {
        maxStringSize = letterNumber;
    }

    int index = 0;
    int tempIndex = 0;

    char ch[maxStringSize];
    int dataSize;

    while(*text != '\0') {
        if (*text != delimeter) {
            ch[tempIndex] = *text;
            ++tempIndex;
        } else {
            if (list->pf->count == list->pf->capacity) {
                list->pf->data = increaseCapacity(list);
            }

            ch[tempIndex] = '\0';
            dataSize = strlen(ch);
            // данные строки
            list->pf->data[index] = malloc(sizeof(String));
            list->pf->data[index]->pf->data = malloc((dataSize + 1) * sizeof(char));
            list->pf->data[index]->pf->count = dataSize;
            list->pf->data[index]->pf->capacity = dataSize;

            strcpy(list->pf->data[index]->pf->data, ch);
            list->pf->count++;
            tempIndex = 0;
            ++index;
        }

        ++text;
    }

    if (list->pf->count == list->pf->capacity) {
        list->pf->data = increaseCapacity(list);
    }

    ch[tempIndex] = '\0';
    dataSize = strlen(ch);
    list->pf->data[index] = malloc(sizeof(String));
    list->pf->data[index]->pf->data = malloc((dataSize + 1) * sizeof(char));
    list->pf->data[index]->pf->count = dataSize;
    list->pf->data[index]->pf->capacity = dataSize;

    strcpy(list->pf->data[index]->pf->data, ch);
    list->pf->count++;

    return list;
}

string trim(string s) {
    char* temp = s->pf->data;
    // TODO
    return s;
}

string joinStrList(StrList list, char* delimeter) {
    int count = 0;
    int letterCounter = 0;

    for (int i = 0; i < list->pf->count; ++i) {
        char* tempStr = list->pf->data[i]->pf->data;
        if (i > 0)
            count += (int) strlen(delimeter);

        while (*tempStr++ != '\0') {
            ++letterCounter;
        }
        count += letterCounter;
        letterCounter = 0;
    }

    char* temp = malloc(++count * sizeof(char));

    for (int i = 0; i < list->pf->count; ++i) {
        if (i == 0) {
            strcpy(temp, list->pf->data[i]->pf->data);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, list->pf->data[i]->pf->data);
    }
    temp[count - 1] = '\0';

    string s = stringOf(temp);
    free(temp);
    return s;
}

bool isEmptyStr(string s) {
    return  s == NULL || s->pf->count == 0;
}

bool isBlank(string s) {
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

bool isNotBlank(string s) {
    if (s == NULL || s->pf->count == 0)
        return false;

    char* text = s->pf->data;
    while (*text != '\0') {
        if (*text != ' ')
            return true;

        ++text;
    }
    return false;
}

string defaultIfNull(string s1, string s2) {
    return s1 == NULL ? s2 : s1;
}

static String** increaseCapacity(StrList list) {
    list->pf->capacity *= 2;
    String** temp = list->pf->data;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    for (int i = 0; i < list->pf->capacity; ++i) {
        list->pf->data[i] = NULL;
    }
    for (int i = 0; i < list->pf->count; ++i) {
        memcpy(&list->pf->data[i], &temp[i], sizeof(String));
    }

    return list->pf->data;
}

