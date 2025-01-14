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
        dest->inner->capacity += sizeFrom;
        dest->inner->data = realloc(dest->inner->data, dest->inner->capacity * sizeof(double));
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

bool removeAllDouble(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    double* temp = malloc(list1->count * sizeof(double));
    int* indexList = malloc(list2->count * sizeof(int));
    memcpy(&temp[0], list1->data, list1->count * sizeof(double));

    int j = 0;
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfDouble(list1, list2->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    free(list1->data);
    list1->data = malloc(list1->capacity * sizeof(double));

    int index = 0;
    for (int i = 0; i < list1->count; ++i) {
        if (binarySearchInt(i, indexList, j)) // 1
            continue;

        list1->data[index] = temp[i];
        ++index;
    }
    list1->count -= j;
    if (list1->count == 0) list1->data = NULL;
    free(indexList);
    free(temp);

    return true;
}

char* toStringDouble(DoubleList list) {
    char* text = NULL;
    if (list->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return text;
    }

    int count = 256;
    text = (char*)malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%f,", list->data[i]);
        if (strlen(text) > (unsigned long long int)(count * 0.8)) {
            count *= 2;
            text = (char*)realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%f", list->data[list->count - 1]);
    strcat(text, "]");
    return text;
}

void printArrayDouble(DoubleList list) {
    if (list == NULL) return;

    printf("%s", "[");
    int counter = list->count;
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%.9f", list->data[i]);
        else
            printf("%.9f, ", list->data[i]);
    }
    printf("%s\n", "]");
}



// TODO доработать логику удаления, чтобы указатель после удаления был равен NULL. Чтобы повторное случайное удаление не вызывало ошибку.
void deleteArrayDouble(DoubleList list) {
    if (list != NULL) {
        if (list->data != NULL)
            free(list->data);
        free(list);
    }
}



bool containsDouble(DoubleList list, double num) {
    for (int i = 0; i < sizeDoubleList(list); ++i) {
        if (fabs(list->data[i] - num) < 0.000001)
            return true;
    }
    return false;
}

bool containsAllDouble(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL || list2->count > list1->count)
        return false;

    for (int i = 0; i < list1->count; ++i) {
        for (int j = 0; j < list2->count; ++j) {
            if (fabs(list1->data[i] - list2->data[j]) > 0.000001)
                return false;
        }
    }

    return true;
}

bool isEmptyDoubleList(DoubleList list) {
    return list == NULL || list->inner->count == 0;
}

int sizeDoubleList(DoubleList list) {
    return list->count;
}

void reverseListDouble(DoubleList list) {
    double* start = list->data;
    double* end = list->data + (list->count - 1);
    double temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualDoubleLists(DoubleList list1, DoubleList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->count != list2->count)
        return false;

    for (int i = 0; i < list1->count; ++i) {
        if (fabs(list1->data[i] - list2->data[i]) > 0.000001)
            return false;
    }

    return true;
}



DoubleList emptyIfNullDouble(DoubleList list) {
    return list == NULL ? newDoubleArray(list) : list;
}

bool containsAnyDouble(DoubleList list1, DoubleList list2) {
    if (isEmptyDouble(list1) || isEmptyDouble(list2))
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (containsDouble(list1, list2->data[i]))
            return true;
    }

    return false;
}

DoubleList subtractDouble(DoubleList list1, DoubleList list2) {
    if (isEmptyDouble(list1)) {
        DoubleList temp = NULL;
        return newDoubleArray(temp);
    }

    if (isEmptyDouble(list2)) {
        DoubleList temp = copyDoubleList(temp, list1);
        return temp;
    }

    DoubleList copyList = copyDoubleList(copyList, list1);
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfDouble(copyList, list2->data[i]);
        if (index != -1)
            copyList->data[index] = INT_MIN;
    }

    DoubleList temp = newDoubleArray(temp);
    int index = 0;
    for (int i = 0; i < copyList->count; ++i) {
        if (copyList->data[i] != INT_MIN) {
            if (temp->count == temp->capacity) {
                temp->data = increaseCapacityDouble(temp);
            }
            temp->data[index++] = copyList->data[i];
        }
    }
    deleteArrayDouble(copyList);
    return temp;
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
    list->capacity *= 2;
    list->data = realloc(list->data, list->capacity * sizeof(double));
    assert(list->data != NULL);

    return list->data;
}

DoubleList copyList(DoubleList dest, DoubleList from) {
    dest = newDoubleArray(dest);
    for (int i = 0; i < from->count; ++i) {
        if (dest->count == dest->capacity) {
            dest->data = increaseCapacityDouble(dest);
        }
        dest->data[i] = from->data[i];
        dest->count++;
    }
    return dest;
}



