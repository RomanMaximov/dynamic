cmake_minimum_required(VERSION 3.25)
project(DynamicCollection C)

set(CMAKE_C_STANDARD 17)

add_executable(DynamicCollection main.c
        string.c
        linkedlist.c
        test/testarray.c
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
        setservice/intset.c
        setservice/doubleset.h
        setservice/doubleset.c
        setservice/strset.h
        setservice/strset.c
        arraylist.h
        arraylist.c
        arrayservice/intarraylist.h
        arrayservice/intarraylist.c
        arrayservice/doublearraylist.h
        arrayservice/doublearraylist.c
        arrayservice/strarraylist.h
        arrayservice/strarraylist.c
        util/arraylistutil.h
        context.h
        util/setutil.h)
