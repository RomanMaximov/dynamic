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
static int compareStr(string s1, string s2);
static void copyList(StrList dest, StrList from);
static void quickSort(String** strList, int low, int high);
static void quickSortReverse(String** strList, int low, int high);
static bool isFull(StrList list);
static bool binarySearchStr(string s, String** strList, int high);
static int compareInt(const void* elem1, const void* elem2);
static bool binarySearch(int elem, const int* arr, int high);
static void checkCapacity(char* text, int* count, int strLength);
static bool hasNext(Iterator iter);



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

        if (compareStr(list->inner->data[i], str) == 0)
            return i;
    }
    return -1;
}

void sortStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = list->inner->count;
    quickSort(list->inner->data, 0, high);
}

void sortStrListReverse(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = sizeStrList(list);
    quickSortReverse(list->inner->data, 0, high);
}

void clearStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    free(list->inner->data);
    list->inner->count = 0;
    list->inner->capacity = 20;
    list->inner->data = malloc(list->inner->capacity * sizeof(String*));
}

bool containsStrList(StrList list, string str) {
    if (list == NULL || isEmptyStr(str))
        return false;

    for (int i = 0; i < list->inner->count; ++i) {
        if (compareStr(list->inner->data[i], str) == 0)
            return true;
    }
    return false;
}

bool containsAllStrList(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count)
        return false;

    StrList temp = newStrList(temp);
    copyList(temp, list1);
    sortStrList(temp);

    for (int i = 0; i < list2->inner->count; ++i) {
        if (!binarySearchStr(list2->inner->data[i], temp->inner->data, temp->inner->count))
            return false;
    }

    deleteStrList(&temp);
    return true;
}

bool containsAnyStrList(StrList list1, StrList list2) {
    if (isEmptyStrList(list1) || isEmptyStrList(list2))
        return false;

    StrList temp = newStrList(temp);
    copyList(temp, list1);
    sortStrList(temp);

    for (int i = 0; i < list2->inner->count; ++i) {
        if (binarySearchStr(list2->inner->data[i], temp->inner->data, temp->inner->count))
            return true;
    }

    deleteStrList(&temp);

    return false;
}

bool removeStrList(StrList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    if (list->inner->count == 1 && index == 0) {
        deleteString(&list->inner->data[index]);
        list->inner->count = 0;
        list->inner->data[index] = NULL;
        return true;
    }

    int sizeTemp = list->inner->count - index - 1;
    String** temp = malloc(sizeTemp * sizeof(String*));
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->inner->data[counter++];
    }

    memcpy(&list->inner->data[index], temp, sizeTemp * sizeof(String));
    list->inner->count--;

    for (int i = 0; i < sizeTemp; ++i) {
        deleteString(&temp[i]);
    }

    free(temp);

    return true;
}

bool removeAllStrList(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    StrList temp = newStrList(temp);//malloc(list1->count * sizeof(string));
    copyList(temp, list1);

    int* indexList = malloc(list2->inner->count * sizeof(int));

    int j = 0;
    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfStrList(list1, list2->inner->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    for (int i = 0; i < list1->inner->count; ++i) {
        deleteString(&list1->inner->data[i]);
    }

    free(list1->inner->data);
    list1->inner->data = malloc(list1->inner->capacity * sizeof(string));
    for (int i = 0; i < list1->inner->capacity; ++i) {
        list1->inner->data[i] = NULL;
    }

    int index = 0;
    for (int i = 0; i < list1->inner->count; ++i) {
        if (binarySearch(i, indexList, j)) // 1
            continue;

        list1->inner->data[index] = temp->inner->data[i];
        ++index;
    }

    list1->inner->count -= j;

    free(indexList);
    deleteStrList(&temp);

    return true;
}

StrList subtractStrList(StrList list1, StrList list2) {
    if (isEmptyStrList(list1)) {
        StrList temp = NULL;
        return newStrList(temp);
    }

    if (isEmptyStrList(list2)) {
        StrList temp = newStrList(temp);
        copyList(temp, list1);
        return temp;
    }

    StrList copyValues = newStrList(copyValues);
    copyList(copyValues, list1);

    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfStrList(copyValues, list2->inner->data[i]);
        if (index != -1) {
            deleteString(&copyValues->inner->data[index]);
        }
    }

    StrList temp = newStrList(temp);
    int index = 0;
    for (int i = 0; i < copyValues->inner->count; ++i) {
        if (copyValues->inner->data[i] != NULL) {
            if (isFull(temp)) {
                temp->inner->data = increaseCapacity(temp);
            }

            temp->inner->data[index++] = stringOf(copyValues->inner->data[i]->data);
            temp->inner->count++;
        }
    }

    deleteStrList(&copyValues);
    return temp;
}

bool isEmptyStrList(StrList list) {
    return list == NULL || list->inner->count == 0;
}

void reverseStrList(StrList list) {
    String** start = list->inner->data;
    String** end = list->inner->data + (list->inner->count - 1);
    String* temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualsStrList(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL || list1->inner->count != list2->inner->count)
        return false;

    int counter = list1->inner->count;
    for (int i = 0; i < counter; ++i) {
        char* temp1 = list1->inner->data[i]->data;
        char* temp2 = list2->inner->data[i]->data;

        if (strcmp(temp1, temp2) != 0)
            return false;
    }

    return true;
}

StrList emptyIfNullStrList(StrList list) {
    return list == NULL ? newStrList(list) : list;
}

int sizeStrList(StrList list) {
    return list->inner->count;
}

string toStringStrList(StrList list) {
    char* text = NULL;
    if (list->inner->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return stringOf(text);
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");

    for (int i = 0; i < list->inner->count - 1; ++i) {
        checkCapacity(text, &count, list->inner->data[i]->count);
        sprintf(&text[strlen(text)], "%s,", list->inner->data[i]->data);
    }

    checkCapacity(text, &count, list->inner->data[list->inner->count - 1]->count);
    sprintf(&text[strlen(text)], "%s", list->inner->data[list->inner->count - 1]->data);
    strcat(text, "]");

    string s = stringOf(text);
    free(text);

    return s;
}

void printStrList(StrList list) {
    if (list == NULL) return;

    int counter = list->inner->count;
    printf("%s", "[");
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1) {
            if (list->inner->data[i] == NULL || list->inner->data[i]->data == NULL)
                printf("%s", "null");
            else
                printf("%s", list->inner->data[i]->data);
        } else {
            if (list->inner->data[i] == NULL || list->inner->data[i]->data == NULL)
                printf("%s, ", "null");
            else
                printf("%s, ", list->inner->data[i]->data);
        }
    }
    printf("%s\n", "]");
}

void deleteStrList(StrList* list) {
    if (list == NULL || *list == NULL) {
        printf("%s\n", "List is NULL.");
        return;
    }

    if ((*list)->inner->data != NULL) {
        for (int i = 0; i < (*list)->inner->count; ++i) {
            if ((*list)->inner->data[i] != NULL) {
                deleteString(&(*list)->inner->data[i]);
            }
        }
        free((*list)->inner->data);
    }

    free((*list)->inner);
    free(*list);
    *list = NULL;
}

Iterator iteratorStrList(StrList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->inner->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = STR_LIST;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
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

    for (int i = 0; i < oldSize; ++i) {
        deleteString(&temp[i]);
    }

    free(temp);

    return list->inner->data;
}

static int compareStr(string s1, string s2) {
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
            if (compareStr(strList[i], strList[j]) == 1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) == 1) {
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
            if (compareStr(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) == -1) {
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

static bool binarySearchStr(string s, String** strList, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (compareStr(s, strList[middle]) < 0)
            high = middle - 1;
        else if (compareStr(s, strList[middle]) > 0)
            low = middle + 1;
        else
            return true;
    }
    return false;
}

static int compareInt(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

static bool binarySearch(int elem, const int* arr, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (elem < arr[middle])
            high = middle - 1;
        else if (elem > arr[middle])
            low = middle + 1;
        else
            return true;
    }
    return false;
}

static void checkCapacity(char* text, int* count, int strLength) {
    if (strLength >= *count - strlen(text)) {
        *count = (*count + strLength) * 2;
        realloc(text, *count * sizeof(char));
    }
}