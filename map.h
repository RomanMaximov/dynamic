#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "dynamic.h"


typedef struct EntrySet {
    String* key;
    String* value;
} EntrySet;

typedef struct EntrySetArray {
    int count;
    struct EntrySet** data;
} EntrySetArray;

typedef EntrySetArray* EntrySetList;


StrStrMap newStrStrMap(StrStrMap);
int sizeStrStrMap(StrStrMap);
bool put(StrStrMap, string key, string value);
string get(StrStrMap, string key);
StringList getValueList(StrStrMap map);
StringList getKeyList(StrStrMap map);
EntrySetList getEntrySetList(StrStrMap);
//putAll()
void clearStrStrMap(StrStrMap);
//remove()
//replace()
bool containsKey(StrStrMap, string);
bool containsValue(StrStrMap, string);
void printMap(StrStrMap);



#endif
