#include <stdio.h>
#include <stdlib.h>
#include "dynamic.h"
//#include "dynamicarray.h"
//#include "linkedlist.h"
//#include "string.h"
//#include "map.h"

int main()
{
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

    //IntArray* arr2 = arrayOf(1, 456);
    //printArray(arr2);
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

    /*IntList arrInt = newList(arrInt);
    add(arrInt, 55);
    add(arrInt, 12);
    add(arrInt, 13);
    add(arrInt, 14);
    add(arrInt, 15);
    add(arrInt, 16);
    printList(arrInt);
    printf("arrInt capacity: %d\n", arrInt->capacity);

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
    deleteString(s);

    string s2 = stringOf("How it was?");
    string s3 = stringOf("broken");

    string s4 = join("-", 3, s2, s3, s2);
    printString(s4);


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
    deleteString(s2);
    deleteString(s3);
    deleteString(s4);
    deleteString(sub);
    deleteString(sub2);
    deleteString(sub3);

    string s5 = stringOf("don,sun,dog");//,string,milk,bob,ron,see,str11,str12,str13");
    printString(s5);
    puts("============================================");
    StringList stringList = newList(stringList);
    StringList stringList2 = newList(stringList2);
    add(stringOf("str1"), stringList);
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
    printList(strings);

    int t1[5] = {1,2,3,4,5};
    int t2[2] = {2, 5};
    IntList baseList = listOfArr(baseList, t1, 5);
    IntList removeList = listOfArr(removeList, t2, 2);
    printList(baseList);
    printList(removeList);
    removeAllInt(baseList, removeList);
    printList(baseList);
    printf("Count of baseList = %d\n", size(baseList));
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
    deleteList(strList2);
    



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


    deleteString(empty);
    deleteString(blank);
    deleteList(stringList);
    deleteList(stringList2);
    deleteList(strings);

    return 0;
}
