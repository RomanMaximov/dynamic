#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
//#include <windows.h>
#include "dynamic.h"
#include "string.h"
#include "setservice/intset.h"
#include "iterator.h"
#include "logerrors.h"
#include "test/testarraylist.h"
#include "test/testlinkedlist.h"
#include "test/testset.h"
#include "test/teststring.h"

#define SIZE 200000000


int sum(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int sumOptimum(int* arr, int size) {
    int* end = arr + size;
    int sum = 0;
    while (arr < end) {
        sum += *(arr++);
    }
    return sum;
}

typedef struct Data{
    const int* arr;
    int start;
    int end;
    int partial_sum;
} Data;

typedef Data* ThreadData;

void* subSum(void* arg) {
    ThreadData data = (ThreadData)arg;
    data->partial_sum = 0;

    for (int i = data->start; i < data->end; ++i) {
        data->partial_sum += data->arr[i];
    }
    return NULL;
}

bool isRemainder(int threadNum, int size) {
    return size % threadNum != 0;
}

ThreadData* arrExecutor(int threadNum, void* func, const int* source, int size) {
    bool remainder = isRemainder(threadNum, size);

    pthread_t threads[threadNum];
    for (int i = 0; i < threadNum; ++i) {
        pthread_t thread = 0;
        threads[i] = thread;
    }

    ThreadData* data = malloc(threadNum * sizeof(ThreadData));
    int part = size / threadNum;

    for (int i = 0; i < threadNum; ++i) {
        data[i] = malloc(sizeof(Data));
        data[i]->arr = source;
        data[i]->start = i * part;
        if ((i + 1) == threadNum) {
            if (remainder) {
                int diff = size - (part * (threadNum - 1));
                data[i]->start = size - diff;
                data[i]->end = size;
            } else {
                data[i]->start = i * part;
                data[i]->end = part * (i + 1);
            }
        } else {
            data[i]->start = i * part;
            data[i]->end = part * (i + 1);
        }
        data[i]->partial_sum = 0;

        pthread_create(&threads[i], NULL, func, data[i]);
    }

    for (int i = 0; i < threadNum; ++i) {
        pthread_join(threads[i], NULL);
    }
    return data;
}

int sumParallel(const int* arr, int size) {
    // thread1, thread2, thread3, thread4;
    //ThreadData data2, data3, data4;
    //int part = size / 4;
    int threadNum = 4;
    int total_sum = 0;

    /*ThreadData data1 = {arr, 0, part, 0};
    data2 = (ThreadData){arr, part, part * 2, 0};
    data3 = (ThreadData){arr, part * 2, part * 3, 0};
    data4 = (ThreadData){arr, part * 3, size, 0};

    pthread_create(&thread1, NULL, subSum, &data1);
    pthread_create(&thread2, NULL, subSum, &data2);
    pthread_create(&thread3, NULL, subSum, &data3);
    pthread_create(&thread4, NULL, subSum, &data4);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    total_sum = data1->partial_sum + data2->partial_sum + data3->partial_sum + data4->partial_sum;*/
    ThreadData* data = arrExecutor(threadNum, subSum, arr, SIZE);
    for (int i = 0; i < threadNum; ++i) {
        total_sum += data[i]->partial_sum;
    }
    return total_sum;
}

void* allocate() {
    char* text = malloc(10 * sizeof(char));
    text[0] = 'R';
    text[1] = 'o';
    return text;
}

int main()
{
    testArrayList();
    //testLinkedList();
    //testSet();
    //testString();
    /*pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, some_work, "Hello World!");
    pthread_create(&thread2, NULL, some_work, "Hello from second thread!");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("End\n");*/
    /*char* text = NULL;
    text = allocate();

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    printf("machine cores: %d\n", sysinfo.dwNumberOfProcessors);

    int* arr = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = 2;
    }
    int total;

    clock_t time_start = clock();
    total = sum(arr, SIZE);
    clock_t time_end = clock() - time_start;
    printf("total = %d\ttime for sum() = %f second", total, (double) time_end / CLOCKS_PER_SEC);
    puts("");

    clock_t time_start2 = clock();
    total = sumOptimum(arr, SIZE);
    clock_t time_end2 = clock() - time_start2;
    printf("total = %d\ttime for sumOptimum() = %f second", total, (double) time_end2 / CLOCKS_PER_SEC);
    puts("");

    clock_t time_start3 = clock();
    total = sumParallel(arr, SIZE);
    clock_t time_end3 = clock() - time_start3;
    printf("total = %d\ttime for sumParallel() = %f second", total, (double) time_end3 / CLOCKS_PER_SEC);
    puts("");*/

    return 0;
}
