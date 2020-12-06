#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fifo.h"

#include "replacement_policies.h"


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

void run_all_policies(int page_refferences[10000], int cache_size, int hash_size, FILE* fp){
    int hits_random= 0, hits_fifo= 0, hits_lru= 0;
    int status;
    hashmap* cur_hash= create_hashmap(hash_size);
    queue* cur_queue= create_queue(cache_size);
    for (int page_no=0; page_no<10000; page_no++){
        status= va_to_pa_RANDOM(cur_hash, cur_queue, page_refferences[page_no], cache_size, hash_size);
        if (status==1)
            hits_random+=1;
    }

    hashmap* cur_hash_fifo= create_hashmap(hash_size);
    queue* cur_queue_fifo= create_queue(cache_size);
    for (int page_no=0; page_no<10000; page_no++){
        status= va_to_pa_FIFO(cur_hash_fifo, cur_queue_fifo, page_refferences[page_no]);
        if (status==1)
            hits_fifo+=1;
    }

    hashmap* cur_hash_lru= create_hashmap(hash_size);
    queue* cur_queue_lru= create_queue(cache_size);
    for (int page_no=0; page_no<10000; page_no++){
        status= va_to_pa_LRU(cur_hash_lru, cur_queue_lru, page_refferences[page_no]);
        if (status==1)
            hits_lru+=1;
    }
    printf("%d, %d, %d\n", hits_random, hits_fifo, hits_lru);
    fprintf(fp, "%d, %d, %d\n", hits_random, hits_fifo, hits_lru);

    // return hitRates;






}

void random_workload(int cache_size, int hash_size){
    // select random number of
    FILE* fp;
    fp = fopen("workload_random.csv", "a");
    srand(time(0));
    int page_refferences[10000];
    int lower = 1;
    int upper= 100;
    int num;

    for (int i=0; i< 10000; i++){
        num = (rand() % (upper - lower + 1)) + lower;
        page_refferences[i]= num;
    }

    run_all_policies(page_refferences, cache_size, hash_size, fp);
    fclose(fp);
}

void looping(int cache_size, int hash_size){
    FILE* fp;
    fp = fopen("workload_looping.csv", "a");

    int page_refferences[10000];
    for (int i=0; i< 10000; i++){
        page_refferences[i]= i%50+1;
    }

    run_all_policies(page_refferences, cache_size, hash_size, fp);
    fclose(fp);
}

void workload_80_20(int cache_size, int hash_size){
    // 80% of the refferences are to the 20% and 20% refference are to the remaining 80%
    FILE* fp;
    fp = fopen("workload_80_20.csv", "a");
    int page_refferences[10000];
    for (int i=0; i< 8000; i++)
        page_refferences[i]= i%20+1;
    for (int i=8001; i< 10000; i++)
        page_refferences[i]= 20+i%80+1;
    // uncomment and see the plot for the 80-20 workload
    // for (int i=0; i< 10000; i++)
    //     printf("%d\n", page_refferences[i]);

    shuffle(page_refferences, 10000);
    for (int i=0; i< 10000; i++)
        printf("%d\n", page_refferences[i]);

    run_all_policies(page_refferences, cache_size, hash_size, fp);
    fclose(fp);

}


int main(int argc, char* argv[]){
    int cache_size= 10, hash_size= 100;
   FILE *fp;


    for (int cache_size=1; cache_size<=1;cache_size++){
        printf("cache size-- %d\n", cache_size);
        if (strcmp(argv[1], "RANDOM")==0) // RANDOM
            random_workload(cache_size, hash_size);
            // printf("%d, %d, %d\n", hitRates[0], hitRates[1], hitRates[2]);
        else if (strcmp(argv[1], "80-20")==0) // FIFO
            workload_80_20(cache_size, hash_size);
        else if (strcmp(argv[1], "LOOPING")==0) // LRU
            looping(cache_size, hash_size);

    }
    return 0;
}