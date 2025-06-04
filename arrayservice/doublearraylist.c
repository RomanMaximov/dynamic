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
#include "../util/arraylistutil.h"

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

void addAllDoubleList(DoubleList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList from = (DoubleList) ctx->collection;

        for (int i = 0; i < from->pf->count; ++i)
            addDoubleList(dest, from->pf->data[i]);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList from = (DoubleLinkedList) ctx->collection;
        DoubleNode current = from->pf->begin;

        while (current != NULL) {
            addDoubleList(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet from = (DoubleSet) ctx->collection;

        double* arr = malloc(from->pf->count * sizeof(double));
        setToArrDouble(from, arr);

        for (int i = 0; i < from->pf->count; ++i)
            addDoubleList(dest, arr[i]);

        free(arr);
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

bool containsAllDoubleList(DoubleList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        DoubleSet set = pr_initSd_(set, list->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyDouble(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        DoubleSet set = pr_initSd_(set, list->values);
        DoubleNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyDouble(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count > list->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        DoubleSet setTemp = pr_initSd_(setTemp, list->values);
        DoubleList listTemp = pr_initLd_(listTemp, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyDouble(setTemp, listTemp->pf->data[i])) {
                setTemp->delete(&setTemp);
                listTemp->delete(&listTemp);
                return false;
            }
        }
        setTemp->delete(&setTemp);
        listTemp->delete(&listTemp);
    }

    return true;
}

bool containsAnyDoubleList(DoubleList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        DoubleSet set = pr_initSd_(set, list->values);

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyDouble(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        DoubleSet set = pr_initSd_(set, list->values);
        DoubleNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyDouble(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        DoubleSet setTemp = pr_initSd_(setTemp, list->values);
        DoubleList listTemp = pr_initLd_(listTemp, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyDouble(setTemp, listTemp->pf->data[i])) {
                setTemp->delete(&setTemp);
                listTemp->delete(&listTemp);
                return true;
            }
        }
        setTemp->delete(&setTemp);
        listTemp->delete(&listTemp);
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

bool removeAllDoubleList(DoubleList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    DoubleList tempList;

    if (ctx->type == DOUBLE_LIST) {
        DoubleList list2 = (DoubleList) ctx->collection;
        tempList = subtractDoubleList(list, list2);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList list2 = (DoubleLinkedList) ctx->collection;
        DoubleList copyValues = pr_initLd_(copyValues, list2->values);

        tempList = subtractDoubleList(list, copyValues);
        copyValues->delete(&copyValues);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet set = (DoubleSet) ctx->collection;
        DoubleList copyValues = pr_initLd_(copyValues, set->values);

        tempList = subtractDoubleList(list, copyValues);
        copyValues->delete(&copyValues);
    }

    list->delete(&list);
    list = tempList;

    return true;
}

DoubleList subtractDoubleList(DoubleList list, void* source) {
    if (isEmptyDoubleList(list)) {
        DoubleList temp = NULL;
        return pr_initLd_(temp, NULL);
    }

    if (source == NULL) {
        DoubleList temp = pr_initLd_(temp, list->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    DoubleList tempList = pr_initLd_(tempList, NULL);

    if (ctx->type == DOUBLE_LIST) {
        DoubleList listSource = (DoubleList) ctx->collection;
        if (listSource->pf->count == 0) {
            DoubleList temp = pr_initLd_(temp, list->values);
            return temp;
        }

        DoubleSet setFrom = pr_initSd_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == DOUBLE_LL) {
        DoubleLinkedList listSource = (DoubleLinkedList) ctx->collection;
        if (listSource->pf->count == 0) {
            DoubleList temp = pr_initLd_(temp, list->values);
            return temp;
        }

        DoubleSet setFrom = pr_initSd_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == DOUBLE_SET) {
        DoubleSet setFrom = (DoubleSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            DoubleList temp = pr_initLd_(temp, list->values);
            return temp;
        }

        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
    }

    list->delete(&list);
    list = tempList;

    return list;
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
        string s = strOf(text);
        free(text);
        return s;
    }

    int count = 256;
    text = (char*)malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->pf->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%f,", list->pf->data[i]);
        if (strlen(text) > (int)(count / 8 * 7)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
            assert(text != NULL);
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



