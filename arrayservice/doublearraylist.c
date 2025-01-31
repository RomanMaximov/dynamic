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
    if (list->pf->count == list->pf->capacity) {
        list->pf->data = increaseCapacity(list);

        list->pf->data[list->pf->count] = num;
        list->pf->count++;
    }
    else {
        list->pf->data[list->pf->count] = num;
        list->pf->count++;
    }
}

void addAllDoubleList(DoubleList dest, DoubleList from) {
    if (dest == NULL || from == NULL || from->pf->data == NULL) return;

    int sizeFrom = sizeDoubleList(from);
    int sizeDest = sizeDoubleList(dest);

    if ((sizeDest + sizeFrom) > dest->pf->capacity) {
        int newCapacity = (sizeDest + sizeFrom) * 2;
        dest->pf->capacity = newCapacity;
        dest->pf->data = realloc(dest->pf->data, newCapacity * sizeof(double));

        memcpy(&dest->pf->data[dest->pf->count], from->pf->data, sizeFrom * sizeof(double));
        dest->pf->count += sizeFrom;
    } else {
        memcpy(&dest->pf->data[dest->pf->count], from->pf->data, sizeFrom * sizeof(double));
        dest->pf->count += sizeFrom;
    }
}

double getDoubleList(DoubleList list, int index) {
    if (list == NULL) {
        puts("Error: List is null.");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return EXIT_FAILURE;
    }

    return list->pf->data[index];
}

bool  setDoubleList(DoubleList list, int index, double num) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index] = num;
    return true;
}

int indexOfDoubleList(DoubleList list, double elem) {
    if (isEmptyDoubleList(list))
        return -1;

    for (int i = 0; i < list->pf->count; ++i) {
        if (fabs(list->pf->data[i] - elem) < ACCURACY)
            return i;
    }
    return -1;
}

void sortDoubleList(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    qsort(list->pf->data, list->pf->count, sizeof(double), compareDouble);
}

void sortDoubleListReverse(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    qsort(list->pf->data, list->pf->count, sizeof(double), compareReverse);
}

void clearDoubleList(DoubleList list) {
    if (isEmptyDoubleList(list))
        return;

    list->pf->count = 0;
    list->pf->capacity = 20;
    free(list->pf->data);
    list->pf->data = malloc(list->pf->count * sizeof(double));
}

bool containsDoubleList(DoubleList list, double num) {
    for (int i = 0; i < sizeDoubleList(list); ++i) {
        if (fabs(list->pf->data[i] - num) < ACCURACY)
            return true;
    }
    return false;
}

bool containsAllDoubleList(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL || list2->pf->count > list1->pf->count)
        return false;

    for (int i = 0; i < list1->pf->count; ++i) {
        for (int j = 0; j < list2->pf->count; ++j) {
            if (fabs(list1->pf->data[i] - list2->pf->data[j]) > 0.000001)
                return false;
        }
    }

    return true;
}

bool containsAnyDoubleList(DoubleList list1, DoubleList list2) {
    if (isEmptyDoubleList(list1) || isEmptyDoubleList(list2))
        return false;

    for (int i = 0; i < list2->pf->count; ++i) {
        if (containsDoubleList(list1, list2->pf->data[i]))
            return true;
    }

    return false;
}

bool removeDoubleList(DoubleList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    if (list->pf->count == 1) {
        list->pf->count = 0;
        free(list->pf->data);
        list->pf->data = malloc(list->pf->count * sizeof(double));
        return true;
    }

    double* temp = malloc((list->pf->count - index - 1) * sizeof(double));
    int sizeTemp = list->pf->count - index - 1;
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->pf->data[counter++];
    }
    memcpy(&list->pf->data[index], temp, sizeTemp * sizeof(double));
    list->pf->count--;
    free(temp);

    return true;
}

bool removeAllDoubleList(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    double* temp = malloc(list1->pf->count * sizeof(double));
    int* indexList = malloc(list2->pf->count * sizeof(int));
    memcpy(&temp[0], list1->pf->data, list1->pf->count * sizeof(double));

    int j = 0;
    for (int i = 0; i < list2->pf->count; ++i) {
        int index = indexOfDoubleList(list1, list2->pf->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareDouble);
    free(list1->pf->data);
    list1->pf->data = malloc(list1->pf->capacity * sizeof(double));

    int index = 0;
    for (int i = 0; i < list1->pf->count; ++i) {
        if (binarySearchInt(i, indexList, j)) // 1
            continue;

        list1->pf->data[index] = temp[i];
        ++index;
    }
    list1->pf->count -= j;
    if (list1->pf->count == 0) list1->pf->data = NULL;
    free(indexList);
    free(temp);

    return true;
}

DoubleList subtractDoubleList(DoubleList list1, DoubleList list2) {
    if (isEmptyDoubleList(list1)) {
        DoubleList temp = NULL;
        return pr_initLd_(temp);
    }

    if (isEmptyDoubleList(list2)) {
        DoubleList temp = pr_initLd_(temp);
        copyList(temp, list1);
        return temp;
    }

    DoubleList copyValues = pr_initLd_(copyValues);
    copyList(copyValues, list1);
    for (int i = 0; i < list2->pf->count; ++i) {
        int index = indexOfDoubleList(copyValues, list2->pf->data[i]);
        if (index != -1)
            copyValues->pf->data[index] = INT_MIN;
    }

    DoubleList temp = pr_initLd_(temp);
    int index = 0;
    for (int i = 0; i < copyValues->pf->count; ++i) {
        if (copyValues->pf->data[i] != INT_MIN) {
            if (temp->pf->count == temp->pf->capacity) {
                temp->pf->data = increaseCapacity(temp);
            }
            temp->pf->data[index++] = copyValues->pf->data[i];
        }
    }
    deleteDoubleList(&copyValues);
    return temp;
}

bool isEmptyDoubleList(DoubleList list) {
    return list == NULL || list->pf->count == 0;
}

void reverseDoubleList(DoubleList list) {
    double* start = list->pf->data;
    double* end = list->pf->data + (list->pf->count - 1);
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
    if (list1 == NULL || list2 == NULL || list1->pf->count != list2->pf->count)
        return false;

    for (int i = 0; i < list1->pf->count; ++i) {
        if (fabs(list1->pf->data[i] - list2->pf->data[i]) > ACCURACY)
            return false;
    }

    return true;
}

int sizeDoubleList(DoubleList list) {
    return list->pf->count;
}

string toStrDoubleList(DoubleList list) {
    char* text = NULL;
    if (list->pf->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return text;
    }

    int count = 256;
    text = (char*)malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->pf->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%f,", list->pf->data[i]);
        if (strlen(text) > (int)(count / 8 * 7)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%f", list->pf->data[list->pf->count - 1]);
    strcat(text, "]");
    string s = strOf(text);
    free(text);

    return s;
}

void printDoubleList(DoubleList list) {
    if (list == NULL || list->pf->data == NULL) {
        puts("[]");
        return;
    }

    printf("%s", "[");
    int counter = list->pf->count;
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%.9f", list->pf->data[i]);
        else
            printf("%.9f, ", list->pf->data[i]);
    }
    printf("%s\n", "]");
}

void deleteDoubleList(DoubleList* list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->pf->data != NULL)
        free((*list)->pf->data);

    free((*list)->pf);
    free(*list);
    *list = NULL;
}

Iterator iteratorDoubleList(DoubleList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->pf->count;
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
    list->pf->capacity *= 2;
    list->pf->data = realloc(list->pf->data, list->pf->capacity * sizeof(double));
    assert(list->pf->data != NULL);

    return list->pf->data;
}

static void copyList(DoubleList dest, DoubleList from) {
    for (int i = 0; i < from->pf->count; ++i) {
        if (dest->pf->count == dest->pf->capacity) {
            dest->pf->data = increaseCapacity(dest);
        }
        dest->pf->data[i] = from->pf->data[i];
        dest->pf->count++;
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



