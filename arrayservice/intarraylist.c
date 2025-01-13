//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "intarraylist.h"

typedef struct InnerIntList {
    int count;
    int* data;
    int capacity;
} InnerIntList;


// private funcs prototypes
static int* increaseCapacityInt(IntList list);


void addIntElemList(IntList list, int num) {
    void* elem = &num;
    if (list->inner->count == list->inner->capacity) {
        list->inner->data = increaseCapacityInt(list);

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

void addAllInt(IntList dest, IntList from) {
    int sizeFrom = sizeIntList(from);
    int sizeDest = sizeIntList(dest);
    if ((sizeDest + sizeFrom) > dest->capacity) {
        dest->capacity += sizeFrom;
        dest->data = realloc(dest->data, dest->capacity * sizeof(int));
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(int));
        dest->count += sizeFrom;
    } else {
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(int));
        dest->count += sizeFrom;
    }
}

int getElemInt(IntList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return EXIT_FAILURE;
    }

    return list->data[index];
}

bool setElemInt(IntList list, int index, int num) {
    if (list == NULL)
        return false;

    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return false;
    }

    list->data[index] = num;
    return true;
}

bool removeElemInt(IntList list, int index) {
    if (list == NULL) return false;

    if (index >= list->count) {
        printf("Index %d out of bounds for length %d\n", index, list->count);
        return false;
    }

    if (list->count == 1) {
        free(list->data);
        list->count = 0;
        list->capacity = 20;
        list->data = malloc(list->capacity * sizeof(int));
        return true;
    }
    int* temp = malloc((list->count - index - 1) * sizeof(int));
    int sizeTemp = list->count - index - 1;
    int counter = index;
    ++counter;
    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->data[counter++];
    }
    memcpy(&list->data[index], temp, sizeTemp * sizeof(int));
    list->count--;
    free(temp);

    return true;
}

bool removeAllInt(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    int* temp = malloc(list1->count * sizeof(int));
    int* indexList = malloc(list2->count * sizeof(int));
    memcpy(&temp[0], list1->data, list1->count * sizeof(int));

    int j = 0;
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfInt(list1, list2->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    qsort(indexList, j - 1, sizeof(int), compareInt);
    free(list1->data);
    list1->data = malloc(list1->capacity * sizeof(int));

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

char* toStringInt(IntList list) {
    char* text = NULL;
    if (list->count == 0) {
        text = (char*)malloc(3 * sizeof(char));
        text[0] = '[';
        text[1] = ']';
        text[2] = '\0';
        return text;
    }

    int count = 256;
    text = malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < list->count - 1; ++i) {
        sprintf(&text[strlen(text)], "%d,", list->data[i]);
        if (strlen(text) > (unsigned long long int)(count * 0.8)) {
            count *= 2;
            text = realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%d", list->data[list->count - 1]);
    strcat(text, "]");
    return text;
}

void printArrayInt(IntList list) {
    if (list == NULL) return;

    printf("%s", "[");
    int counter = (int)list->count;
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%d", list->data[i]);
        else
            printf("%d, ", list->data[i]);
    }
    printf("%s\n", "]");
}

void clearInt(IntList list) {
    if (list == NULL) return;

    free(list->data);
    list->count = 0;
    list->capacity = 20;
    list->data = malloc(list->capacity * sizeof(int));
}

// TODO доработать логику удаления, чтобы указатель после удаления был равен NULL. Чтобы повторное случайное удаление не вызывало ошибку.
void deleteArrayInt(IntList list) {
    if (list != NULL) {
        if (list->data != NULL)
            free(list->data);
        free(list);
    }
}

void sortInt(IntList list) {
    if (list == NULL)
        return;

    int high = sizeIntList(list);
    //quickSortInt(list->data, 0, high);
    qsort(list->data, high, sizeof(int), compareInt);
}

bool containsInt(IntList list, int num) {
    for (int i = 0; i < sizeIntList(list); ++i) {
        if (list->data[i] == num)
            return true;
    }
    return false;
}

bool containsAllInt(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL || list2->count > list1->count)
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (indexOfInt(list1, list2->data[i]) == -1)
            return false;
    }

    return true;
}

bool isEmptyInt(IntList list) {
    return list == NULL || list->count == 0;
}

int sizeIntList(IntList list) {
    return list->count;
}

void reverseListInt(IntList list) {
    int* start = list->data;
    int* end = list->data + (list->count - 1);
    int temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualIntLists(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->count != list2->count)
        return false;

    for (int i = 0; i < list1->count; ++i) {
        if (list1->data[i] != list2->data[i])
            return false;
    }

    return true;
}

int indexOfInt(IntList list, int elem) {
    if (list == NULL)
        return -1;

    for (int i = 0; i < list->count; ++i) {
        if (list->data[i] == elem)
            return i;
    }
    return -1;
}

IntList emptyIfNullInt(IntList list) {
    return list == NULL ? newIntArray(list) : list;
}

bool containsAnyInt(IntList list1, IntList list2) {
    if (isEmptyInt(list1) || isEmptyInt(list2 ))
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (containsInt(list1, list2->data[i]))
            return true;
    }

    return false;
}

IntList subtractInt(IntList list1, IntList list2) {
    if (isEmptyInt(list1)) {
        IntList temp = NULL;
        return newIntArray(temp);
    }

    if (isEmptyInt(list2)) {
        IntList temp = copyIntList(temp, list1);
        return temp;
    }

    IntList copyList = copyIntList(copyList, list1);
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfInt(copyList, list2->data[i]);
        if (index != -1)
            copyList->data[index] = INT_MIN;
    }

    IntList temp = newIntArray(temp);
    int index = 0;
    for (int i = 0; i < copyList->count; ++i) {
        if (copyList->data[i] != INT_MIN) {
            if (temp->count == temp->capacity) {
                temp->data = increaseCapacityInt(temp);
            }
            temp->data[index++] = copyList->data[i];
        }
    }
    deleteArrayInt(copyList);
    return temp;
}



// ===================== private funcs =======================

static int* increaseCapacityInt(IntList list) {
    list->inner->capacity *= 2;;
    list->inner->data = realloc(list->inner->data, list->inner->capacity * sizeof(int));
    assert(list->inner->data != NULL);

    return list->inner->data;
}

static int compareInt(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

void sortIntReverse(IntList list) {
    if (list == NULL)
        return;

    int high = sizeIntList(list);
    //quickSortInt(list->data, 0, high);
    qsort(list->data, high, sizeof(int), compareReverse);
}

static int compareReverse(const void* elem1, const void* elem2) {
    return (*(int*)elem2 - *(int*)elem1);
}

bool binarySearchInt(int elem, const int* arr, int high) {
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

IntList copyIntList(IntList dest, IntList from) {
    dest = newIntArray(dest);
    for (int i = 0; i < from->count; ++i) {
        if (dest->count == dest->capacity) {
            dest->data = increaseCapacityInt(dest);
        }
        dest->data[i] = from->data[i];
        dest->count++;
    }
    return dest;
}




