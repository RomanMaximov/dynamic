#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "dynamicarray.h"



StrStrMap newStrStrMap(StrStrMap map) {
    map = malloc(sizeof(StrStrTreeMap));
    map->count = 0;
    map->data = NULL;

    return map;
}

int sizeStrStrMap(StrStrMap map) {
    return (int)map->count;
}

void addKeyToList(StrStrTree* data, StringList list) {
    addStrElem(data->key, list);
}

void addValueToList(StrStrTree** data, StringList list) {
    addStrElem((*data)->value, list);
}

void getKeyInOrder(StrStrTree* data, StringList list) {
    if (data != NULL) {
        getKeyInOrder(data->left, list);
        addKeyToList(data, list);
        getKeyInOrder(data->right, list);
    }
}

StringList getKeyList(StrStrMap map) {
    StringList keyList = newList(keyList);
    if (map->data != NULL && keyList != NULL) {
        getKeyInOrder(map->data, keyList);
    }
    return keyList;
}

void getValueInOrder(StrStrTree** data, StringList list) {
    if (*data != NULL) {
        getValueInOrder(&(*data)->left, list);
        addValueToList(data, list);
        getValueInOrder(&(*data)->right, list);
    }
}

StringList getValueList(StrStrMap map) {
    StringList valueList = newList(valueList);
    if (map->data != NULL && valueList != NULL) {
        getValueInOrder(&map->data, valueList);
    }
    return valueList;
}

int keySearch(string str, StringList keyList, int high)
{
    int low, middle;
    low = 0;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (strcmp(str->data, keyList->str[middle]->data) == -1)
            high = middle - 1;
        else if (strcmp(str->data, keyList->str[middle]->data) == 1)
            low = middle + 1;
        else
            return middle;
    }
    return -1;
}

void insertEntry(StrStrTree** data, string key, string value, unsigned int* counter) {
    if (*data == NULL) {
        *data = (StrStrTree*) malloc(sizeof (StrStrTree));
        (*data)->key = key;
        (*data)->value = value;
        (*data)->left = NULL;
        (*data)->right = NULL;
        (*counter)++;
    } else {
        int cmp = strcmp(key->data, (*data)->key->data);
        if (cmp == 0) {
            free((*data)->value->data);
            free((*data)->value);
            (*data)->value = value;
        } else if (cmp < 0) {
            insertEntry(&((*data)->left), key, value, counter);
        } else {
            insertEntry(&((*data)->right), key, value, counter);
        }
    }
}

bool put(StrStrMap map, string key, string value) {
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return false;
    }

    if (key == NULL) {
        printf("%s\n", "Key is NULL.");
        return false;
    }

    insertEntry(&map->data, key, value, &map->count);

    return true;
}

string getValue(StrStrTree** data, char* key) {
    if (*data == NULL)
        return NULL;

    int cmp = strcmp(key, (*data)->key->data);
    if (cmp == 0) {
        return (*data)->value;
    } else if (cmp < 0) {
        return getValue(&((*data)->left), key);
    } else {
        return getValue(&((*data)->right), key);
    }
}

string get(StrStrMap map, string key) {
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return false;
    }

    if (key == NULL) {
        printf("%s\n", "Key is NULL.");
        return false;
    }

    return getValue(&map->data, key->data);
}

void printInOrder(StrStrTree* data, unsigned int* counter) {
    if (data != NULL) {
        printInOrder(data->left, counter);
        printf("%s%s%s%s%s", "{", data->key->data, ":", data->value->data, "}");
        if (*counter - 1 != 0) {
            printf("%s", ",");
            --(*counter);
        }
        printInOrder(data->right, counter);
    }
}

void printMap(StrStrMap map){
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return;
    }

    printf("%s", "[");
    printInOrder(map->data, &map->count);
    printf("%s", "]");
    puts("");
}

bool isKey(StrStrTree** data, char* key) {
    if (*data == NULL)
        return NULL;

    int cmp = strcmp(key, (*data)->key->data);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        return getValue(&((*data)->left), key);
    } else {
        return getValue(&((*data)->right), key);
    }
}

bool containsKey(StrStrMap map, string key) {
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return false;
    }

    if (key == NULL) {
        printf("%s\n", "Key is NULL.");
        return false;
    }

    return isKey(&map->data, key->data);
}

bool isValue(StrStrTree** data, char* value) {
    if (*data == NULL)
        return NULL;

    int cmp = strcmp(value, (*data)->value->data);
    if (cmp == 0) {
        return true;
    } else if (cmp < 0) {
        return getValue(&((*data)->left), value);
    } else {
        return getValue(&((*data)->right), value);
    }
}

bool containsValue(StrStrMap map, string value) {
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return false;
    }

    if (value == NULL) {
        printf("%s\n", "Value is NULL.");
        return false;
    }

    return isValue(&map->data, value->data);
}

void deleteNode(StrStrTree** data) {
    if (*data == NULL)
        return;

    // Удаляем поддеревья
    deleteNode(&((*data)->left));
    deleteNode(&((*data)->right));

    free((*data)->key->data);
    (*data)->key->data = NULL;
    free((*data)->value->data);
    (*data)->value->data = NULL;
    free((*data)->key);
    (*data)->key = NULL;
    free((*data)->value);
    (*data)->value = NULL;
    free(*data);
}

void clearStrStrMap(StrStrMap map) {
    if (map == NULL) {
        printf("%s\n", "Map is NULL.");
        return;
    } else {
        if (map->data != NULL) {
            deleteNode(&map->data);
            map->data = NULL;
            map->count = 0;
        } else {
            map->count = 0;
            return;
        }
    }
}



