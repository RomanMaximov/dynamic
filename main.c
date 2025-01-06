#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dynamic.h"
//#include "dynamicarray.h"
//#include "linkedlist.h"
//#include "string.h"
//#include "map.h"


// Простая хэш-функция для строк (алгоритм djb2)
unsigned long hashString(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

unsigned long hashDouble(double value) {
    // Для хранения битового представления double используем 64-битный целочисленный тип
    uint64_t intRepresentation;

    // Копируем биты double в 64-битное целое число
    memcpy(&intRepresentation, &value, sizeof(double));

    // Используем это 64-битное число как хэш
    return (unsigned long)(intRepresentation ^ (intRepresentation >> 32));
}

int main()
{

    ///////////   int index = hashCode(key) % capacity;  индекс бакета

    /*IntArray* arrInt = null;
    arrInt = newArray(arrInt);

    puts("============================================");
    int temp[] = { 111, 65, 112, 113, 7, 22 };
    double temp2[] = {167.91, 14.3, 12.7};
    IntArray* from = null;
    from = arrayOf(from, temp, sizeof(temp) / sizeof(int));
    add(from, 55);

    DoubleArray* from2 = null;
    from2 = arrayOf(from2, temp2, sizeof(temp2) / sizeof(double));
    add(from2, 145.97);

    printf("size: %d\n", size(from));
    sort(from);
    printArray(from);
    reverseArray(from);
    printArray(from);

    printf("size: %d\n", size(from2));
    sort(from2);
    printArray(from2);
    reverseArray(from2);
    printArray(from2);
    if (contains(from2, 167.91)) {
        printf("element %s\n", "contains");
    }*/
    //removeElem(from, 1);

    //printArray(from);
    //printf("size: %d\n", size(from));
    //puts("============================================");

    //add(arr, 55);
    //add(arr, 34);
    //addAll(arr, from);
    //printArray(arr);
    //puts("============================================");

    //printf("[0]: %d\n", getElem(arr, 0));
    //printf("[1]: %d\n", getElem(arr, 1));

    //printf("size: %d\n", size(arr));
    ////sort(arr);
    //printArray(arr);
    //puts("============================================");

    //IntList arr2 = listOfInt(arr2, 2, 77, 88);
    //addIntElem(arr2, 99);
    //addIntElem(arr2, 111);
    //addIntElem(arr2, 222);
    //printArrayInt(arr2);
    //setElem(arr2, 0, 255);
    //printArray(arr2);
    //printf("size arr2: %d\n", size(arr2));
    //removeElem(arr2, 0);
    //printArray(arr2);
    //printf("size arr2: %d\n", size(arr2));
    //puts("============================================");

    /*IntArray* ss = newIntArray();
    srand(time(NULL));
    for (int i = 0; i < 3; ++i) {
        add(ss, rand() % 1000);
    }
    printf("size ss: %d\n", size(ss));
    printArray(ss);*/
    //for (int i = 0; i < 10; ++i) {
    //    int index = rand() % 100;
    //    printf("[%d]: %d\n", index, getElem(ss, index));
    //}
    //clear(ss);
    //printf("size ss: %d\n", size(ss));
    //printArray(ss);

    /*DoubleList arrDouble = newList(arrDouble);
    addDoubleElem(arrDouble, 55.009);
    addDoubleElem(arrDouble, 12.071);
    addDoubleElem(arrDouble, 12.007);
    addDoubleElem(arrDouble, 1.18);
    addDoubleElem(arrDouble, 12.0069);
    addDoubleElem(arrDouble, 16.00056);
    addDoubleElem(arrDouble, 99.0000075);
    addDoubleElem(arrDouble, 99.0000074);
    printList(arrDouble);
    sortDouble(arrDouble);
    printList(arrDouble);*/
    //sortIntReverse(arrInt);
    //printList(arrInt);
    /*printf("arrInt capacity: %d\n", arrInt->capacity);

    puts("============================================");
    int temp[] = { 111, 65, 112, 113, 7, 22 };
    IntList from = listOf(from, temp, sizeof(temp) / sizeof(int));
    add(from, 55);
    printList(from);

    puts("============================================");
    StringList strList = stringListOf(3, "bob", "rob", "ron");
    //printList(strList);
    printf("strList size: %d\n", strList->count);

    deleteList(arrInt);
    deleteList(strList);
    //deleteArray(ss);
    deleteList(from);*/
    //deleteArray(from2);

    /*puts("============================================");
    LinkedList* list = newIntLinkedList();
    insertEnd(list, 45);
    printLinkedList(list);
    printf("size: %d\n", sizeList(list));
    insertBegin(list, 555);
    insertEnd(list, 99);
    printLinkedList(list);
    printf("size: %d\n", sizeList(list));
    printf("begin: %d\tend: %d\n\n", list->begin->number, list->end->number);

    puts("============================================");
    LinkedList* list2 = listOf(4, 251, 261, 277, 385);
    printLinkedList(list2);
    printf("size: %d\n", sizeList(list2));
    printf("begin: %d\tend: %d\n", list2->begin->number, list2->end->number);

    deleteLinkedList(list);
    deleteLinkedList(list2);*/

    puts("============================================");
    //test();

    puts("============================================");
    string s = stringOf("Moto");
    printString(s);
    int len = length(s);
    s = toLowerCase(s);
    printf("size: %d\n", len);
    printString(s);

    s = toUpperCase(s);
    printString(s);
    //delStr(&s);
    deleteString(&s);


    string s2 = stringOf("How it was?");
    string s3 = stringOf("broken");

    string s4 = join("-", 3, s2, s3, s2);
    printString(s4);

    char temp[1];
    StringList stringList = listOfStrLiteral(stringList, temp, 9, "web", "cam", "bob", "g7", "acr", "web", "cat", "a1", "cat");
    printArrayString(stringList);
    sortStrList(stringList);
    printArrayString(stringList);

    //printf("ch = %c\n", charAt(s2, 4));
    string sub = stringOf("See");
    string sub2 = stringOf("r.");
    string sub3 = stringOf("ts");

    if (startsWith(s2, sub)) {
        puts("starts OK.");
    } else {
        puts("NOT starts.");
    }

    if (endsWith(s2, sub2)) {
        puts("ends OK.");
    } else {
        puts("NOT ends.");
    }

    s2 = reverseStr(s2);
    printString(s2);
    printf("char index: %d\n", indexOf(s2, '?'));
    deleteString(&s2);
    deleteString(&s3);
    deleteString(&s4);
    deleteString(&sub);
    deleteString(&sub2);
    deleteString(&sub3);

    /*string s5 = stringOf("don,sun,dog");//,string,milk,bob,ron,see,str11,str12,str13");
    printString(s5);
    puts("============================================");
    StringList stringList = newList(stringList);
    StringList stringList2 = newList(stringList2);*/


    puts("========================= ////////               /////// ============================================");
    string ll1 = stringOf("s1");
    string ll2 = stringOf("s2");
    string ll3 = stringOf("s3");
    string ll4 = stringOf("s4");
    StrLinkedList strLinkedList = newStrLinkedList(strLinkedList);
    strLinkedList->add(strLinkedList, ll1);
    strLinkedList->add(strLinkedList, ll2);
    strLinkedList->add(strLinkedList, ll3);
    strLinkedList->add(strLinkedList, ll4);
    strLinkedList->reverse(strLinkedList);
    printStrLL(strLinkedList);


    puts("");
    /*add(stringOf("str1"), stringList);
    add(stringOf("str2"), stringList);
    add(stringOf("str3"), stringList);
    printList(stringList);
    add(stringOf("str1"), stringList2);
    add(stringOf("str2"), stringList2);
    printList(stringList2);

    if (isEqualStrLists(stringList, stringList2)) {
        puts("Lists are equals.");
    } else {
        puts("Lists are NOT equals.");
    }

    StringList strings = split(s5, ',');
    puts("Strings after split:");
    add("pppp", strings);
    printList(strings);

    puts("remove string with index = 1");
    removeElem(strings, 1);
    printList(strings);
    puts("print finished");

    setElem("Set elem", strings, 2);
    printList(strings);*/

    //printList(baseList);
    //printList(removeList);
    //removeAllInt(baseList, removeList);
    //printList(baseList);
    /*printf("Count of baseList = %d\n", size(baseList));
    deleteList(baseList);
    deleteList(removeList);

    IntList fff = newList(fff);

    string s6 = joinStrList("-", strings);
    printString(s6);
    deleteString(s5);
    deleteString(s6);


    string empty = emptyStr(); //stringOf("");
    if (isEmptyStr(empty))
        puts("string is empty.");

    string blank = stringOf(" y ");
    if (isBlank(blank))
        puts("string is blank.");
    else
        puts("string is NOT blank.");

    IntList intList = listOf(intList, 3, 333,444,555);
    printList(intList);
    deleteList(intList);

    char t[1];
    StringList strListFromCharArr = listOf(t, 3, "aaa1", "bbb1", "ccc1");
    printList(strListFromCharArr);

    StringList strList = listOf(strList, 3, stringOf("aaa2"), stringOf("bbb2"), stringOf("ccc2"));
    printList(strList);

    char* charArr[] = {"aaa3", "bbb3", "ccc3"};
    StringList strList2 = listOfArr(strList, charArr, 3);
    printList(strList2);
    addAll(strList, strList2);
    add(stringOf("oooooooooo"), strList2);
    printList(strList);
    if (containsAll(strList, strList2)) {
        puts("Contains all.");
    } else {
        puts("Not contains all.");
    }

    puts("===========================================");
    printList(strList);
    printList(strList2);
    removeAllStr(strList, strList2);
    printList(strList);

    deleteList(strListFromCharArr);
    deleteList(strList);
    deleteList(strList2);*/

    puts("===========================================");

    IntSet set = newIntSet(set);
    IntSet set2 = newIntSet(set2);
    set->add(set, 0);
    set->add(set, 1);
    set->add(set, 2);
    set->add(set, 17);
    //set2->add(set2, 99);
    //set2->add(set2, 98);
    printSet(set);

    set->add(set, 3);
    set->add(set, 4);
    set->add(set, 5);
    set->add(set, 6);
    set->add(set, 7);
    set->add(set, 8);
    printSet(set);
    set->add(set, 9);
    set->add(set, 10);
    set->add(set, 11);
    set->add(set, 12);
    set->add(set, 13);
    set->add(set, 14);
    set->add(set, 15);
    set->add(set, 96);
    set->add(set, 64);
    printSet(set);
    int number = 23;
    if(containsIntSet(set, number))
        printf("set contains %d\n", number);
    else
        printf("set NOT contains %d\n", number);

    if (containsAnyIntSet(set, set2))
        puts("set contains any set2");
    else
        puts("set NOT contains any set2");

    deleteIntSet(&set);
    printSet(set);

    puts("");

    /*StrStrMap strStrMap = newStrStrMap(strStrMap);
    string s35 = stringOf("35");
    string key1 = stringOf("1");
    put(strStrMap, key1, stringOf("water"));
    put(strStrMap, stringOf("2"), stringOf("milk"));
    put(strStrMap, stringOf("2"), stringOf("fruit"));
    put(strStrMap, stringOf("67"), stringOf("TTTTT"));
    put(strStrMap, stringOf("35"), stringOf("MMMM"));

    //clear(strStrMap);
    printf("%s", "key1: ");
    printString(key1);
    printf("map size: %d\n", size(strStrMap));

    StringList keyList = getKeyList(strStrMap);
    puts("key list:");
    printList(keyList);
    puts("====ok====");
    StringList valueList = getValueList(strStrMap);
    puts("====ok====");
    puts("value list:");
    printList(valueList);

    bool isKey = containsKey(strStrMap, s35);

    printf("value by key: \"35\" is: ");

    string temp35 = get(strStrMap, s35);
    printString(temp35);

    printMap(strStrMap);
    puts("====ok====");*/


    /*deleteString(empty);
    deleteString(blank);
    deleteList(stringList);
    deleteList(stringList2);
    deleteList(strings);*/

    return 0;
}
