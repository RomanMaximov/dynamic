/*
 * MIT License
 *
 * Created by Roman Maximov on 09.11.2024
 *
 * Copyright (c) 2024 Roman Maximov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <stdbool.h>
#include "string.h"
#include "linkedlist.h"
#include "arraylist.h"
#include "set.h"


/**
 *  через дженерики создаем коллекции
 */

#define newList(T, V) _Generic((T),          \
    IntList : pr_initLi_,                    \
    DoubleList : pr_initLd_,                 \
    StrList : pr_initLs_,                    \
    IntLinkedList : pr_initLLi_,             \
    DoubleLinkedList : pr_initLLd_,          \
    StrLinkedList : pr_initLLs_              \
)(T, V)

#define listOf(T, V, ...) _Generic((T),       \
    IntList : pr_initLi_lo_,                  \
    DoubleList : pr_initLd_lo_,               \
    StrList : pr_initLs_lo_,                   \
    IntLinkedList : pr_initLLi_lo_,             \
    DoubleLinkedList : pr_initLLd_lo_,          \
    StrLinkedList : pr_initLLs_lo_              \
)(T, V, __VA_ARGS__)

#define listOfArr(T, V, S) _Generic((T),        \
    DoubleList : pr_initLd_loa_,                \
    IntList : pr_initLi_loa_,                   \
    StrList : pr_initLs_loa_,                    \
    IntLinkedList : pr_initLLi_loa_,             \
    DoubleLinkedList : pr_initLLd_loa_,          \
    StrLinkedList : pr_initLLs_loa_              \
)(T, V, S)

#define newSet(T, V) _Generic((T),             \
    IntSet : pr_initSi_,                    \
    DoubleSet : pr_initSd_,                 \
    StrSet : pr_initSs_                     \
)(T, V)

#define setOf(T, V, ...) _Generic((T),       \
    IntSet : pr_initSi_so_,                  \
    DoubleSet : pr_initSd_so_,               \
    StrSet : pr_initSs_so_                  \
)(T, V, __VA_ARGS__)

#define setOfArr(T, V, S) _Generic((T),      \
    DoubleSet : pr_initSd_soa_,              \
    IntSet : pr_initSi_soa_,                 \
    StrSet : pr_initSs_soa_                  \
)(T, V, S)


#endif



