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
#include "../util/arraylistutil.h"

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
static bool hasNext(Iterator iter);


void addIntList(IntList list, int num) {
    void* elem = &num;
    if (list->pf->count == list->pf->capacity) {
        list->pf->data = increaseCapacity(list);

        //memcpy(&list->data[list->count], elem, sizeof(int));
        //list->count++;
        list->pf->data[list->pf->count] = num;
        list->pf->count++;
    }
    else {
        list->pf->data[list->pf->count] = num;
        list->pf->count++;
    }
}

void addAllIntList(IntList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList from = (IntList) ctx->collection;
        for (int i = 0; i < from->pf->count; ++i)
            addIntList(dest, from->pf->data[i]);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList from = (IntLinkedList) ctx->collection;
        IntNode current = from->pf->begin;
        while (current != NULL) {
            addIntList(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == INT_SET) {
        IntSet from = (IntSet) ctx->collection;
        int* arr = malloc(from->pf->count * sizeof(int));
        setToArrInt(from, arr);
        for (int i = 0; i < from->pf->count; ++i)
            addIntList(dest, arr[i]);

        free(arr);
    }
}

int getIntList(IntList list, int index) {
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

bool setIntList(IntList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index] = num;
    return true;
}

int indexOfIntList(IntList list, int elem) {
    if (isEmptyIntList(list))
        return -1;

    for (int i = 0; i < list->pf->count; ++i) {
        if (list->pf->data[i] == elem)
            return i;
    }
    return -1;
}

void sortIntList(IntList list) {
    if (isEmptyIntList(list))
        return;

    qsort(list->pf->data, list->pf->count, sizeof(int), compareInt);
}

void sortIntListReverse(IntList list) {
    if (isEmptyIntList(list))
        return;

    qsort(list->pf->data, list->pf->count, sizeof(int), compareReverse);
}

void clearIntList(IntList list) {
    if (isEmptyIntList(list))
        return;

    free(list->pf->data);
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(int));
}

bool containsIntList(IntList list, int num) {
    for (int i = 0; i < list->pf->count; ++i) {
        if (list->pf->data[i] == num)
            return true;
    }
    return false;
}

bool containsAllIntList(IntList list1, void* source) {
    if (list1 == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        IntSet set = pr_initSi_(set, list1->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyInt(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        if (list2->pf->count > list1->pf->count)
            return false;

        IntSet set = pr_initSi_(set, list1->values);
        IntNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyInt(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count > list1->pf->count)
            return false;

        IntSet setTemp = pr_initSi_(setTemp, list1->values);
        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyInt(setTemp, listFrom->pf->data[i])) {
                setTemp->delete(&setTemp);
                listFrom->delete(&listFrom);
                return false;
            }
        }
        setTemp->delete(&setTemp);
        listFrom->delete(&listFrom);
    }

    return true;
}

bool containsAnyIntList(IntList list1, void* source) {
    if (list1 == NULL || source == NULL || isEmptyIntList(list1)) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        IntSet set = pr_initSi_(set, list1->values);

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyInt(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        IntSet set = pr_initSi_(set, list1->values);
        IntNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyInt(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        IntSet setTemp = pr_initSi_(setTemp, list1->values);
        IntList listFrom = pr_initLi_(listFrom, setFrom->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyInt(setTemp, listFrom->pf->data[i])) {
                setTemp->delete(&setTemp);
                listFrom->delete(&listFrom);
                return true;
            }
        }
        setTemp->delete(&setTemp);
        listFrom->delete(&listFrom);
    }

    return false;
}

bool removeIntList(IntList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    if (list->pf->count == 1) {
        list->pf->count = 0;
        free(list->pf->data);
        list->pf->data = malloc(list->pf->count * sizeof(int));
        return true;
    }

    int* temp = malloc((list->pf->count - index - 1) * sizeof(int));
    int sizeTemp = list->pf->count - index - 1;
    int counter = index;
    ++counter;

    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->pf->data[counter++];
    }

    memcpy(&list->pf->data[index], temp, sizeTemp * sizeof(int));
    list->pf->count--;
    free(temp);

    return true;
}

bool removeAllIntList(IntList list1, void* source) {
    if (list1 == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    IntList tempList;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        tempList = subtractIntList(list1, list2);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList list2 = (IntLinkedList) ctx->collection;
        IntList copyValues = pr_initLi_(copyValues, list2->values);

        tempList = subtractIntList(list1, copyValues);
        copyValues->delete(&copyValues);
    }

    if (ctx->type == INT_SET) {
        IntSet set = (IntSet) ctx->collection;
        IntList copyValues = pr_initLi_(copyValues, set->values);

        tempList = subtractIntList(list1, copyValues);
        copyValues->delete(&copyValues);
    }

    list1->delete(&list1);
    list1 = tempList;

    return true;
}

IntList subtractIntList(IntList list1, IntList list2) {
    if (isEmptyIntList(list1)) {
        IntList temp = NULL;
        return pr_initLi_(temp, NULL);
    }

    if (isEmptyIntList(list2)) {
        IntList temp = pr_initLi_(temp, list1->values);
        return temp;
    }

    IntSet set = pr_initSi_(set, list2->values);
    IntList temp = pr_initLi_(temp, NULL);

    for (int i = 0; i < list1->pf->count; ++i) {
        if (!set->contains(set, list1->pf->data[i]))
            temp->add(temp, list1->pf->data[i]);
    }

    set->delete(&set);

    return temp;
}

bool isEmptyIntList(IntList list) {
    return list == NULL || list->pf->count == 0;
}

void reverseIntList(IntList list) {
    if (list == NULL || list->pf->data == NULL) return;

    int* start = list->pf->data;
    int* end = list->pf->data + (list->pf->count - 1);
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

    if (list1->pf->count != list2->pf->count)
        return false;

    for (int i = 0; i < list1->pf->count; ++i) {
        if (list1->pf->data[i] != list2->pf->data[i])
            return false;
    }

    return true;
}

int sizeIntList(IntList list) {
    return list->pf->count;
}

string toStrIntList(IntList list) {
    if (list == NULL)
        return NULL;

    char* text = NULL;
    if (list->pf->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return strOf(text);
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->pf->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%d,", list->pf->data[i]);
        if (strlen(text) > (int)(count / 8 * 7)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%d", list->pf->data[list->pf->count - 1]);
    strcat(text, "]");
    string s = strOf(text);
    free(text);

    return s;
}

void printIntList(IntList list) {
    if (list == NULL || list->pf->count == 0) {
        puts("[]");
        return;
    }

    printf("%s", "[");
    int counter = list->pf->count;

    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%d", list->pf->data[i]);
        else
            printf("%d, ", list->pf->data[i]);
    }
    printf("%s\n", "]");
}

void deleteIntList(IntList* list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->pf->data != NULL)
        free((*list)->pf->data);

    free((*list)->pf);
    free(*list);
    *list = NULL;
}

Iterator iteratorIntList(IntList list){
    Iterator iter = malloc(sizeof(Itr));
    iter->count = 0;
    iter->data = list;
    iter->collectionSize = list->pf->count;
    iter->hasNext = (void*) hasNext(iter);
    iter->type = INT_LIST;
    return iter;
}

static bool hasNext(Iterator iter) {
    return iter->count < iter->collectionSize;
}

// ===================== private funcs =======================

static int* increaseCapacity(IntList list) {
    list->pf->capacity *= 2;
    list->pf->data = realloc(list->pf->data, list->pf->capacity * sizeof(int));
    assert(list->pf->data != NULL);

    return list->pf->data;
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