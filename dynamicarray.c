#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "dynamicarray.h"

String** increaseCapacity(StringList list);

IntList newIntArray(IntList list) {
    list = (IntList)malloc(sizeof(IntArray));
    list->count = 0;
    list->capacity = 20;
    list->data = malloc(list->capacity * sizeof(int));
    return list;
}

DoubleList newDoubleArray(DoubleList list) {
    list = (DoubleArray*)malloc(sizeof(DoubleArray));
    list->count = 0;
    list->capacity = 20;
    list->data = (double*)malloc(list->capacity * sizeof(double));
    return list;
}

StringList newStringArray(StringList temp) {
    StringList list = malloc(sizeof(StringArray));
    list->count = 0;
    list->capacity = 20;
    list->str = malloc(list->capacity * sizeof(String*));
    for (int i = 0; i < list->capacity; ++i) {
        list->str[i] = NULL;
    }
    return list;
}



int sizeIntArray(IntList list) {
    return (int)list->count;
}

int sizeDoubleArray(DoubleList list) {
    return (int)list->count;
}

int sizeStringArray(StringList list) {
    return (int)list->count;
}

void addIntElem(IntList list, int num) {
    void* elem = &num;
    if (list->count == list->capacity) {
        list->capacity *= 2;
        int* temp = list->data;
        list->data = malloc(list->capacity * sizeof(int));
        for (int i = 0; i < list->count; ++i) {
            memcpy(&list->data[i], &temp[i], sizeof(int));
        }
        free(temp);

        memcpy(&list->data[list->count], elem, sizeof(int));
        list->count++;
    }
    else {
        memcpy(&list->data[list->count], elem, sizeof(int));
        list->count++;
    }
}

void addDoubleElem(DoubleList list, double num) {
    void* elem = &num;
    if (list->count == list->capacity) {
        list->capacity *= 2;
        double* temp = list->data;
        list->data = malloc(list->capacity * sizeof(double));
        for (int i = 0; i < list->count; ++i) {
            memcpy(&list->data[i], &temp[i], sizeof(double));
        }
        free(temp);

        memcpy(&list->data[list->count], elem, sizeof(double));
        list->count++;
    }
    else {
        memcpy(&list->data[list->count], elem, sizeof(double));
        list->count++;
    }
}

void addStringElem(StringList list, String* str) {
    void* elem = &str;

    if (list->count == list->capacity) {
        list->str = increaseCapacity(list);
        memcpy(&list->str[list->count], elem, sizeof(String));
        list->count++;
    } else {
        memcpy(&list->str[list->count], elem, sizeof(String));
        list->count++;
    }
}

IntList intArrayOf(IntList list, int temp[], int size) {
    list = (IntList)malloc(sizeof(IntArray));
    list->count = 0;
    list->capacity = size;
    list->data = malloc(list->capacity * sizeof(int));
    for (int i = 0; i < size; ++i) {
        int number = temp[i];
        void* elem = &number;
        memcpy(&list->data[list->count], elem, sizeof(int));
        list->count++;
    }
    return list;
}

StringList stringListOf(int size, ...) {
    StringList list = newList(list);

    va_list counter;
    va_start(counter, size);

    unsigned long long int dataSize;

    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacity(list);
        }

        char* arg = va_arg(counter, char*);
        dataSize = strlen(arg);
        list->str[i] = malloc(sizeof(String));
        list->str[i]->data = malloc((dataSize + 1) * sizeof(char));
        list->str[i]->count = dataSize;
        list->str[i]->capacity = dataSize;
        strcpy(list->str[i]->data, arg);
        list->count++;
    }
    va_end(counter);

    return list;
}

DoubleList doubleArrayOf(DoubleList list, double temp[], int size) {
    list = (DoubleList)malloc(sizeof(DoubleArray));
    list->count = 0;
    list->capacity = size;
    list->data = (double*)malloc(list->capacity * sizeof(double));
    for (int i = 0; i < size; ++i) {
        double number = temp[i];
        void* elem = &number;
        memcpy(&list->data[list->count], elem, sizeof(double));
        list->count++;
    }
    return list;
}

void addAllInt(IntList dest, IntList from) {
    int sizeFrom = size(from);
    int sizeDest = size(dest);
    if ((sizeDest + sizeFrom) > dest->capacity) {
        dest->capacity += sizeFrom;
        dest->data = (int*)realloc(dest->data, dest->capacity * sizeof(int));
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(int));
        dest->count += sizeFrom;
    }
    else {
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(int));
        dest->count += sizeFrom;
    }
}

void addAllDouble(DoubleList dest, DoubleList from) {
    int sizeFrom = size(from);
    int sizeDest = size(dest);
    if ((sizeDest + sizeFrom) > dest->capacity) {
        dest->capacity += sizeFrom;
        dest->data = (double*)realloc(dest->data, dest->capacity * sizeof(double));
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(double));
        dest->count += sizeFrom;
    }
    else {
        memcpy(&dest->data[dest->count], from->data, sizeFrom * sizeof(double));
        dest->count += sizeFrom;
    }
}

unsigned int getElemInt(IntList list, int index) {
    if (list->count > 0) {
        if (index < list->count)
            return list->data[index];
    }
    return -INT_MAX;
}

double getElemDouble(DoubleList list, int index) {
    if (list->count > 0) {
        if (index < list->count)
            return list->data[index];
    }
    return -INT_MAX;
}

void setElemInt(IntList list, int index, int num) {
    list->data[index] = num;
}

void setElemDouble(DoubleList list, int index, double num) {
    list->data[index] = num;
}

void removeElemInt(IntList list, int index) {
    if (list->count == 1) {
        free(list->data);
        list->count = 0;
        list->capacity = 20;
        list->data = (int*)malloc(list->capacity * sizeof(int));
        return;
    }
    int* temp = (int*)malloc((list->count - index - 1) * sizeof(int));
    int sizeTemp = list->count - index - 1;
    int counter = index;
    ++counter;
    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->data[counter++];
    }
    memcpy(&list->data[index], temp, sizeTemp * sizeof(int));
    list->count--;
    free(temp);
}

void removeElemDouble(DoubleList list, int index) {
    if (list->count == 1) {
        free(list->data);
        list->count = 0;
        list->capacity = 20;
        list->data = (double*)malloc(list->capacity * sizeof(double));
        return;
    }
    double * temp = (double*)malloc((list->count - index - 1) * sizeof(double));
    unsigned int sizeTemp = list->count - index - 1;
    int counter = index;
    ++counter;
    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->data[counter++];
    }
    memcpy(&list->data[index], temp, sizeTemp * sizeof(double));
    list->count--;
    free(temp);
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
    text = (char*)malloc(count * sizeof(char));
    strcpy(text, "[");
    for (int i = 0; i < size(list) - 1; ++i) {
        sprintf(&text[strlen(text)], "%d,", list->data[i]);
        if (strlen(text) > (int)count * 0.8) {
            count *= 2;
            text = (char*)realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%d", list->data[size(list) - 1]);
    strcat(text, "]");
    return text;
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
        if (strlen(text) > (int)count * 0.8) {
            count *= 2;
            text = (char*)realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%d", list->data[size(list) - 1]);
    strcat(text, "]");
    return text;
}

void printArrayInt(IntList list) {
    printf("%s", "[");
    int counter = size(list);
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%d", list->data[i]);
        else
            printf("%d, ", list->data[i]);
    }
    printf("%s\n", "]");
}

void printArrayDouble(DoubleList list) {
    printf("%s", "[");
    unsigned int counter = list->count;
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%f", list->data[i]);
        else
            printf("%f, ", list->data[i]);
    }
    printf("%s\n", "]");
}

void printArrayString(StringList list) {
    unsigned int counter = list->count;
    printf("%s", "[");
    for (int i = 0; i < counter; ++i) {
        if (i == counter - 1)
            printf("%s", list->str[i]->data);
        else
            printf("%s, ", list->str[i]->data);
    }
    printf("%s\n", "]");
}

void clearInt(IntList list) {
    free(list->data);
    list->count = 0;
    list->capacity = 20;
    list->data = (int*)malloc(list->capacity * sizeof(int));
}

void clearDouble(DoubleList list) {
    free(list->data);
    list->count = 0;
    list->capacity = 20;
    list->data = (double*)malloc(list->capacity * sizeof(double));
}

void deleteArrayInt(IntList list) {
    if (list != NULL) {
        if (list->data != NULL)
            free(list->data);
        free(list);
    }
}

void deleteArrayDouble(DoubleList list) {
    if (list != NULL) {
        if (list->data != NULL)
            free(list->data);
        free(list);
    }
}

void deleteArrayString(StringList list) {
    if (list == NULL) {
        printf("%s\n", "List is NULL.");
        return;
    }

    if (list->str != NULL) {
        for (int i = 0; i < list->count; ++i) {
            if (list->str[i] != NULL) {
                deleteString(list->str[i]);
            }
        }
        free(list->str);
    }
    free(list);
}

void quicksortInt(int* arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    int temp;
    do
    {
        while (j > i)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quicksortInt(arr, i + 1, high);
    if (low < j - 1)
        quicksortInt(arr, low, j);
}

void quicksortDouble(double* arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    float temp;
    do
    {
        while (j > i)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                --j;
                break;
            }
            ++i;
        }
    } while (i < j);

    if (i < high - 1)
        quicksortDouble(arr, i + 1, high);
    if (low < j - 1)
        quicksortDouble(arr, low, j);
}

void sortInt(IntList list) {
    int high = sizeIntArray(list);
    quicksortInt(list->data, 0, high);
}

void sortDouble(DoubleList list) {
    int high = sizeDoubleArray(list);
    quicksortDouble(list->data, 0, high);
}

bool containsInt(IntList list, int num) {
    for (int i = 0; i < sizeIntArray(list); ++i) {
        if (list->data[i] == num)
            return true;
    }
    return false;
}

bool containsDouble(DoubleList list, double num) {
    for (int i = 0; i < sizeDoubleArray(list); ++i) {
        if (fabs(list->data[i] - num) < 0.000001)
            return true;
    }
    return false;
}

int isEmptyInt(IntList list) {
    return list->count == 0 ? true : false;
}
int isEmptyDouble(DoubleList list) {
    return list->count == 0 ? true : false;
}

void reverseArrayInt(IntList list) {
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

void reverseArrayDouble(DoubleList list) {
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




