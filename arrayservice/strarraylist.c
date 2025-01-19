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


/*typedef struct String {
    int count;
    char* data;
    int capacity;
} String;*/

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
            list->pf->data = increaseCapacity(list);

        list->pf->data[list->pf->count] = NULL;
        list->pf->count++;
    } else {
        string temp = stringOf(str->data);
        if (isFull(list)) {
            list->pf->data = increaseCapacity(list);
            memcpy(&list->pf->data[list->pf->count], &temp, sizeof(String));
            list->pf->count++;
        } else {
            memcpy(&list->pf->data[list->pf->count], &temp, sizeof(String));
            list->pf->count++;
        }
    }
}

void addCharArrList(StrList list, char* str) {
    if (str == NULL || list == NULL) return;

    string elem = stringOf(str);

    if (isFull(list)) {
        list->pf->data = increaseCapacity(list);
        memcpy(&list->pf->data[list->pf->count], &elem, sizeof(String));
        list->pf->count++;
    } else {
        memcpy(&list->pf->data[list->pf->count], &elem, sizeof(String));
        list->pf->count++;
    }
}

void addAllStrList(StrList dest, StrList from) {
    if (dest == NULL || from == NULL || from->pf->data == NULL) return;

    int sizeFrom = sizeStrList(from);
    int sizeDest = sizeStrList(dest);
    if ((sizeDest + sizeFrom) > dest->pf->capacity) {
        int newCapacity = (sizeDest + sizeFrom) * 2;
        dest->pf->capacity = newCapacity;
        dest->pf->data = realloc(dest->pf->data, newCapacity * sizeof(String*));
        for (int i = 0; i < dest->pf->capacity; ++i)
            dest->pf->data[i] = NULL;

        for (int i = sizeFrom; i < sizeFrom + sizeDest; ++i) {
            dest->pf->data[i] = stringOf(from->pf->data[i]->data);
        }
        dest->pf->count += sizeFrom;
    } else {
        int indexFrom = 0;
        for (int i = sizeDest; i < sizeFrom + sizeDest; ++i) {
            dest->pf->data[i] = stringOf(from->pf->data[indexFrom++]->data);
        }
        dest->pf->count += sizeFrom;
    }
}

string getStrList(StrList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return NULL;
    }

    if (index < 0 || index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return NULL;
    }

    return stringOf(list->pf->data[index]->data);
}

bool setStrList(StrList list, int index, string str) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index] = stringOf(str->data);
    return true;
}

bool setCharArrList(StrList list, int index, char* str) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index] = stringOf(str);
    return true;
}

int indexOfStrList(StrList list, string str) {
    if (list == NULL || str == NULL)
        return -1;

    for (int i = 0; i < list->pf->count; ++i) {
        if (list->pf->data[i] == NULL)
            continue;

        if (compareStr(list->pf->data[i], str) == 0)
            return i;
    }
    return -1;
}

void sortStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = list->pf->count;
    quickSort(list->pf->data, 0, high);
}

void sortStrListReverse(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = sizeStrList(list);
    quickSortReverse(list->pf->data, 0, high);
}

void clearStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    free(list->pf->data);
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
}

bool containsStrList(StrList list, string str) {
    if (list == NULL || isEmptyStr(str))
        return false;

    for (int i = 0; i < list->pf->count; ++i) {
        if (compareStr(list->pf->data[i], str) == 0)
            return true;
    }
    return false;
}

bool containsAllStrList(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL || list2->pf->count > list1->pf->count)
        return false;

    StrList temp = newStrList(temp);
    copyList(temp, list1);
    sortStrList(temp);

    for (int i = 0; i < list2->pf->count; ++i) {
        if (!binarySearchStr(list2->pf->data[i], temp->pf->data, temp->pf->count))
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

    for (int i = 0; i < list2->pf->count; ++i) {
        if (binarySearchStr(list2->pf->data[i], temp->pf->data, temp->pf->count))
            return true;
    }

    deleteStrList(&temp);

    return false;
}

bool removeStrList(StrList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    if (list->pf->count == 1 && index == 0) {
        deleteString(&list->pf->data[index]);
        list->pf->count = 0;
        list->pf->data[index] = NULL;
        return true;
    }

    int sizeTemp = list->pf->count - index - 1;
    String** temp = malloc(sizeTemp * sizeof(String*));
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->pf->data[counter++];
    }

    memcpy(&list->pf->data[index], temp, sizeTemp * sizeof(String));
    list->pf->count--;

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

    int* indexList = malloc(list2->pf->count * sizeof(int));

    int j = 0;
    for (int i = 0; i < list2->pf->count; ++i) {
        int index = indexOfStrList(list1, list2->pf->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    for (int i = 0; i < list1->pf->count; ++i) {
        deleteString(&list1->pf->data[i]);
    }

    free(list1->pf->data);
    list1->pf->data = malloc(list1->pf->capacity * sizeof(string));
    for (int i = 0; i < list1->pf->capacity; ++i) {
        list1->pf->data[i] = NULL;
    }

    int index = 0;
    for (int i = 0; i < list1->pf->count; ++i) {
        if (binarySearch(i, indexList, j)) // 1
            continue;

        list1->pf->data[index] = temp->pf->data[i];
        ++index;
    }

    list1->pf->count -= j;

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

    for (int i = 0; i < list2->pf->count; ++i) {
        int index = indexOfStrList(copyValues, list2->pf->data[i]);
        if (index != -1) {
            deleteString(&copyValues->pf->data[index]);
        }
    }

    StrList temp = newStrList(temp);
    int index = 0;
    for (int i = 0; i < copyValues->pf->count; ++i) {
        if (copyValues->pf->data[i] != NULL) {
            if (isFull(temp)) {
                temp->pf->data = increaseCapacity(temp);
            }

            temp->pf->data[index++] = stringOf(copyValues->pf->data[i]->data);
            temp->pf->count++;
        }
    }

    deleteStrList(&copyValues);
    return temp;
}

bool isEmptyStrList(StrList list) {
    return list == NULL || list->pf->count == 0;
}

void reverseStrList(StrList list) {
    String** start = list->pf->data;
    String** end = list->pf->data + (list->pf->count - 1);
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
    if (list1 == NULL || list2 == NULL || list1->pf->count != list2->pf->count)
        return false;

    int counter = list1->pf->count;
    for (int i = 0; i < counter; ++i) {
        char* temp1 = list1->pf->data[i]->data;
        char* temp2 = list2->pf->data[i]->data;

        if (strcmp(temp1, temp2) != 0)
            return false;
    }

    return true;
}

StrList emptyIfNullStrList(StrList list) {
    return list == NULL ? newStrList(list) : list;
}

int sizeStrList(StrList list) {
    return list->pf->count;
}

string toStringStrList(StrList list) {
    char* text = NULL;
    if (list->pf->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return stringOf(text);
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");

    for (int i = 0; i < list->pf->count - 1; ++i) {
        checkCapacity(text, &count, list->pf->data[i]->count);
        sprintf(&text[strlen(text)], "%s,", list->pf->data[i]->data);
    }

    checkCapacity(text, &count, list->pf->data[list->pf->count - 1]->count);
    sprintf(&text[strlen(text)], "%s", list->pf->data[list->pf->count - 1]->data);
    strcat(text, "]");

    string s = stringOf(text);
    free(text);

    return s;
}

void printStrList(StrList list) {
    if (list == NULL) return;

    int counter = list->pf->count;
    printf("%s", "[");
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1) {
            if (list->pf->data[i] == NULL || list->pf->data[i]->data == NULL)
                printf("%s", "null");
            else
                printf("%s", list->pf->data[i]->data);
        } else {
            if (list->pf->data[i] == NULL || list->pf->data[i]->data == NULL)
                printf("%s, ", "null");
            else
                printf("%s, ", list->pf->data[i]->data);
        }
    }
    printf("%s\n", "]");
}

void deleteStrList(StrList* list) {
    if (list == NULL || *list == NULL) {
        printf("%s\n", "List is NULL.");
        return;
    }

    if ((*list)->pf->data != NULL) {
        for (int i = 0; i < (*list)->pf->count; ++i) {
            if ((*list)->pf->data[i] != NULL) {
                deleteString(&(*list)->pf->data[i]);
            }
        }
        free((*list)->pf->data);
    }

    free((*list)->pf);
    free(*list);
    *list = NULL;
}

Iterator iteratorStrList(StrList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->pf->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = STR_LIST;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

// ===================== private funcs =======================

static String** increaseCapacity(StrList list) {
    int oldSize = list->pf->count;
    list->pf->capacity *= 2;

    String** temp = list->pf->data;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    assert(list->pf->data != NULL);

    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->data[i] = NULL;

    for (int i = 0; i < list->pf->count; ++i) {
        memcpy(&list->pf->data[i], &temp[i], sizeof(String));
    }

    for (int i = 0; i < oldSize; ++i) {
        deleteString(&temp[i]);
    }

    free(temp);

    return list->pf->data;
}

static int compareStr(string s1, string s2) {
    int result = strcmp(s1->data, s2->data);
    return result;
}

static void copyList(StrList dest, StrList from) {
    for (int i = 0; i < from->pf->count; ++i) {
        if (isFull(dest)) {
            dest->pf->data = increaseCapacity(dest);
        }

        dest->pf->data[i] = stringOf(from->pf->data[i]->data);
        dest->pf->count++;
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
    return list->pf->count > list->pf->capacity / 5 * 4;
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