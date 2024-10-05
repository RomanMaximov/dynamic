#include<stdio.h>
#include"testarray.h"


void test() {

    /*IntList arrInt = newList(arrInt);
    printf("%s ", "array not null");
    assertNotNull(arrInt);
    free(arrInt);

    int temp[] = {23, 67, 55, 4};
    arrInt = listOfArr(arrInt, temp, 4);
    printf("%s ", "array not null");
    assertNotNull(arrInt);
    printf("%s ", "count");
    unsigned int result = arrInt->count;
    assertThat(result, 4);

    printf("%s ", "get elem");
    result = getElem(arrInt, 1);
    assertThat(result, 67);

    setElem(arrInt, 1, 88);
    printf("%s ", "set elem");
    result = getElem(arrInt, 1);
    assertThat(getElem(arrInt, 1), 88);

    add(arrInt, 99);
    printf("%s ", "add elem");
    result = arrInt->count;
    assertThat(result, 5);

    addAll(arrInt, arrInt);
    printf("%s ", "add all elems");
    result = arrInt->count;
    assertThat(result, 10);

    removeElem(arrInt, 2);
    printf("%s ", "count after remove");
    result = arrInt->count;
    assertThat(result, 9);
    printf("%s ", "get elem after remove");
    result = arrInt->data[2];
    assertThat(result, 4);

    deleteList(arrInt);*/
}

void assertInt(unsigned int result, unsigned int nominal) {
    if (result == nominal)
        printf("test: \t%sOK%s\n", GREEN, RESET);
    else
        printf("test: \t%sFAILURE%s\n", RED, RESET);
}

void assertNotNullInt(IntArray* arr) {
    if (arr != NULL)
        printf("test: \t%sOK%s\n", GREEN, RESET);
    else
        printf("test: \t%sFAILURE%s\n", RED, RESET);
}
