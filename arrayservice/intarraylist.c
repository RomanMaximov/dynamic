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
static int* increaseCapacityAddAll(IntList list, int size);
static int compareInt(const void* elem1, const void* elem2);
static int compareReverse(const void* elem1, const void* elem2);


void addIntList(IntList list, int num) {
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

void addAllIntList(IntList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList from = (IntList) ctx->collection;
        if (dest->pf->capacity <= from->pf->count + dest->pf->count) {
            dest->pf->data = increaseCapacityAddAll(dest, from->pf->count);
            memcpy(&dest->pf->data[dest->pf->count], from->pf->data, sizeof(int) * from->pf->count);
            dest->pf->count += from->pf->count;
        } else {
            memcpy(&dest->pf->data[dest->pf->count], from->pf->data, sizeof(int) * from->pf->count);
            dest->pf->count += from->pf->count;
        }
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
        IntSet fromSet = (IntSet) ctx->collection;
        int* arr = malloc(fromSet->pf->count * sizeof(int));
        setToArrInt(fromSet, arr);
        if (dest->pf->capacity <= fromSet->pf->count + dest->pf->count) {
            dest->pf->data = increaseCapacityAddAll(dest, fromSet->pf->count);
            memcpy(&dest->pf->data[dest->pf->count], arr, sizeof(int));
            dest->pf->count += fromSet->pf->count;
        } else {
            memcpy(&dest->pf->data[dest->pf->count], arr, sizeof(int));
            dest->pf->count += fromSet->pf->count;
        }

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

bool containsAllIntList(IntList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        IntSet set = pr_initSi_(set, list->values);
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
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        IntSet set = pr_initSi_(set, list->values);
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
        if (setFrom->pf->count > list->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        IntSet setTemp = pr_initSi_(setTemp, list->values);
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

bool containsAnyIntList(IntList list, void* source) {
    if (list == NULL || source == NULL || isEmptyIntList(list)) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == INT_LIST) {
        IntList list2 = (IntList) ctx->collection;
        IntSet set = pr_initSi_(set, list->values);

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
        IntSet set = pr_initSi_(set, list->values);
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
        IntSet setTemp = pr_initSi_(setTemp, list->values);
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

bool removeAllIntList(IntList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    IntList tempList;

    if (ctx->type == INT_LIST) {
        tempList = subtractIntList(list, (void*) ctx);
    }

    if (ctx->type == INT_LL) {
        tempList = subtractIntList(list, (void*) ctx);
    }

    if (ctx->type == INT_SET) {
        tempList = subtractIntList(list, (void*) ctx);
    }

    free(list->pf->data);
    list->pf->count = tempList->pf->count;
    list->pf->data = malloc(list->pf->capacity * sizeof(int));
    assert(list->pf->data != NULL);
    memcpy(&list->pf->data[0], tempList->pf->data, sizeof(int) * tempList->pf->count);

    return true;
}

IntList subtractIntList(IntList list, void* source) {
    if (isEmptyIntList(list)) {
        IntList temp = NULL;
        return pr_initLi_(temp, NULL);
    }

    if (source == NULL) {
        IntList temp = pr_initLi_(temp, list->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    IntList tempList = pr_initLi_(tempList, NULL);

    if (ctx->type == INT_LIST) {
        IntList listSource = (IntList) ctx->collection;
        if (listSource->pf->count == 0) {
            IntList temp = pr_initLi_(temp, list->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == INT_LL) {
        IntLinkedList listSource = (IntLinkedList) ctx->collection;
        if (listSource->pf->count == 0) {
            IntList temp = pr_initLi_(temp, list->values);
            return temp;
        }

        IntSet setFrom = pr_initSi_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == INT_SET) {
        IntSet setFrom = (IntSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            IntList temp = pr_initLi_(temp, list->values);
            return temp;
        }

        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
    }

    return tempList;
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
            assert(text != NULL);
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

// ===================== private funcs =======================

static int* increaseCapacity(IntList list) {
    list->pf->capacity *= 2;
    list->pf->data = realloc(list->pf->data, list->pf->capacity * sizeof(int));
    assert(list->pf->data != NULL);

    return list->pf->data;
}

static int* increaseCapacityAddAll(IntList list, int size) {
    list->pf->capacity += size;
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