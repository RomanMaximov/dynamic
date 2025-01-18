//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarraylist.h"

typedef struct InnerIntList {
    int count;
    int* data;
    int capacity;
} InnerIntList;


// private funcs prototypes
static int* increaseCapacity(IntList list);
static int compareInt(const void* elem1, const void* elem2);
static int compareReverse(const void* elem1, const void* elem2);
static bool binarySearch(int elem, const int* arr, int high);
static void copyList(IntList dest, IntList from);
static bool hasNext(Iterator iter);


void addIntList(IntList list, int num) {
    void* elem = &num;
    if (list->inner->count == list->inner->capacity) {
        list->inner->data = increaseCapacity(list);

        //memcpy(&list->data[list->count], elem, sizeof(int));
        //list->count++;
        list->inner->data[list->inner->count] = num;
        list->inner->count++;
    }
    else {
        list->inner->data[list->inner->count] = num;
        list->inner->count++;
    }
}

void addAllIntList(IntList dest, IntList from) {
    if (dest == NULL || from == NULL || from->inner->data == NULL) return;

    int sizeFrom = sizeIntList(from);
    int sizeDest = sizeIntList(dest);

    if ((sizeDest + sizeFrom) > dest->inner->capacity) {
        int newCapacity = (sizeDest + sizeFrom) * 2;
        dest->inner->capacity = newCapacity;
        dest->inner->data = realloc(dest->inner->data, newCapacity * sizeof(int));

        memcpy(&dest->inner->data[dest->inner->count], from->inner->data, sizeFrom * sizeof(int));
        dest->inner->count += sizeFrom;
    } else {
        memcpy(&dest->inner->data[dest->inner->count], from->inner->data, sizeFrom * sizeof(int));
        dest->inner->count += sizeFrom;
    }
}

int getIntList(IntList list, int index) {
    if (list == NULL) {
        puts("Error: List is null.");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return EXIT_FAILURE;
    }

    return list->inner->data[index];
}

bool setIntList(IntList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    list->inner->data[index] = num;
    return true;
}

int indexOfIntList(IntList list, int elem) {
    if (isEmptyIntList(list))
        return -1;

    for (int i = 0; i < list->inner->count; ++i) {
        if (list->inner->data[i] == elem)
            return i;
    }
    return -1;
}

void sortIntList(IntList list) {
    if (isEmptyIntList(list))
        return;

    qsort(list->inner->data, list->inner->count, sizeof(int), compareInt);
}

void sortIntListReverse(IntList list) {
    if (isEmptyIntList(list))
        return;

    qsort(list->inner->data, list->inner->count, sizeof(int), compareReverse);
}

void clearIntList(IntList list) {
    if (isEmptyIntList(list))
        return;

    free(list->inner->data);
    list->inner->count = 0;
    list->inner->capacity = 20;
    list->inner->data = malloc(list->inner->capacity * sizeof(int));
}

bool containsIntList(IntList list, int num) {
    for (int i = 0; i < list->inner->count; ++i) {
        if (list->inner->data[i] == num)
            return true;
    }
    return false;
}

bool containsAllIntList(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count)
        return false;

    for (int i = 0; i < list2->inner->count; ++i) {
        if (indexOfIntList(list1, list2->inner->data[i]) == -1)
            return false;
    }

    return true;
}

bool containsAnyIntList(IntList list1, IntList list2) {
    if (isEmptyIntList(list1) || isEmptyIntList(list2 ))
        return false;

    for (int i = 0; i < list2->inner->count; ++i) {
        if (containsIntList(list1, list2->inner->data[i]))
            return true;
    }

    return false;
}

bool removeIntList(IntList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    if (list->inner->count == 1) {
        list->inner->count = 0;
        free(list->inner->data);
        list->inner->data = malloc(list->inner->count * sizeof(int));
        return true;
    }

    int* temp = malloc((list->inner->count - index - 1) * sizeof(int));
    int sizeTemp = list->inner->count - index - 1;
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->inner->data[counter++];
    }

    memcpy(&list->inner->data[index], temp, sizeTemp * sizeof(int));
    list->inner->count--;
    free(temp);

    return true;
}

bool removeAllIntList(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    int* temp = malloc(list1->inner->count * sizeof(int));
    int* indexList = malloc(list2->inner->count * sizeof(int));
    memcpy(&temp[0], list1->inner->data, list1->inner->count * sizeof(int));

    int j = 0;
    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfIntList(list1, list2->inner->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    free(list1->inner->data);
    list1->inner->data = malloc(list1->inner->capacity * sizeof(int));

    int index = 0;
    for (int i = 0; i < list1->inner->count; ++i) {
        if (binarySearch(i, indexList, j))
            continue;

        list1->inner->data[index] = temp[i];
        ++index;
    }

    list1->inner->count -= j;
    if (list1->inner->count == 0)
        list1->inner->data = NULL;

    free(indexList);
    free(temp);

    return true;
}

IntList subtractInt(IntList list1, IntList list2) {
    if (isEmptyIntList(list1)) {
        IntList temp = NULL;
        return newIntList(temp);
    }

    if (isEmptyIntList(list2)) {
        IntList temp = newIntList(temp);
        copyList(temp, list1);
        return temp;
    }

    IntList copyValues = newIntList(copyValues);
    copyList(copyValues, list1);

    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfIntList(copyValues, list2->inner->data[i]);
        if (index != -1)
            copyValues->inner->data[index] = INT_MIN;
    }

    IntList temp = newIntList(temp);
    int index = 0;
    for (int i = 0; i < copyValues->inner->count; ++i) {
        if (copyValues->inner->data[i] != INT_MIN) {
            if (temp->inner->count == temp->inner->capacity) {
                temp->inner->data = increaseCapacity(temp);
            }
            temp->inner->data[index++] = copyValues->inner->data[i];
        }
    }

    deleteIntList(&copyValues);
    return temp;
}

bool isEmptyIntList(IntList list) {
    return list == NULL || list->inner->count == 0;
}

void reverseIntList(IntList list) {
    if (list == NULL || list->inner->data == NULL) return;

    int* start = list->inner->data;
    int* end = list->inner->data + (list->inner->count - 1);
    int temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualsIntList(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->inner->count != list2->inner->count)
        return false;

    for (int i = 0; i < list1->inner->count; ++i) {
        if (list1->inner->data[i] != list2->inner->data[i])
            return false;
    }

    return true;
}

IntList emptyIfNullIntList(IntList list) {
    return list == NULL ? newIntList(list) : list;
}

int sizeIntList(IntList list) {
    return list->inner->count;
}

string toStringInt(IntList list) {
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
        sprintf(&text[strlen(text)], "%d,", list->inner->data[i]);
        if (strlen(text) > (int)(count / 8 * 6)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%d", list->inner->data[list->inner->count - 1]);
    strcat(text, "]");
    string s = stringOf(text);
    free(text);

    return s;
}

void printIntList(IntList list) {
    if (list == NULL || list->inner->data == NULL) {
        puts("[]");
        return;
    }

    printf("%s", "[");
    int counter = list->inner->count;

    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%d", list->inner->data[i]);
        else
            printf("%d, ", list->inner->data[i]);
    }
    printf("%s\n", "]");
}

void deleteIntList(IntList* list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->inner->data != NULL)
        free((*list)->inner->data);

    free((*list)->inner);
    free(*list);
    *list = NULL;
}

Iterator iteratorIntList(IntList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->inner->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = INT_LIST;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

// ===================== private funcs =======================

static int* increaseCapacity(IntList list) {
    list->inner->capacity *= 2;
    list->inner->data = realloc(list->inner->data, list->inner->capacity * sizeof(int));
    assert(list->inner->data != NULL);

    return list->inner->data;
}

static int compareInt(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

static int compareReverse(const void* elem1, const void* elem2) {
    return (*(int*)elem2 - *(int*)elem1);
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

static void copyList(IntList dest, IntList from) {
    for (int i = 0; i < from->inner->count; ++i) {
        if (dest->inner->count == dest->inner->capacity) {
            dest->inner->data = increaseCapacity(dest);
        }
        dest->inner->data[i] = from->inner->data[i];
        dest->inner->count++;
    }
}