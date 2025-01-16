//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "doublearraylist.h"

#define ACCURACY 0.000000001

typedef struct InnerDoubleList {
    int count;
    double* data;
    int capacity;
} InnerDoubleList;


// private funcs prototypes
static double* increaseCapacity(DoubleList list);
static int compareDouble(const void* elem1, const void* elem2);
static int compareReverse(const void* elem1, const void* elem2);
static bool binarySearch(double elem, const int* arr, int high);
static void copyList(DoubleList dest, DoubleList from);
static bool hasNext(Iterator iter);
static bool binarySearchInt(int elem, const int* arr, int high);


void addDoubleList(DoubleList list, double num) {
    void* elem = &num;
    if (list->inner->count == list->inner->capacity) {
        list->inner->data = increaseCapacity(list);

        list->inner->data[list->inner->count] = num;
        list->inner->count++;
    }
    else {
        list->inner->data[list->inner->count] = num;
        list->inner->count++;
    }
}

void addAllDoubleList(DoubleList dest, DoubleList from) {
    if (dest == NULL || from == NULL || from->inner->data == NULL) return;

    int sizeFrom = sizeDoubleList(from);
    int sizeDest = sizeDoubleList(dest);

    if ((sizeDest + sizeFrom) > dest->inner->capacity) {
        int newCapacity = (sizeDest + sizeFrom) * 2;
        dest->inner->capacity = newCapacity;
        dest->inner->data = realloc(dest->inner->data, newCapacity * sizeof(double));

        memcpy(&dest->inner->data[dest->inner->count], from->inner->data, sizeFrom * sizeof(double));
        dest->inner->count += sizeFrom;
    } else {
        memcpy(&dest->inner->data[dest->inner->count], from->inner->data, sizeFrom * sizeof(double));
        dest->inner->count += sizeFrom;
    }
}

double getElemDoubleList(DoubleList list, int index) {
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

bool  setElemDoubleList(DoubleList list, int index, double num) {
    if (list == NULL)
        return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    list->inner->data[index] = num;
    return true;
}

int indexOfDoubleList(DoubleList list, double elem) {
    if (isEmptyDoubleList(list))
        return -1;

    for (int i = 0; i < list->inner->count; ++i) {
        if (fabs(list->inner->data[i] - elem) < ACCURACY)
            return i;
    }
    return -1;
}

void sortDoubleList(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    qsort(list->inner->data, list->inner->count, sizeof(double), compareDouble);
}

void sortDoubleListReverse(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    qsort(list->inner->data, list->inner->count, sizeof(double), compareReverse);
}

void clearDoubleList(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    list->inner->count = 0;
    free(list->inner->data);
    list->inner->data = malloc(list->inner->count * sizeof(double));
}

bool containsDoubleList(DoubleList list, double num) {
    for (int i = 0; i < sizeDoubleList(list); ++i) {
        if (fabs(list->inner->data[i] - num) < ACCURACY)
            return true;
    }
    return false;
}

bool containsAllDoubleList(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL || list2->inner->count > list1->inner->count)
        return false;

    for (int i = 0; i < list1->inner->count; ++i) {
        for (int j = 0; j < list2->inner->count; ++j) {
            if (fabs(list1->inner->data[i] - list2->inner->data[j]) > 0.000001)
                return false;
        }
    }

    return true;
}

bool containsAnyDoubleList(DoubleList list1, DoubleList list2) {
    if (isEmptyDoubleList(list1) || isEmptyDoubleList(list2))
        return false;

    for (int i = 0; i < list2->inner->count; ++i) {
        if (containsDoubleList(list1, list2->inner->data[i]))
            return true;
    }

    return false;
}

bool removeDoubleList(DoubleList list, int index) {
    if (list == NULL) return false;

    if (index >= list->inner->count) {
        printf("Index %d out of bounds for length %d\n", index, list->inner->count);
        return false;
    }

    if (list->inner->count == 1) {
        list->inner->count = 0;
        free(list->inner->data);
        list->inner->data = malloc(list->inner->count * sizeof(double));
        return true;
    }

    double* temp = malloc((list->inner->count - index - 1) * sizeof(double));
    int sizeTemp = list->inner->count - index - 1;
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->inner->data[counter++];
    }
    memcpy(&list->inner->data[index], temp, sizeTemp * sizeof(double));
    list->inner->count--;
    free(temp);

    return true;
}

bool removeAllDoubleList(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    double* temp = malloc(list1->inner->count * sizeof(double));
    int* indexList = malloc(list2->inner->count * sizeof(int));
    memcpy(&temp[0], list1->inner->data, list1->inner->count * sizeof(double));

    int j = 0;
    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfDoubleList(list1, list2->inner->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareDouble);
    free(list1->inner->data);
    list1->inner->data = malloc(list1->inner->capacity * sizeof(double));

    int index = 0;
    for (int i = 0; i < list1->inner->count; ++i) {
        if (binarySearchInt(i, indexList, j)) // 1
            continue;

        list1->inner->data[index] = temp[i];
        ++index;
    }
    list1->inner->count -= j;
    if (list1->inner->count == 0) list1->inner->data = NULL;
    free(indexList);
    free(temp);

    return true;
}

DoubleList subtractDoubleList(DoubleList list1, DoubleList list2) {
    if (isEmptyDoubleList(list1)) {
        DoubleList temp = NULL;
        return newDoubleList(temp);
    }

    if (isEmptyDoubleList(list2)) {
        DoubleList temp = newDoubleList(temp);
        copyList(temp, list1);
        return temp;
    }

    DoubleList copyValues = newDoubleList(copyValues);
    copyList(copyValues, list1);
    for (int i = 0; i < list2->inner->count; ++i) {
        int index = indexOfDoubleList(copyValues, list2->inner->data[i]);
        if (index != -1)
            copyValues->inner->data[index] = INT_MIN;
    }

    DoubleList temp = newDoubleList(temp);
    int index = 0;
    for (int i = 0; i < copyValues->inner->count; ++i) {
        if (copyValues->inner->data[i] != INT_MIN) {
            if (temp->inner->count == temp->inner->capacity) {
                temp->inner->data = increaseCapacity(temp);
            }
            temp->inner->data[index++] = copyValues->inner->data[i];
        }
    }
    deleteDoubleList(&copyValues);
    return temp;
}

bool isEmptyDoubleList(DoubleList list) {
    return list == NULL || list->inner->count == 0;
}

void reverseDoubleList(DoubleList list) {
    double* start = list->inner->data;
    double* end = list->inner->data + (list->inner->count - 1);
    double temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualsDoubleList(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL || list1->inner->count != list2->inner->count)
        return false;

    for (int i = 0; i < list1->inner->count; ++i) {
        if (fabs(list1->inner->data[i] - list2->inner->data[i]) > ACCURACY)
            return false;
    }

    return true;
}

DoubleList emptyIfNullDoubleList(DoubleList list) {
    return list == NULL ? newDoubleList(list) : list;
}

int sizeDoubleList(DoubleList list) {
    return list->inner->count;
}

string toStringDoubleList(DoubleList list) {
    char* text = NULL;
    if (list->inner->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return text;
    }

    int count = 256;
    text = (char*)malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->inner->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%f,", list->inner->data[i]);
        if (strlen(text) > (unsigned long long int)(count * 0.8)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%f", list->inner->data[list->inner->count - 1]);
    strcat(text, "]");
    string s = stringOf(text);
    free(text);

    return s;
}

void printDoubleList(DoubleList list) {
    if (list == NULL || list->inner->data == NULL) {
        puts("[]");
        return;
    }

    printf("%s", "[");
    int counter = list->inner->count;
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%.9f", list->inner->data[i]);
        else
            printf("%.9f, ", list->inner->data[i]);
    }
    printf("%s\n", "]");
}

void deleteDoubleList(DoubleList* list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->inner->data != NULL)
        free((*list)->inner->data);

    free((*list)->inner);
    free(*list);
    *list = NULL;
}

Iterator iteratorDoubleList(DoubleList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->inner->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = DOUBLE_LIST;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

// ===================== private funcs =======================

static int compareDouble(const void* elem1, const void* elem2) {
    return fabs((*(double*)elem1 - *(double*)elem2)) < ACCURACY
           ? 0
           : (*(double*)elem1 - *(double*)elem2) < 0 ? -1 : 1;
}

static int compareReverse(const void* elem1, const void* elem2) {
    return fabs((*(double*)elem2 - *(double*)elem1)) < ACCURACY
           ? 0
           : (*(double*)elem2 - *(double*)elem1) < 0 ? -1 : 1;
}

static double* increaseCapacity(DoubleList list) {
    list->inner->capacity *= 2;
    list->inner->data = realloc(list->inner->data, list->inner->capacity * sizeof(double));
    assert(list->inner->data != NULL);

    return list->inner->data;
}

static void copyList(DoubleList dest, DoubleList from) {
    for (int i = 0; i < from->inner->count; ++i) {
        if (dest->inner->count == dest->inner->capacity) {
            dest->inner->data = increaseCapacity(dest);
        }
        dest->inner->data[i] = from->inner->data[i];
        dest->inner->count++;
    }
}

static bool binarySearchInt(int elem, const int* arr, int high) {
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



