//
// Created by Roman Maximov on 12.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strarraylist.h"
#include "../util/arraylistutil.h"


typedef struct InnerStrList {
    int count;
    struct String** data;
    int capacity;
} InnerStrList;

typedef String* string;


// private funcs prototypes
static String** increaseCapacity(StrList list);
static int compareStr(string s1, string s2);
static void quickSort(String** strList, int low, int high);
static void quickSortReverse(String** strList, int low, int high);
static bool isFull(StrList list);
static int compareInt(const void* elem1, const void* elem2);
static void checkCapacity(char* text, int* count, int strLength);


void addStrList(StrList list, string str) {
    if (list == NULL) return;

    if (str == NULL) {
        if (isFull(list))
            list->pf->data = increaseCapacity(list);

        list->pf->data[list->pf->count] = NULL;
        list->pf->count++;
    } else {
        if (isFull(list)) {
            list->pf->data = increaseCapacity(list);
            list->pf->data[list->pf->count] = strOf(str->pf->data);
            list->pf->count++;
        } else {;
            list->pf->data[list->pf->count] = strOf(str->pf->data);
            list->pf->count++;
        }
    }
}

void addCharArrList(StrList list, char* str) {
    if (str == NULL || list == NULL) return;

    if (isFull(list)) {
        list->pf->data = increaseCapacity(list);
        list->pf->data[list->pf->count] = strOf(str);
        list->pf->count++;
    } else {
        list->pf->data[list->pf->count] = strOf(str);
        list->pf->count++;
    }
}

void addAllStrList(StrList dest, void* source) {
    if (dest == NULL || source == NULL) return;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList from = (StrList) ctx->collection;
        if (from == NULL) return;
        for (int i = 0; i < from->pf->count; ++i)
            addStrList(dest, from->pf->data[i]);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList from = (StrLinkedList) ctx->collection;
        if (from == NULL) return;

        StrNode current = from->pf->begin;
        while (current != NULL) {
            addStrList(dest, current->data);
            current = current->next;
        }
    }

    if (ctx->type == STR_SET) {
        StrSet from = (StrSet) ctx->collection;
        if (from == NULL) return;

        StrList temp = pr_initLs_(temp, NULL);
        setToStrList(from, temp);
        for (int i = 0; i < from->pf->count; ++i)
            addStrList(dest, temp->pf->data[i]);

        temp->delete(&temp);
    }
}

string getStrList(StrList list, int index) {
    if (list == NULL) {
        puts("ERROR: List is null.");
        return NULL;
    }

    if (index < 0 || index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return NULL;
    }

    return strOf(list->pf->data[index]->pf->data);
}

bool setStrList(StrList list, int index, string str) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index]->delete(&list->pf->data[index]);
    list->pf->data[index] = str;
    return true;
}

bool setCharArrList(StrList list, int index, char* str) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    list->pf->data[index] = strOf(str);
    return true;
}

int indexOfStrList(StrList list, string str) {
    if (list == NULL || str == NULL)
        return -1;

    for (int i = 0; i < list->pf->count; ++i) {
        if (list->pf->data[i] == NULL)
            continue;

        if (compareStr(list->pf->data[i], str) == 0)
            return i;
    }
    return -1;
}

void sortStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = list->pf->count;
    quickSort(list->pf->data, 0, high);
}

void sortStrListReverse(StrList list) {
    if (isEmptyStrList(list))
        return;

    int high = sizeStrList(list);
    quickSortReverse(list->pf->data, 0, high);
}

void clearStrList(StrList list) {
    if (isEmptyStrList(list))
        return;

    free(list->pf->data);
    list->pf->count = 0;
    list->pf->capacity = 20;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
}

bool containsStrList(StrList list, string str) {
    if (list == NULL || str->isEmpty(str))
        return false;

    for (int i = 0; i < list->pf->count; ++i) {
        if (compareStr(list->pf->data[i], str) == 0)
            return true;
    }
    return false;
}

bool containsAllStrList(StrList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        StrSet set = pr_initSs_(set, list->values);
        for (int i = 0; i < list2->pf->count; ++i) {
            if (!containsKeyStr(set, list2->pf->data[i])) {
                set->delete(&set);
                return false;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        if (list2->pf->count > list->pf->count)
            return false;

        if (list2->pf->count == 0) return true;

        StrSet set = pr_initSs_(set, list->values);
        StrNode current = list2->pf->begin;
        while (current != NULL) {
            if (!containsKeyStr(set, current->data)) {
                set->delete(&set);
                return false;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count > list->pf->count)
            return false;

        if (setFrom->pf->count == 0) return true;

        StrList strList = pr_initLs_(strList, setFrom->values);
        StrSet setTemp = pr_initSs_(setTemp, list->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (!containsKeyStr(setTemp, strList->pf->data[i])) {
                setTemp->delete(&setTemp);
                strList->delete(&strList);
                return false;
            }
        }
        setTemp->delete(&setTemp);
        strList->delete(&strList);
    }

    return true;
}

bool containsAnyStrList(StrList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;

    if (ctx->type == STR_LIST) {
        StrList list2 = (StrList) ctx->collection;
        StrSet set = pr_initSs_(set, list->values);

        for (int i = 0; i < list2->pf->count; ++i) {
            if (containsKeyStr(set, list2->pf->data[i])) {
                set->delete(&set);
                return true;
            }
        }
        set->delete(&set);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList list2 = (StrLinkedList) ctx->collection;
        StrSet set = pr_initSs_(set, list->values);
        StrNode current = list2->pf->begin;

        while (current != NULL) {
            if (containsKeyStr(set, current->data)) {
                set->delete(&set);
                return true;
            }
            current = current->next;
        }
        set->delete(&set);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        StrList strList = pr_initLs_(strList, setFrom->values);
        StrSet setTemp = pr_initSs_(setTemp, list->values);

        for (int i = 0; i < setFrom->pf->count; ++i) {
            if (containsKeyStr(setTemp, strList->pf->data[i])) {
                setTemp->delete(&setTemp);
                strList->delete(&strList);
                return true;
            }
        }
        setTemp->delete(&setTemp);
        strList->delete(&strList);
    }

    return false;
}

bool removeStrList(StrList list, int index) {
    if (list == NULL) return false;

    if (index < 0 || index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    if (list->pf->count == 1 && index == 0) {
        list->pf->data[index]->delete(&list->pf->data[index]);
        list->pf->count = 0;
        list->pf->data[index] = NULL;
        return true;
    }

    list->pf->data[index]->delete(&list->pf->data[index]);
    list->pf->data[index] = NULL;
    String** temp = list->pf->data;

    int sizeTemp = list->pf->count - 1;
    list->pf->data = malloc(sizeTemp * sizeof(String*));

    int counter = 0;
    for (int i = 0; i < list->pf->count; ++i) {
        if (temp[i] == NULL) continue;

        list->pf->data[counter] = temp[i];
        ++counter;
    }

    list->pf->count--;
    free(temp);

    return true;
}

bool removeAllStrList(StrList list, void* source) {
    if (list == NULL || source == NULL) return false;

    Ctx ctx = (Ctx) source;
    StrList tempList;

    if (ctx->type == STR_LIST) {
        tempList = subtractStrList(list, (void*) ctx);
    }

    if (ctx->type == STR_LL) {
        tempList = subtractStrList(list, (void*) ctx);
    }

    if (ctx->type == STR_SET) {
        tempList = subtractStrList(list, (void*) ctx);
    }

    for (int i = 0; i <list->pf->count; ++i) {
        if (list->pf->data[i] != NULL)
            list->pf->data[i]->delete(&list->pf->data[i]);
    }
    for (int i = 0; i <tempList->pf->count; ++i) {
        list->pf->data[i] = strOf(tempList->pf->data[i]->pf->data);
    }

    list->pf->count = tempList->pf->count;
    tempList->delete(&tempList);

    return true;
}

StrList subtractStrList(StrList list, void* source) {
    if (isEmptyStrList(list)) {
        StrList temp = NULL;
        return pr_initLs_(temp, NULL);
    }

    if (source == NULL) {
        StrList temp = pr_initLs_(temp, list->values);
        return temp;
    }

    Ctx ctx = (Ctx) source;
    StrList tempList = pr_initLs_(tempList, NULL);

    if (ctx->type == STR_LIST) {
        StrList listSource = (StrList) ctx->collection;
        if (listSource->pf->count == 0) {
            StrList temp = pr_initLs_(temp, list->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            string temp = list->pf->data[i];
            if (list->pf->data[i] == NULL) continue;
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == STR_LL) {
        StrLinkedList listSource = (StrLinkedList) ctx->collection;
        if (listSource->pf->count == 0) {
            StrList temp = pr_initLs_(temp, list->values);
            return temp;
        }

        StrSet setFrom = pr_initSs_(setFrom, listSource->values);
        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
        setFrom->delete(&setFrom);
    }

    if (ctx->type == STR_SET) {
        StrSet setFrom = (StrSet) ctx->collection;
        if (setFrom->pf->count == 0) {
            StrList temp = pr_initLs_(temp, list->values);
            return temp;
        }

        for (int i = 0; i < list->pf->count; ++i) {
            if (!setFrom->contains(setFrom, list->pf->data[i]))
                tempList->add(tempList, list->pf->data[i]);
        }
    }

    return tempList;
}

bool isEmptyStrList(StrList list) {
    return list == NULL || list->pf->count == 0;
}

void reverseStrList(StrList list) {
    if (list == NULL || list->pf == NULL || list->pf->data == NULL) {
        return;
    }

    int end = list->pf->count - 1;
    string temp = NULL;
    for (int i = 0; i < list->pf->count / 2; ++i, --end) {
        temp = list->pf->data[i];
        list->pf->data[i] = list->pf->data[end];
        list->pf->data[end] = temp;
    }
}

bool isEqualsStrList(StrList list1, StrList list2) {
    if (list1 == NULL || list2 == NULL || list1->pf->count != list2->pf->count)
        return false;

    int counter = list1->pf->count;
    for (int i = 0; i < counter; ++i) {
        char* temp1 = list1->pf->data[i]->pf->data;
        char* temp2 = list2->pf->data[i]->pf->data;

        if (strcmp(temp1, temp2) != 0)
            return false;
    }

    return true;
}

int sizeStrList(StrList list) {
    return list->pf->count;
}

string joinStrList(StrList list, char* delimeter) {
    if (list == NULL || list->pf == NULL || list->pf->data == NULL) {
        return NULL;
    }

    int indexList = 0;
    int sizeNewStr = 0;
    int delimeterSize = (int) strlen(delimeter);
    int delimeterCount = list->pf->count - 1;
    for (int i = 0; i < list->pf->count; ++i) {
        sizeNewStr += list->pf->data[i]->pf->count;
    }
    sizeNewStr = sizeNewStr + 1 + (delimeterCount * (int) strlen(delimeter));

    char* temp = malloc(++sizeNewStr * sizeof(char));

    for (int i = 0; i < list->pf->count; ++i) {
        char currentStr[list->pf->data[i]->pf->count + 1];
        strcpy(currentStr, list->pf->data[i]->pf->data);
        for (int j = 0; j < list->pf->data[i]->pf->count; ++j) {
            temp[indexList++] = currentStr[j];
        }

        if (i == list->pf->count - 1)
            continue;

        strcpy(temp + indexList, delimeter);
        indexList += delimeterSize;
    }
    temp[indexList] = '\0';

    string s = strOf(temp);
    free(temp);
    return s;
}

string toStrStrList(StrList list) {
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
        checkCapacity(text, &count, list->pf->data[i]->pf->count);
        sprintf(&text[strlen(text)], "%s,", list->pf->data[i]->pf->data);
    }

    checkCapacity(text, &count, list->pf->data[list->pf->count - 1]->pf->count);
    sprintf(&text[strlen(text)], "%s", list->pf->data[list->pf->count - 1]->pf->data);
    strcat(text, "]");

    string s = strOf(text);
    free(text);

    return s;
}

void printStrList(StrList list) {
    if (list == NULL) return;

    int counter = list->pf->count;
    printf("%s", "[");
    for (int i = 0; i < counter; ++i) {
        string temp = list->pf->data[i];
        if (i == counter - 1) {
            if (list->pf->data[i] != NULL && list->pf->data[i]->pf->data == NULL)
                printf("%s", "null");
            else if (list->pf->data[i] == NULL)
                continue;
            else
                printf("%s", list->pf->data[i]->pf->data);
        } else {
            if (list->pf->data[i] != NULL && list->pf->data[i]->pf->data == NULL)
                printf("%s, ", "null");
            else if (list->pf->data[i] == NULL)
                continue;
            else
                printf("%s, ", list->pf->data[i]->pf->data);
        }
    }
    printf("%s\n", "]");
}

void deleteStrList(StrList* list) {
    if (list == NULL || *list == NULL) {
        printf("%s\n", "List is NULL.");
        return;
    }

    if ((*list)->pf->data != NULL) {
        for (int i = 0; i < (*list)->pf->count; ++i) {
            if ((*list)->pf->data[i] != NULL) {
                (*list)->pf->data[i]->delete(&(*list)->pf->data[i]);
            }
        }
    }

    free((*list)->pf);
    free(*list);
    *list = NULL;
}

// ===================== private funcs =======================

static String** increaseCapacity(StrList list) {
    int oldSize = list->pf->count;
    list->pf->capacity *= 2;

    String** temp = list->pf->data;
    list->pf->data = malloc(list->pf->capacity * sizeof(String*));
    assert(list->pf->data != NULL);

    for (int i = 0; i < list->pf->capacity; ++i)
        list->pf->data[i] = NULL;

    for (int i = 0; i < oldSize; ++i)
        list->pf->data[i] = temp[i];

    return list->pf->data;
}

static int compareStr(string s1, string s2) {
    int result = strcmp(s1->pf->data, s2->pf->data);
    return result;
}

static void quickSort(String** strList, int low, int high)
{
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareStr(strList[i], strList[j]) == 1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) == 1) {
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
        quickSort(strList, i + 1, high);
    if (low < j - 1)
        quickSort(strList, low, j);
}

static void quickSortReverse(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareStr(strList[i], strList[j]) == -1) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) == -1) {
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
        quickSortReverse(strList, i + 1, high);
    if (low < j - 1)
        quickSortReverse(strList, low, j);
}

static bool isFull(StrList list) {
    return list->pf->count >= list->pf->capacity / 5 * 4;
}

static int compareInt(const void* elem1, const void* elem2) {
    return (*(int*)elem1 - *(int*)elem2);
}

static void checkCapacity(char* text, int* count, int strLength) {
    if (strLength >= *count - strlen(text)) {
        *count = (*count + strLength) * 2;
        text = realloc(text, *count * sizeof(char));
        assert(text != NULL);
    }
}