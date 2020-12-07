// This file contains all the functions related to the generation of workload

#include "definitions.h"

struct workload * generate_workload(WorkloadsT type, int pages, int size)
{
    // given workload type, total number of pages and size
    struct workload* w= (struct workload*)(malloc(sizeof(struct workload)));
    w->pages= pages;
    w->size= size;
    if (type== 0)
        generate_loop(w);
    else if (type== 1)
        generate_random(w);
    else if(type== 2)
        generate_local(w);
    // for (int i=0; i< w->size; i++){
    //     printf("%d\n", w->work[i]);
    // }
    return w;
}

struct workload * generate_random(struct workload * w)
{
    srand(time(0));
    int* page_refferences= (int*)malloc(sizeof(int)*w->size);
    int lower = 1;
    int upper= w->pages;
    int num;
    for (int i=0; i< w->size; i++){
        num = (rand() % (upper - lower + 1)) + lower;
        page_refferences[i]= num;
    }
    w->work= page_refferences;
    return w;
}

struct workload * generate_loop(struct workload * w)
{
    int* page_refferences= (int*)malloc(sizeof(int)*w->size);
    for (int i=0; i< w->size; i++){
        page_refferences[i]= i%50+1;
    }
    w->work= page_refferences;
    return w;
}

void shuffle(int *array, size_t n){
    // taken from stack overflow -- https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

struct workload * generate_local(struct workload * w)
{
    int* page_refferences= (int*)malloc(sizeof(int)*w->size);
    for (int i=0; i< 8000; i++)
        page_refferences[i]= i%20+1;
    for (int i=8001; i< 10000; i++)
        page_refferences[i]= 20+i%80+1;

    shuffle(page_refferences, w->size);
    w->work= page_refferences;
    return w;
}