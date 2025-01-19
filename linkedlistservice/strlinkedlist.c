//
// Created by Roman Maximov on 16.11.2024.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlinkedlist.h"

// structures
typedef struct NodeStr {
    string data;
    struct NodeStr* next;
    struct NodeStr* prev;
} NodeStr;

typedef struct InnerStrLL {
    int count;
    int index;
    NodeStr* nodes;
    NodeStr* begin;
    NodeStr* end;
} InnerStrLL;

/*typedef struct String {
    int count;
    char* data;
    int capacity;
} String;*/

typedef struct InnerStrList {
    int count;
    String** str;
    int capacity;
} InnerStrList;

typedef struct NodeStr NodeStr;
typedef NodeStr* StrNode;
typedef String* string;
typedef ArrayListStr* StrList;


// prototypes
static void fillNodeStr(StrNode node, char* s, int* index);
static void quickSortStr(String** strList, int low, int high);
static void quickSortStrReverse(String** strList, int low, int high);
static bool binarySearchStr(string s, String** strList, int high);
static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index);
static void deleteFirstNodeStr(StrLinkedList list, StrNode current);
static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous);
static void copyLLToStrList(StrLinkedList strLL, StrList strList);
static StrLinkedList copyStrLL(StrLinkedList list);
static int compareStr(string s1, string s2);


// funcs
void addStrElemLL(StrLinkedList list, string s) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->pf->end;
    int* index = &list->pf->index;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, s->data, index);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, s->data, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

void addArrCharLL(StrLinkedList list, char* arr) {
    StrNode newNodeEnd = NULL;
    StrNode newNode = NULL;
    StrNode current = list->pf->end;
    int* index = &list->pf->index;

    if (list->pf->count == 0) {
        newNode = malloc(sizeof(NodeStr));
        if (newNode != NULL) {
            fillNodeStr(newNode, arr, index);
        }

        newNode->next = list->pf->nodes;
        list->pf->nodes = newNode;
        list->pf->begin = list->pf->nodes;
        list->pf->end = newNode;
        list->pf->begin = newNode;
    } else {
        newNodeEnd = malloc(sizeof(NodeStr));
        if (newNodeEnd != NULL) {
            fillNodeStr(newNodeEnd, arr, index);
        }

        current->next = newNodeEnd;
        newNodeEnd->prev = current;
        list->pf->end = newNodeEnd;
    }

    list->pf->count++;
}

bool setStrElemLL(StrLinkedList list, int index, string s) {
    if (list == NULL)
        return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    int tempIndex = 0;
    StrNode current = list->pf->begin;
    while (current != NULL) {
        if (index == tempIndex) {
            current->data = s;
            return true;
        }
        ++tempIndex;
        current = current->next;
    }
    return false;
}

void addAllStrElemLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return;

    StrNode current2 = list2->pf->nodes;
    while (current2 != NULL) {
        addStrElemLL(list1, current2->data);
        current2 = current2->next;
    }
}

string getStrElemLL(StrLinkedList list, int index) {
    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return NULL;
    }

    int tempIndex = 0;
    StrNode current = list->pf->nodes;
    while (current != NULL) {
        if (tempIndex == index)
            return current->data;

        ++tempIndex;
        current = current->next;
    }
    return NULL;
}

void sortStrLL(StrLinkedList list) {
    StrList strList = newStrList(strList);
    StrNode current = list->pf->begin;
    StrNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        addStrList(strList, current->data);
        current = current->next;
    }

    quickSortStr(strList->pf->str, 0, strList->pf->count);

    index = 0;
    while (temp != NULL) {
        temp->data = stringOf(strList->pf->str[index++]->data);
        temp = temp->next;
    }
    deleteStrList(&strList);
}

void sortStrLLReverse(StrLinkedList list) {
    StrList strList = newStrList(strList);
    StrNode current = list->pf->begin;
    StrNode temp = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        addStrList(strList, current->data);
        current = current->next;
    }

    quickSortStrReverse(strList->pf->str, 0, strList->pf->count);

    index = 0;
    while (temp != NULL) {
        temp->data = stringOf(strList->pf->str[index++]->data);
        temp = temp->next;
    }
    deleteStrList(&strList);
}

int indexOfStrLL(StrLinkedList list, string s) {
    if (list == NULL)
        return -1;

    StrNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        if (compareStr(s, current->data) == 1)
            return index;

        current = current->next;
        ++index;
    }
    return -1;
}

void clearStrLL(StrLinkedList list) {
    if (list == NULL)
        return;

    StrNode current = list->pf->begin;
    StrNode temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->next;

        deleteString(&(temp->data));
        free(temp);
    }

    list->pf->count = 0;
    list->pf->index = 0;
    list->pf->begin = NULL;
    list->pf->end = NULL;
    list->pf->nodes = NULL;
}

bool containsStrLL(StrLinkedList list, string s) {
    if (list == NULL || isEmptyStr(s)) return false;

    StrNode current = list->pf->begin;
    while (current != NULL) {
        if (compareStr(s, current->data) == 1)
            return true;

        current = current->next;
    }
    return false;
}

bool containsAllStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL || list2->pf->count > list1->pf->count) return false;

    StrList tempList = newStrList(tempList);
    StrNode current = list1->pf->begin;
    StrNode current2 = list2->pf->begin;

    while (current != NULL) {
        addStrList(tempList, current->data);
        current = current->next;
    }

    quickSortStr(tempList->pf->str, 0, tempList->pf->count);

    while (current2 != NULL) {
        if (!binarySearchStr(current2->data, tempList->pf->str, list1->pf->count)) {
            deleteStrList(&tempList);
            return false;
        }

        current2 = current2->next;
    }

    deleteStrList(&tempList);
    return true;
}

bool containsAnyStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL) return false;

    StrList tempList = newStrList(tempList);
    StrNode current = list1->pf->begin;
    StrNode current2 = list2->pf->begin;

    while (current != NULL) {
        addStrList(tempList, current->data);
        current = current->next;
    }

    quickSortStr(tempList->pf->str, 0, tempList->pf->count);

    while (current2 != NULL) {
        if (binarySearchStr(current2->data, tempList->pf->str, list1->pf->count)) {
            deleteStrList(&tempList);
            return true;
        }

        current2 = current2->next;
    }

    deleteStrList(&tempList);
    return false;
}

bool removeStrLL(StrLinkedList list, int index) {
    if (list == NULL) return false;

    if (index >= list->pf->count) {
        printf("Index %d out of bounds for length %d\n", index, list->pf->count);
        return false;
    }

    StrNode current = list->pf->begin;
    StrNode previous = NULL;
    StrNode temp = NULL;

    if (list->pf->count == 1) {
        temp = list->pf->begin;
        list->pf->nodes = NULL;
        list->pf->begin = NULL;
        list->pf->end = NULL;
        list->pf->count = 0;
        list->pf->index = 0;
        free(temp);
        return true;
    }

    return removeNodeStr(list, current, previous, index);
}

bool removeAllStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 ==NULL) return false;

    int listSize = list1->pf->count;
    StrList tempList = newStrList(tempList);
    StrList filtered = newStrList(filtered);
    StrList tempForBS = newStrList(tempForBS);

    copyLLToStrList(list1, tempList);
    copyLLToStrList(list1, tempForBS);
    quickSortStr(tempForBS->pf->str, 0, listSize);

    StrNode current2 = list2->pf->begin;
    while (current2 != NULL) {
        bool isExist = binarySearchStr(current2->data, tempForBS->pf->str, listSize);
        if (isExist)
            addStrList(filtered, current2->data);

        current2 = current2->next;
    }

    clearStrLL(list1);

    quickSortStr(filtered->pf->str, 0, filtered->pf->count);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearchStr(tempList->pf->str[i], filtered->pf->str, filtered->pf->count))
            continue;

        addStrElemLL(list1, tempList->pf->str[i]);
    }

    deleteStrList(&tempForBS);
    deleteStrList(&filtered);
    deleteStrList(&tempList);

    return true;
}

StrLinkedList subtractStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (isEmptyStrLL(list1)) {
        StrLinkedList temp = NULL;
        return newStrLinkedList(temp);
    }

    if (isEmptyStrLL(list2)) {
        return copyStrLL(list1);
    }

    int listSize = list1->pf->count;
    StrList tempList = newStrList(tempList);
    StrList filtered = newStrList(filtered);
    StrList tempForBS = newStrList(tempForBS);

    copyLLToStrList(list1, tempList);
    copyLLToStrList(list1, tempForBS);
    quickSortStr(tempForBS->pf->str, 0, listSize);

    StrNode current2 = list2->pf->begin;
    while (current2 != NULL) {
        bool isExist = binarySearchStr(current2->data, tempForBS->pf->str, listSize);
        if (isExist)
            addStrList(filtered, current2->data);

        current2 = current2->next;
    }

    StrLinkedList newLL = newStrLinkedList(newLL);

    quickSortStr(filtered->pf->str, 0, filtered->pf->count);
    for (int i = 0; i < listSize; ++i) {
        if (binarySearchStr(tempList->pf->str[i], filtered->pf->str, filtered->pf->count))
            continue;

        addStrElemLL(list1, tempList->pf->str[i]);
    }

    deleteStrList(&tempForBS);
    deleteStrList(&filtered);
    deleteStrList(&tempList);

    return newLL;
}

void reverseStrLL(StrLinkedList list) {
    StrList tempList = newStrList(tempList);

    copyLLToStrList(list, tempList);
    reverseStrList(tempList);

    StrNode current = list->pf->begin;
    int index = 0;
    while (current != NULL) {
        free(current->data);
        current->data = stringOf(tempList->pf->str[index]->data);
        current = current->next;
        ++index;
    }

    deleteStrList(&tempList);
}

int sizeStrLL(StrLinkedList list) {
    return list->pf->count;
}

bool isEmptyStrLL(StrLinkedList list) {
    return list == NULL || list->pf->count == 0;
}

bool isEqualListsStrLL(StrLinkedList list1, StrLinkedList list2) {
    if (list1 == NULL || list2 == NULL)
        return false;

    if (list1->pf->count != list2->pf->count)
        return false;

    StrNode current1 = list1->pf->begin;
    StrNode current2 = list2->pf->begin;

    while (current1 != NULL) {
        if (compareStr(current1->data, current2->data) != 0)
            return false;

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

StrLinkedList emptyIfNullStrLL(StrLinkedList list) {
    return list == NULL ? newStrLinkedList(list) : list;
}

void printStrLL(StrLinkedList list) {
    if (list == NULL || list->pf == NULL) return;

    StrNode current = list->pf->begin;
    printf("%s", "[");
    while (current != NULL) {
        if (current->data == NULL || current->data->data == NULL) {
            if (current->next == NULL)
                printf("%s", "null");
            else
                printf("%s, ", "null");

            current = current->next;
            continue;
        }

        if (current->next == NULL)
            printf("%s", current->data->data);
        else
            printf("%s, ", current->data->data);
        current = current->next;
    }
    printf("%s\n", "]");
}

void deleteStrLL(StrLinkedList* list) {
    if (list == NULL || *list == NULL) return;

    if ((*list)->pf != NULL) {
        StrNode current = (*list)->pf->nodes;
        StrNode temp = NULL;

        while (current != NULL) {
            temp = current;
            current->prev = NULL;
            current = current->next;

            if (temp->data != NULL)
                deleteString(&(temp->data));

            free(temp);
        }

        free((*list)->pf);
    }

    free(*list);
    *list = NULL;
}

// ===================== private funcs =======================

static bool removeNodeStr(StrLinkedList list, StrNode current, StrNode previous, int index) {
    if (index == 0) {
        deleteFirstNodeStr(list, current);
        return true;
    } else {
        previous = list->pf->begin;
        previous->prev = NULL;
        current = current->next;
        current->prev = previous;

        int tempIndex = 1;
        while (current != NULL && tempIndex != index) {
            previous = current;
            current = current->next;
            current->prev = previous;
            ++tempIndex;
        }

        if (current == NULL) return false;

        deleteNodeStr(list, current, previous);

        return true;
    }
}

static void deleteFirstNodeStr(StrLinkedList list, StrNode current) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    current->prev = NULL;
    list->pf->nodes = current;
    list->pf->begin = current;
    list->pf->count--;
    list->pf->index--;
    deleteString(&(temp->data));
    free(temp);
}

static void deleteNodeStr(StrLinkedList list, StrNode current, StrNode previous) {
    StrNode temp = NULL;

    temp = current;
    current = current->next;
    if (current != NULL)
        current->prev = previous;
    else
        list->pf->end = previous;

    previous->next = current;
    list->pf->count--;
    list->pf->index--;
    deleteString(&(temp->data));
    free(temp);
}

static void quickSortStr(String** strList, int low, int high) {
    int i = low;
    int j = high - 1;
    String* temp;
    do {
        while (j > i) {
            if (compareStr(strList[i], strList[j]) > 0) {
                temp = strList[i];
                strList[i] = strList[j];
                strList[j] = temp;
                ++i;
                break;
            }
            --j;
        }
        while (i < j) {
            if (compareStr(strList[i], strList[j]) > 0) {
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

 static void quickSortStrReverse(String** strList, int low, int high) {
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
        quickSortStrReverse(strList, i + 1, high);
    if (low < j - 1)
        quickSortStrReverse(strList, low, j);
}

static bool binarySearchStr(string s, String** strList, int high) {
    int low, middle;
    --high;
    low = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (compareStr(s, strList[middle]) < 0)
            high = middle - 1;
        else if (compareStr(s, strList[middle]) > 0)
            low = middle + 1;
        else
            return true;
    }
    return false;
}

static void fillNodeStr(StrNode node, char* s, int* index) {
    string temp = stringOf(s);
    node->data = temp;
    node->next = NULL;
    node->prev = NULL;
    ++(*index);
}

static void copyLLToStrList(StrLinkedList strLL, StrList strList) {
    StrNode current = strLL->pf->begin;
    while (current != NULL) {
        addStrList(strList, current->data);
        current = current->next;
    }
}

static StrLinkedList copyStrLL(StrLinkedList list) {
    StrLinkedList temp = newStrLinkedList(temp);
    StrNode current = list->pf->begin;

    while (current != NULL) {
        addStrElemLL(temp, current->data);
        current = current->next;
    }
    return temp;
}

static int compareStr(string s1, string s2) {
    int result = strcmp(s1->data, s2->data);
    return result;
}
