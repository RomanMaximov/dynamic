#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string.h"
#include "dynamicarray.h"


string stringOf(char* s) {
    string str = malloc(sizeof(String));
    int length = 0;
    char* start = s;
    while(*start != '\0') {
        ++length;
        ++start;
    }
    if (length != 0) {
        str->data = (char*)malloc((length + 1) * sizeof(char));
        strcpy(str->data, s);
    } else {
        str->data = NULL;
    }
    str->count = length;
    str->capacity = length;
    return str;
}

string emptyStr() {
    string str = malloc(sizeof(String));
    str->count = 0;
    str->capacity = 0;
    str->data = NULL;
    return str;
}

int length(string s) {
    return (int) s->count;
}

int compareTo(string s1, string s2) {
    return strcmp(s1->data, s2->data);
}

int binarySearch(char ch, const char* arr, int high)
{
    int low, middle;
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
    if (s == NULL || s->data == NULL) {
        printf("Error: string is empty or null \n");
        return NULL;
    }

    int index;
    unsigned int count = s->count;

    char temp[count];
    strcpy(temp, s->data);

    strlwr(temp);

    if (strcmp(temp, s->data) == 0)
        return s;

    free(s->data);
    free(s);

    return stringOf(temp);
}

String* toUpperCase(String* s) {
    if (s == NULL || s->data == NULL) {
        printf("Error: string is empty or null \n");
        return NULL;
    }

    int index;
    unsigned int count = s->count;
    char temp[count];

    strcpy(temp, s->data);
    strupr(temp);

    if (strcmp(temp, s->data) == 0)
        return s;

    free(s->data);
    free(s);

    return stringOf(temp);
}

void printString(string s) {
    if (s == NULL || s->data == NULL) {
        printf("Error: string is empty or null \n");
        return;
    }

    printf("%s\n", s->data);
}

String* concat(String* s1, String* s2) {
    if (s1 == NULL || s1->data == NULL) {
        printf("Error: first string is empty or null \n");
        return NULL;
    }
    if (s2 == NULL || s2->data == NULL) {
        printf("Error: second string is empty or null \n");
        return NULL;
    }

    unsigned int count = s1->count + s2->count;
    char temp[count];
    strcpy(temp, s1->data);
    strcat(temp, s2->data);

    free(s1->data);
    free(s2->data);
    free(s1);
    free(s2);
    return stringOf(temp);
}

String* replace(String* s1, char ch1, char ch2) {
    if (s1 == NULL || s1->data == NULL) {
        printf("Error: first string is empty or null \n");
        return NULL;
    }

    unsigned int count = s1->count;
    char temp[count];
    strcpy(temp, s1->data);

    for (int i = 0; i < count; ++i) {
        if (s1->data[i] == ch1)
            temp[i] = ch2;
        else
            temp[i] = s1->data[i];
    }
    free(s1->data);
    free(s1);
    return stringOf(temp);
}

string join(char* delimeter, int countParams, ...) {
    va_list counter;
    va_start(counter, countParams);

    unsigned int count = 0;
    int number = 0;
    for (int i = 0; i < countParams; ++i) {
        String* tempStr = va_arg(counter, String*);
        if (i > 0)
            count += strlen(delimeter);
        count += tempStr->count;
        ++number;
    }
    va_end(counter);

    char temp[count + 1];

    va_list params;
    va_start(params, countParams);

    for (int i = 0; i < number; ++i) {
        String* tempStr = va_arg(params, String*);
        if (i == 0) {
            strcpy(temp, tempStr->data);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, tempStr->data);
    }
    temp[count] = '\0';
    va_end(params);

    String* s = stringOf(temp);
    return s;
}

void deleteString(string s) {
    if (s != NULL) {
        if (s->data != NULL) {
            free(s->data);
        }
        free(s);
    }
}

char charAt(String* s, int index) {
    if (s == NULL || s->data == NULL) {
        printf("Error: string is empty or null \n");
        return '1';
    }

    int length = s->count - 1;
    if (index >= length) {
        puts("Out of bound exception.");
        return '1';
    }
    const char* str = s->data;
    char ch = *(str + index);
    return ch;
}

int containsSubStr(String* str, String* substr) {
    if (str == NULL || substr == NULL)
        return 0;

    char *substring = strstr(str->data, substr->data);

    if(substring)
        return 1;
    else
        return 0;
}

int startsWith(string str, string substr) {
    if (str == NULL || substr == NULL || substr->count > str->count)
        return 0;

    const char* text = str->data;
    const char* sub = substr->data;
    while(*sub != '\0') {
        if (*text != *sub)
            return 0;

        ++text;
        ++sub;
    }
    return 1;
}

int endsWith(string str, string substr) {
    if (str == NULL || substr == NULL || substr->count > str->count)
        return 0;

    const char* text = str->data;
    const char* sub = substr->data;
    while(*text != '\0')
        ++text;

    text -= substr->count - 1;

    while(*sub != '\0') {
        if (*text != *sub)
            return 0;

        ++text;
        ++sub;
    }
    return 1;
}

string reverseStr(string s) {
    int count = s->count;
    char temp[count + 1];

    strcpy(temp, s->data);
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

    free(s->data);
    free(s);

    return stringOf(temp);
}

long indexOf(string s, char ch) {
    if (s == NULL || s->count == 0)
        return -1;

    const char* text = s->data;

    long counter = 0;
    while(*text != '\0') {
        if (*text == ch)
            return counter;

        ++text;
        ++counter;
    }
    return -1;
}

long indexOfStr(string str, string sub) {
    if (str == NULL || sub == NULL || sub->count > str->count)
        return -1;

    char* text = str->data;
    char* textCurrent = text;
    char* substr = sub->data;
    char* subCurrent = substr;
    long counter = 0;

    while(*text != '\0') {
        ++counter;
        if (*text == *subCurrent) {
            int isEqual = sub->count - 2;
            textCurrent = text;
            ++textCurrent;
            ++subCurrent;

            for (int i = 0; i < sub->count - 1; ++i) {
                if (*textCurrent != *subCurrent)
                    break;
                --isEqual;
                ++textCurrent;
                ++subCurrent;
            }

            if (isEqual == 0)
                return counter - 1;
            else
                ++text;
                subCurrent = substr;
        } else {
            ++text;
        }
    }

    return -1;
}

StringList split(string s, char delimeter) {
    StringList list = newList(list);

    char* text = s->data;
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
    unsigned long long int dataSize;

    while(*text != '\0') {
        if (*text != delimeter) {
            ch[tempIndex] = *text;
            ++tempIndex;
        } else {
            if (list->count == list->capacity) {
                list->str = increaseCapacity(list);
            }

            ch[tempIndex] = '\0';
            dataSize = strlen(ch);
            // данные строки
            list->str[index] = malloc(sizeof(String));
            list->str[index]->data = malloc((dataSize + 1) * sizeof(char));
            list->str[index]->count = dataSize;
            list->str[index]->capacity = dataSize;

            strcpy(list->str[index]->data, ch);
            list->count++;
            tempIndex = 0;
            ++index;
        }

        ++text;
    }

    if (list->count == list->capacity) {
        list->str = increaseCapacity(list);
    }

    ch[tempIndex] = '\0';
    dataSize = strlen(ch);
    list->str[index] = malloc(sizeof(String));
    list->str[index]->data = malloc((dataSize + 1) * sizeof(char));
    list->str[index]->count = dataSize;
    list->str[index]->capacity = dataSize;

    strcpy(list->str[index]->data, ch);
    list->count++;

    return list;
}

String** increaseCapacity(StringList list) {
    list->capacity *= 2;
    String** temp = list->str;
    list->str = malloc(list->capacity * sizeof(String*));
    for (int i = 0; i < list->capacity; ++i) {
        list->str[i] = NULL;
    }
    for (int i = 0; i < list->count; ++i) {
        memcpy(&list->str[i], &temp[i], sizeof(String));
    }

    return list->str;
}

string joinStrList(char* delimeter, StringList list) {
    unsigned int count = 0;
    unsigned int letterCounter = 0;

    for (int i = 0; i < list->count; ++i) {
        char* tempStr = list->str[i]->data;
        if (i > 0)
            count += strlen(delimeter);

        while (*tempStr++ != '\0') {
            ++letterCounter;
        }
        count += letterCounter;
        letterCounter = 0;
    }

    char* temp = malloc(++count * sizeof(char));

    for (int i = 0; i < list->count; ++i) {
        if (i == 0) {
            strcpy(temp, list->str[i]->data);
            continue;
        }
        if (i > 0) {
            strcat(temp, delimeter);
        }
        strcat(temp, list->str[i]->data);
    }
    temp[count - 1] = '\0';

    string s = stringOf(temp);
    free(temp);
    return s;
}

int isEmptyStr(string s) {
    if (s == NULL || length(s) == 0)
        return 1;
    else
        return 0;
}

int isBlank(string s) {
    if (s == NULL || length(s) == 0)
        return 0;

    char* text = s->data;
    while (*text != '\0') {
        if (*text != ' ')
            return 0;

        ++text;
    }
    return 1;
}

