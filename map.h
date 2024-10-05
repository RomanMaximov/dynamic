#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "string.h"
#include "dynamicarray.h"

typedef struct StrStrTree StrStrTree;
typedef struct StrStrTreeMap StrStrTreeMap;
typedef struct String String;
typedef struct StringArray StringArray;

typedef struct EntrySet {
    String* key;
    String* value;
} EntrySet;

typedef struct EntrySetArray {
    int count;
    struct EntrySet** data;
} EntrySetArray;

typedef EntrySetArray* EntrySetList;
typedef StrStrTreeMap* StrStrMap;
typedef String* string;
typedef StringArray* StringList;


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
