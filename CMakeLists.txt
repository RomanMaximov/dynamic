cmake_minimum_required(VERSION 3.25)
project(DynamicCollection C)

set(CMAKE_C_STANDARD 11)

add_executable(DynamicCollection main.c
        dynamicarray.c
        map.c
        string.c
        linkedlist.c
        testarray.c
        linkedlistservice/intlinkedlist.h
        linkedlistservice/intlinkedlist.c
        linkedlistservice/doublelinkedlist.h
        linkedlistservice/doublelinkedlist.c
        linkedlistservice/strlinkedlist.h
        linkedlistservice/strlinkedlist.c
        collectiontypes.h
        iterator.h
        set.h
        set.c
        setservice/intset.h
        setservice/intset.c setservice/doubleset.h setservice/doubleset.c)
