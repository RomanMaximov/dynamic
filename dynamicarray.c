#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "dynamicarray.h"

void quickSortInt(int*, int, int);
bool binarySearchInt(int elem, const int* arr, int high);

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

void addStrElem(String* str, StringList list) {
    if (list->count == list->capacity) {
        list->str = increaseCapacity(list);
        memcpy(&list->str[list->count], &str, sizeof(String));
        list->count++;
    } else {
        memcpy(&list->str[list->count], &str, sizeof(String));
        list->count++;
    }
}

void addCharArrElem(char* str, StringList list) {
    string elem = stringOf(str);

    if (list->count == list->capacity) {
        list->str = increaseCapacity(list);
        memcpy(&list->str[list->count], &elem, sizeof(String));
        list->count++;
    } else {
        memcpy(&list->str[list->count], &elem, sizeof(String));
        list->count++;
    }
}

IntList listOfInt(IntList list, int num, ...) {
    list = newList(list);

    va_list counter;
    va_start(counter, num);

    for (int i = 0; i < num; ++i) {
        // TODO сделать проверку на превышение capacity
        int arg = va_arg(counter, int);
        list->data[i] = arg;
        list->count++;
    }
    va_end(counter);

    return list;
}

DoubleList listOfDouble(DoubleList list, int num, ...) {
    list = newList(list);

    va_list counter;
    va_start(counter, num);

    for (int i = 0; i < num; ++i) {
        // TODO сделать проверку на превышение capacity
        double arg = va_arg(counter, double);
        list->data[i] = arg;
        list->count++;
    }
    va_end(counter);

    return list;
}

StringList listOfStrLiteral(char* arr, int size, ...) {
    StringList list = newList(list);

    va_list counter;
    va_start(counter, size);

    unsigned long long int dataSize;

    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacity(list);  // TODO сделать общую функцию через дженерик
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

StringList listOfStr(StringList list, int size, ...) {
    list = newList(list);

    va_list counter;
    va_start(counter, size);

    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacity(list);
        }

        string arg = va_arg(counter, string);
        list->str[i] = malloc(sizeof(String));
        list->str[i] = arg;
        list->count++;
    }
    va_end(counter);

    return list;
}

IntList listOfArrInt(IntList list, int* temp, int size) {
    list = malloc(sizeof(IntArray));
    list->count = 0;
    list->capacity = size < 20 ? 20 : size;
    list->data = malloc(list->capacity * sizeof(int));
    for (int i = 0; i < size; ++i) {
        // TODO сделать проверку на превышение capacity
        memcpy(&list->data[list->count], &temp[i], sizeof(int));
        list->count++;
    }
    return list;
}

DoubleList listOfArrDouble(DoubleList list, double* temp, int size) {
    list = malloc(sizeof(DoubleArray));
    list->count = 0;
    list->capacity = size < 20 ? 20 : size;
    list->data = malloc(list->capacity * sizeof(double));
    for (int i = 0; i < size; ++i) {
        // TODO сделать проверку на превышение capacity
        memcpy(&list->data[list->count], &temp[i], sizeof(double));
        list->count++;
    }
    return list;
}

StringList listOfArrChar(StringList list, char* arr[], int size) {
    list = newList(list);

    unsigned long long int dataSize;
    for (int i = 0; i < size; ++i) {
        if (list->count == list->capacity) {
            list->str = increaseCapacity(list);
        }

        char* data = arr[i];
        dataSize = strlen(data);
        list->str[i] = malloc(sizeof(String));
        list->str[i]->data = malloc((dataSize + 1) * sizeof(char));
        list->str[i]->count = dataSize;
        list->str[i]->capacity = dataSize;
        strcpy(list->str[i]->data, data);
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

void addAllStr(StringList dest, StringList from) {
    int sizeFrom = size(from);
    int sizeDest = size(dest);
    if ((sizeDest + sizeFrom) > dest->capacity) {
        dest->capacity += sizeFrom;
        dest->str = realloc(dest->str, dest->capacity * sizeof(String*));
        for (int i = sizeFrom; i < sizeFrom + sizeDest; ++i) {
            dest->str[i] = stringOf(from->str[i]->data);
        }
        dest->count += sizeFrom;
    }
    else {
        int indexFrom = 0;
        for (int i = sizeDest; i < sizeFrom + sizeDest; ++i) {
            dest->str[i] = stringOf(from->str[indexFrom++]->data);
        }
        dest->count += sizeFrom;
    }
}

unsigned int getElemInt(IntList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= list->count) {
        puts("ERROR: Index value out of bound.");
        return EXIT_FAILURE;
    }

    return list->data[index];
}

double getElemDouble(DoubleList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= list->count) {
        puts("ERROR: Index value out of bound.");
        return EXIT_FAILURE;
    }

    return list->data[index];
}

string getElemStr(StringList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return NULL;
    }

    if (index < 0 || index >= list->count) {
        puts("ERROR: Index value out of bound.");
        return NULL;
    }

    return stringOf(list->str[index]->data);
}

void setElemInt(IntList list, int index, int num) {
    list->data[index] = num;
}

void setElemDouble(DoubleList list, int index, double num) {
    list->data[index] = num;
}

bool setElemStr(string str, StringList list, int index) {
    if (list == NULL)
        return false;

    if (index >= list->count) {
        puts("Index value out of bound.");
        return false;
    }

    list->str[index] = stringOf(str->data);

    return true;
}

bool setElemCharArr(char* str, StringList list, int index) {
    if (list == NULL)
        return false;

    if (index >= list->count) {
        puts("Index value out of bound.");
        return false;
    }

    list->str[index] = stringOf(str);

    return true;
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

void removeElemStr(StringList list, int index) {
    if (index >= list->count) {
        puts("Index value out of bound.");
        return;
    }

    if (list->count == 1) {
        free(list->str[0]);
        list->count = 0;
        /*list->capacity = 20;
        list->data = (double*)malloc(list->capacity * sizeof(double));*/
        return;
    }
    String** temp = malloc((list->count - index - 1) * sizeof(String*));
    unsigned int sizeTemp = list->count - index - 1;
    int counter = index;
    ++counter;
    for (int i = 0; i < sizeTemp; ++i) {
        temp[i] = list->str[counter++];
    }
    memcpy(&list->str[index], temp, sizeTemp * sizeof(String));
    list->count--;
    free(temp);
}

void removeAllInt(IntList list1, IntList list2) {
    if (list1 == NULL || list2 == NULL || list2->count > list1->count)
        return;

    int* temp = malloc(list1->count * sizeof(int));
    int* indexList = malloc(list2->count * sizeof(int));
    memcpy(&temp[0], list1->data, list1->count * sizeof(int));

    int j = 0;
    for (int i = 0; i < list2->count; ++i) {
        int index = indexOfInt(list1, list2->data[i]);
        if (index != -1)
            indexList[j++] = index;
    }

    quickSortInt(indexList, 0, j - 1);
    free(list1->data);
    list1->data = malloc(list1->capacity * sizeof(int));

    int index = 0;
    for (int i = 0; i < list1->count; ++i) {
        if (binarySearchInt(i, indexList, j - 1))
            continue;

        list1->data[index] = temp[index];
        ++index;
    }
    list1->count -= j;
    free(indexList);
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
        if (strlen(text) > (unsigned long long int)(count * 0.8)) {
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
        if (strlen(text) > (unsigned long long int)(count * 0.8)) {
            count *= 2;
            text = (char*)realloc(text, count * sizeof(char));
        }
    }

    sprintf(&text[strlen(text)], "%f", list->data[size(list) - 1]);
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
    list->data = malloc(list->capacity * sizeof(int));
}

void clearDouble(DoubleList list) {
    free(list->data);
    list->count = 0;
    list->capacity = 20;
    list->data = malloc(list->capacity * sizeof(double));
}

void clearStrList(StringList list) {
    free(list->str);
    list->count = 0;
    list->capacity = 20;
    list->str = malloc(list->capacity * sizeof(String*));
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

void quickSortInt(int* arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    int temp;
    do {
        while (j > i) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (arr[i] > arr[j]) {
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
        quickSortInt(arr, i + 1, high);
    if (low < j - 1)
        quickSortInt(arr, low, j);
}

void quickSortDouble(double* arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    double temp;
    do {
        while (j > i) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (arr[i] > arr[j]) {
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
        quickSortDouble(arr, i + 1, high);
    if (low < j - 1)
        quickSortDouble(arr, low, j);
}

void quickSortStr(String** strList, int low, int high)
{
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareTo(strList[i], strList[j]) == 1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareTo(strList[i], strList[j]) == 1) {
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
        quickSortStr(strList, i + 1, high);
    if (low < j - 1)
        quickSortStr(strList, low, j);
}

void quickSortReverseStr(String** strList, int low, int high)
{
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareTo(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareTo(strList[i], strList[j]) == -1) {
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
        quickSortReverseStr(strList, i + 1, high);
    if (low < j - 1)
        quickSortReverseStr(strList, low, j);
}

void sortInt(IntList list) {
    if (list == NULL)
        return;

    int high = sizeIntArray(list);
    quickSortInt(list->data, 0, high);
}

void sortDouble(DoubleList list) {
    if (list == NULL)
        return;

    int high = sizeDoubleArray(list);
    quickSortDouble(list->data, 0, high);
}

void sortStrList(StringList list) {
    if (list == NULL)
        return;

    int high = sizeStringArray(list);
    quickSortStr(list->str, 0, high);
}

void sortReverseStrList(StringList list) {
    if (list == NULL)
        return;

    int high = sizeStringArray(list);
    quickSortReverseStr(list->str, 0, high);
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

bool containsStr(StringList list, string str) {
    if (list == NULL)
        return false;

    for (int i = 0; i < list->count; ++i) {
        if (compareTo(list->str[i], str) == 0)
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

bool containsAllStr(StringList list1, StringList list2) {
    if (list1 == NULL || list2 == NULL || list2->count > list1->count)
        return false;

    for (int i = 0; i < list2->count; ++i) {
        if (indexOfStrList(list1, list2->str[i]) == -1)
            return false;
    }

    return true;
}

bool isEmptyInt(IntList list) {
    return list != NULL && list->count == 0;
}

bool isEmptyDouble(DoubleList list) {
    return list != NULL && list->count == 0;
}

bool isEmptyStrList(StringList list) {
    return list != NULL && list->count == 0;
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

void reverseArrayStr(StringList list) {
    String** start = list->str;
    String** end = list->str + (list->count - 1);
    String* temp;
    while (start <= end) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

bool isEqualStrLists(StringList list1, StringList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->count != list2->count)
        return false;

    unsigned int counter = list1->count;
    for (int i = 0; i < counter; ++i) {
        char* temp1 = list1->str[i]->data;
        char* temp2 = list2->str[i]->data;

        if (strcmp(temp1, temp2) != 0)
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

int indexOfDouble(DoubleList list, double elem) {
    if (list == NULL)
        return -1;

    for (int i = 0; i < list->count; ++i) {
        if (fabs(list->data[i] - elem) < 0.000001)
            return i;
    }
    return -1;
}

int indexOfStrList(StringList list, string str) {
    if (list == NULL)
        return -1;

    for (int i = 0; i < list->count; ++i) {
        if (compareTo(list->str[i], str) == 0)
            return i;
    }
    return -1;
}

bool binarySearchInt(int elem, const int* arr, int high) {
    int low, middle;
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


