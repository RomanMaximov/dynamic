#ifndef TESTARRAY_H
#define TESTARRAY_H

#include"dynamicarray.h"

#define true 1
#define false 0

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN  "\033[1;32m"

#define assertNotNull(T) _Generic((T), \
    DoubleArray* : assertNotNullDouble(T),\
    IntArray* : assertNotNullInt(T) \
)

#define assertThat(T, V) _Generic((T), \
    double : assertDouble(T, V),\
    unsigned int : assertInt(T, V) \
)

void assertInt(unsigned int result, unsigned int nominal);
void assertDouble(double , double);
void assertNotNullInt(IntList);
void assertNotNullDouble(DoubleList);
void test();


#endif
