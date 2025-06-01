#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "dynamiccollection.h"
#include "string.h"
#include "setservice/intset.h"
#include "iterator.h"
#include "logerrors.h"

int main()
{
    ///////////   int index = hashCode(key) % capacity;  индекс бакета
    unsigned int key = 510;
    unsigned long long tempKey = (unsigned long long) key;
    tempKey = ((tempKey >> 4) ^ tempKey) * 0x1b873593ULL;
    printf("key: %lld\n", tempKey);

    unsigned int key2 = 550;
    unsigned long long tempKey2 = (unsigned long long) key2;
    tempKey2 = ((tempKey2 >> 4) ^ tempKey2) * 0x1b873593ULL;
    printf("key: %lld\n", tempKey2);
    printf("key: %d\n", (int) (tempKey % 16));
    printf("key2: %d\n", (int) (tempKey2 % 16));
    puts("==============================");

    IntList listForIter = listOf(listForIter, 2, 10, 15);
    Iterator itr = iterator(listForIter->values);
    int value = 0;
    while (hasNext(itr)) {
        value = nextInt(itr);
        printf("iterator value: %d\n", value);
    }

    IntList intList = NULL;
    LOG_INFO("Response: code = %d, description = %s", 200, "OK");

    if (intList == NULL) {
        LOG_ERROR("intList is NULL");
    }

    deleteItr(&itr);
    puts("=======================================================================");


    int arr[100];
    printf("size of arr: %llu\n", sizeof(arr));




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
    string s = strOf("MotoCYclE");
    s->print(s);
    int len = s->length(s);
    s->toLowerCase(s);
    printf("size: %d\n", len);
    s->print(s);

    s->toUpperCase(s);
    s->print(s);
    //delStr(&s);
    s->delete(&s);


    string s2 = strOf("How it was?");
    string s3 = strOf("broken");
    s2->concat(s2, s3);
    puts("==========  concat  ========");
    s2->print(s2);

    string s4 = joinStr("-", 3, s2, s3, s2);
    s4->print(s4);


    //printf("ch = %c\n", charAt(s2, 4));
    string sub = strOf("See");
    string sub2 = strOf("r.");
    string sub3 = strOf("ts");

    if (s2->startsWith(s2, sub)) {
        puts("starts OK.");
    } else {
        puts("NOT starts.");
    }

    if (s2->endsWith(s2, sub2)) {
        puts("ends OK.");
    } else {
        puts("NOT ends.");
    }

    s2->reverse(s2);
    s2->print(s2);
    printf("char index: %d\n", s2->indexOf(s2, '?'));
    s2->delete(&s2);
    s3->delete(&s3);
    s4->delete(&s4);
    sub->delete(&sub);
    sub2->delete(&sub2);
    sub3->delete(&sub3);

    /*string s5 = stringOf("don,sun,dog");//,string,milk,bob,ron,see,str11,str12,str13");
    printString(s5);
    puts("============================================");
    StringList stringList = newList(stringList);
    StringList stringList2 = newList(stringList2);*/


    /*puts("========================= ////////   LinkedList   /////// ============================================");
    string ll1 = strOf("s1");
    string ll2 = strOf("s2");
    string ll3 = strOf("s3");
    string ll4 = strOf("s4");
    StrLinkedList strLinkedList = newList(strLinkedList, NULL);
    strLinkedList->add(strLinkedList, ll1);
    strLinkedList->add(strLinkedList, ll2);
    strLinkedList->add(strLinkedList, ll3);
    strLinkedList->add(strLinkedList, ll4);
    strLinkedList->add(strLinkedList, ll4);
    strLinkedList->add(strLinkedList, ll4);
    puts("// === //");
    strLinkedList->print(strLinkedList);
    strLinkedList->reverse(strLinkedList);
    puts("// === //");
    strLinkedList->print(strLinkedList);
    strLinkedList->delete(&strLinkedList);

    puts("========================= ////////   ArrayList   /////// ============================================");
    IntList intList = newList(intList, NULL);
    intList->add(intList, rand() % 100);
    IntList intList2 = newList(intList2, intList->values);
    intList->print(intList);
    intList2->print(intList2);

    StrList strList = listOf(strList, 3, "dob", "pop", "com");
    strList->print(strList);

    char* arr[] = {"fact", "pop", "com"};
    StrList strList2 = listOfArr(strList2, arr, 3);
    strList2->print(strList2);
    strList->removeAll(strList, strList2->values);
    strList->print(strList);

    puts("");
    puts("================ ////////   string   /////// ==================");
    string strForSub = strOf("The great country in world.");
    string subStr = strOf("great country");
    printf("subStr index: %d\n", strForSub->indexOfSubStr(strForSub, subStr));

    puts("");
    puts("================ ////////   set   /////// ==================");
    IntSet intSet = newSet(intSet, NULL);
    intSet->add(intSet, 2);
    intSet->add(intSet, 5);
    intSet->add(intSet, 7);*/

    //bool isKey = containsKeyInt(intSet, 8);
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

    IntSet set = newSet(set, NULL);
    IntSet set2 = newSet(set2, NULL);

    set->add(set, 200);
    set->add(set, 120);
    set->add(set, 300);
    set->add(set, 100);
    set->add(set, 150);
    set->add(set, 130);

    //printTree(set);
    set->removeElem(set, 200);
    //printTree(set);
    //printIntSet(set);
    //printIntSet(set2);



    //deleteIntSet(&set);
    //printIntSet(set);

    puts("=======================");



    /*deleteString(empty);
    deleteString(blank);
    deleteList(stringList);
    deleteList(stringList2);
    deleteList(strings);*/

    return 0;
}
