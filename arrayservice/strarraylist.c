//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strarraylist.h"


typedef struct String {
    int count;
    char* data;
    int capacity;
} String;

typedef struct InnerStrList {
    int count;
    String** data;
    int capacity;
} InnerStrList;

typedef String* string;


// private funcs prototypes
static String** increaseCapacity(StrList list);
static int compare(string s1, string s2);
static void copyList(StrList dest, StrList from);
static void quickSort(String** strList, int low, int high);
static void quickSortReverse(String** strList, int low, int high);
static bool isFull(StrList list);



void addStrList(StrList list, string str) {
    if (list == NULL) return;

    if (str == NULL) {
        if (isFull(list))
            list->inner->data = increaseCapacity(list);

        list->inner->data[list->inner->count] = NULL;
        list->inner->count++;
    } else {
        string temp = stringOf(str->data);
        if (isFull(list)) {
            list->inner->data = increaseCapacity(list);
            memcpy(&list->inner->data[list->inner->count], &temp, sizeof(String));
            list->inner->count++;
        } else {
            memcpy(&list->inner->data[list->inner->count], &temp, sizeof(String));
            list->inner->count++;
        }
    }
}

void addCharArrList(StrList list, char* str) {
    if (str == NULL || list == NULL) return;

    string elem = stringOf(str);

    if (isFull(list)) {
        list->inner->data = increaseCapacity(list);
        memcpy(&list->inner->data[list->inner->count], &elem, sizeof(String));
        list->inner->count++;
    } else {
        memcpy(&list->inner->data[list->inner->count], &elem, sizeof(String));
        list->inner->count++;
    }
}

void addAllStrList(StrList dest, StrList from) {
    if (dest == NULL || from == NULL || from->inner->data == NULL) return;

    int sizeFrom = sizeStrList(from);
    int sizeDest = sizeStrList(dest);
    if ((sizeDest + sizeFrom) > dest->inner->capacity) {
        int newCapacity = (sizeDest + sizeFrom) * 2;
        dest->inner->capacity = newCapacity;
        dest->inner->data = realloc(dest->inner->data, newCapacity * sizeof(String*));
        for (int i = 0; i < dest->inner->capacity; ++i)
            dest->inner->data[i] = NULL;

        for (int i = sizeFrom; i < sizeFrom + sizeDest; ++i) {
            dest->inner->data[i] = stringOf(from->inner->data[i]->data);
        }
        dest->inner->count += sizeFrom;
    } else {
        int indexFrom = 0;
        for (int i = sizeDest; i < sizeFrom + sizeDest; ++i) {
            dest->inner->data[i] = stringOf(from->inner->data[indexFrom++]->data);
        }
        dest->inner->count += sizeFrom;
    }
}

string getStrList(StrList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return NULL;
    }

    if (index < 0 || index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return NULL;
    }

    return stringOf(list->inner->data[index]->data);
}

bool setStrList(StrList list, int index, string str) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    list->inner->data[index] = stringOf(str->data);
    return true;
}

bool setCharArrList(StrList list, int index, char* str) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    list->inner->data[index] = stringOf(str);
    return true;
}

int indexOfStrList(StrList list, string str) {
    if (list == NULL || str == NULL)
        return -1;

    for (int i = 0; i < list->inner->count; ++i) {
        if (list->inner->data[i] == NULL)
            continue;

        if (compare(list->inner->data[i], str) == 0)
            return i;
    }
    return -1;
}

void sortStrList(StrList list) {
    if (list == NULL || list->inner->data == NULL)
        return;

    int high = list->inner->count;
    quickSort(list->inner->data, 0, high);
}



bool removeElemStr(StrList list, int index) {
    if (list == NULL) return false;

    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return false;
    }

    if (list->count == 1) {
        free(list->str[0]);
        list->count = 0;
        return true;
    }

    String** temp = malloc((list->count - index - 1) * sizeof(String*));
    unsigned int sizeTemp = list->count - index - 1;
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->str[counter++];
    }
    memcpy(&list->str[index], temp, sizeTemp * sizeof(String));
    list->count--;
    free(temp);

    return true;
}

bool removeAllStr(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    String** temp = malloc(list1->count * sizeof(string));
    int* indexList = malloc(list2->count * sizeof(int));
    memcpy(&temp[0], list1->str, list1->count * sizeof(string));

    int j = 0;
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfStrList(list1, list2->str[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    free(list1->str);
    list1->str = malloc(list1->capacity * sizeof(string));

    int index = 0;
    for (int i = 0; i < list1->count; ++i) {
        if (binarySearchInt(i, indexList, j)) // 1
            continue;

        list1->str[index] = temp[i];
        ++index;
    }
    list1->count -= j;
    if (list1->count == 0) list1->str = NULL;
    free(indexList);
    free(temp);

    return true;
}

void printArrayString(StrList list) {
    if (list == NULL) return;

    int counter = list->count;
    printf("%s", "[");
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1) {
            if (list->str[i] == NULL || list->str[i]->data == NULL)
                printf("%s", "null");
            else
                printf("%s", list->str[i]->data);
        } else {
            if (list->str[i] == NULL || list->str[i]->data == NULL)
                printf("%s, ", "null");
            else
                printf("%s, ", list->str[i]->data);
        }
    }
    printf("%s\n", "]");
}

void clearStrList(StrList list) {
    if (list == NULL) return;

    free(list->str);
    list->count = 0;
    list->capacity = 20;
    list->str = malloc(list->capacity * sizeof(String*));
}

// TODO доработать удаление, чтобы внешний указатель был NULL
void deleteStrList(StrList list) {
    if (list == NULL) {
        printf("%s\n", "List is NULL.");
        return;
    }

    if (list->str != NULL) {
        for (int i = 0; i < list->count; ++i) {
            if (list->str[i] != NULL) {
                deleteString(&(list->str[i]));
            }
        }
        free(list->str);
    }
    free(list);
}





void sortReverseStrList(StrList list) {
    if (list == NULL)
        return;

    int high = sizeStrList(list);
    quickSortReverseStr(list->str, 0, high);
}

bool containsStr(StrList list, string str) {
    if (list == NULL)
        return false;

    for (int i = 0; i < list->count; ++i) {
        if (compareTo(list->str[i], str) == 0)
            return true;
    }
    return false;
}

bool containsAllStr(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL || list2->count > list1->count)
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (indexOfStrList(list1, list2->str[i]) == -1)
            return false;
    }

    return true;
}

bool isEmptyStrList(StrList list) {
    return list == NULL || list->count == 0;
}

int sizeStrList(StrList list) {
    return list->count;
}

void reverseListStr(StrList list) {
    String** start = list->str;
    String** end = list->str + (list->count - 1);
    String* temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualStrLists(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->count != list2->count)
        return false;

    int counter = list1->count;
    for (int i = 0; i < counter; ++i) {
        char* temp1 = list1->str[i]->data;
        char* temp2 = list2->str[i]->data;

        if (strcmp(temp1, temp2) != 0)
            return false;
    }
    return true;
}



StrList emptyIfNullStr(StrList list) {
    return list == NULL ? newStrArray(list) : list;
}

bool containsAnyStr(StrList list1, StrList list2) {
    if (isEmptyStrList(list1) || isEmptyStrList(list2))
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (containsStr(list1, list2->str[i]))
            return true;
    }

    return false;
}

StrList subtractStr(StrList list1, StrList list2) {
    if (isEmptyStrList(list1)) {
        StrList temp = NULL;
        return newStrArray(temp);
    }

    if (isEmptyStrList(list2)) {
        StrList temp = copyStrList(temp, list1);
        return temp;
    }

    StrList copyList = copyStrList(copyList, list1);
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfStrList(copyList, list2->str[i]);
        if (index != -1)
            copyList->str[index] = NULL;
    }

    StrList temp = newStrArray(temp);
    int index = 0;
    for (int i = 0; i < copyList->count; ++i) {
        if (copyList->str[i] != NULL) {
            if (temp->count == temp->capacity) {
                temp->str = increaseCapacity(temp);
            }
            temp->str[index++] = stringOf(copyList->str[i]->data);
            temp->count++;
        }
    }
    deleteStrList(copyList);
    return temp;
}

// ===================== private funcs =======================

static String** increaseCapacity(StrList list) {
    int oldSize = list->inner->count;
    list->inner->capacity *= 2;

    String** temp = list->inner->data;
    list->inner->data = malloc(list->inner->capacity * sizeof(String*));
    assert(list->inner->data != NULL);

    for (int i = 0; i < list->inner->capacity; ++i)
        list->inner->data[i] = NULL;

    for (int i = 0; i < list->inner->count; ++i) {
        memcpy(&list->inner->data[i], &temp[i], sizeof(String));
    }

    return list->inner->data;
}

static int compare(string s1, string s2) {
    int result = strcmp(s1->data, s2->data);
    return result;
}

static void copyList(StrList dest, StrList from) {
    for (int i = 0; i < from->inner->count; ++i) {
        if (isFull(dest)) {
            dest->inner->data = increaseCapacity(dest);
        }

        dest->inner->data[i] = stringOf(from->inner->data[i]->data);
        dest->inner->count++;
    }
}

static void quickSort(String** strList, int low, int high)
{
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compare(strList[i], strList[j]) == 1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compare(strList[i], strList[j]) == 1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quickSort(strList, i + 1, high);
    if (low < j - 1)
        quickSort(strList, low, j);
}

static void quickSortReverse(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compare(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compare(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quickSortReverse(strList, i + 1, high);
    if (low < j - 1)
        quickSortReverse(strList, low, j);
}

static bool isFull(StrList list) {
    return list->inner->count > list->inner->capacity / 5 * 4;
}
