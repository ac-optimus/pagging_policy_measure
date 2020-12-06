#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fifo.h"
#include "replacement_policies.h"

#define NUM_OF_PAGE_TO_REFFERENCE 100000
#define NUM_UNIQUE_PAGES 100
// hash_size and NUM_UNIQUE_PAGES are the same
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

// void run_all_policies(int page_refferences[], int cache_size, int hash_size, FILE* fp, int size){
//     int hits_random= 0, hits_fifo= 0, hits_lru= 0;
//     int status;

//     printf("------ running random --- \n");
//     hashmap* cur_hash= create_hashmap(hash_size);
//     queue* cur_queue= create_queue(cache_size);
//     for (int page_no=0; page_no< 10000; page_no++){
//         status= va_to_pa_RANDOM(cur_hash, cur_queue, page_refferences[page_no], cache_size, hash_size);
//         if (status==1)
//             hits_random+=1;
//     }

//     printf("------ running FIFO --- \n");
//     hashmap* cur_hash_fifo= create_hashmap(hash_size);
//     queue* cur_queue_fifo= create_queue(cache_size);
//     for (int page_no=0; page_no<10000; page_no++){
//         status= va_to_pa_FIFO(cur_hash_fifo, cur_queue_fifo, page_refferences[page_no]);
//         if (status==1)
//             hits_fifo+=1;
//     }

//     printf("------ running LRU --- \n");
//     hashmap* cur_hash_lru= create_hashmap(hash_size);
//     queue* cur_queue_lru= create_queue(cache_size);
//     for (int page_no=0; page_no<10000; page_no++){
//         status= va_to_pa_LRU(cur_hash_lru, cur_queue_lru, page_refferences[page_no]);
//         if (status==1)
//             hits_lru+=1;
//     }
//     fprintf(fp, "%d, %d, %d\n", hits_random, hits_lru, hits_fifo);
// }



void run_all_policies(int page_refferences[], int cache_size, int hash_size, FILE* fp, int size){
    int hits_random= 0, hits_fifo= 0, hits_lru= 0, hits_lru_approx= 0;
    int status;

    printf("------ running random --- \n");
    hashmap* cur_hash= create_hashmap(hash_size);
    queue* cur_queue= create_queue(cache_size);
    for (int page_no=0; page_no< 10000; page_no++){
        status= va_to_pa_RANDOM(cur_hash, cur_queue, page_refferences[page_no], cache_size, hash_size);
        if (status==1)
            hits_random+=1;
    }

    printf("------ running FIFO --- \n");
    hashmap* cur_hash_fifo= create_hashmap(hash_size);
    queue* cur_queue_fifo= create_queue(cache_size);
    for (int page_no=0; page_no<10000; page_no++){
        status= va_to_pa_FIFO(cur_hash_fifo, cur_queue_fifo, page_refferences[page_no]);
        if (status==1)
            hits_fifo+=1;
    }

    printf("------ running LRU --- \n");
    hashmap* cur_hash_lru= create_hashmap(hash_size);
    queue* cur_queue_lru= create_queue(cache_size);
    for (int page_no=0; page_no<10000; page_no++){
        status= va_to_pa_LRU(cur_hash_lru, cur_queue_lru, page_refferences[page_no]);
        if (status==1)
            hits_lru+=1;
    }

    printf("------ running LRU APPROX --- \n");
    hashmap* cur_hash_lru_approx= create_hashmap(hash_size);
    queue* cur_queue_lru_approx= create_queue(cache_size);
    // q_node clock_head;
    int bits[hash_size];
    for (int indx= 0; indx < hash_size; indx++)
        bits[indx]=-1;
    for (int page_no= 0; page_no < 10000; page_no++){
        status= va_to_pa_LRU_APRROX(cur_hash_lru_approx, cur_queue_lru_approx, bits, page_refferences[page_no], cache_size, hash_size);
        if (status==1)
            hits_lru_approx+=1;
    }
    fprintf(fp, "%d, %d, %d, %d\n", hits_random, hits_lru, hits_fifo, hits_lru_approx);
}



void workload_random(int cache_size, int hash_size){
    FILE* fp;
    fp = fopen("workload_random.csv", "a");
    srand(time(0));
    int page_refferences[NUM_OF_PAGE_TO_REFFERENCE];
    int lower = 1;
    int upper= NUM_UNIQUE_PAGES;
    int num;
    for (int i=0; i< NUM_OF_PAGE_TO_REFFERENCE; i++){
        num = (rand() % (upper - lower + 1)) + lower;
        page_refferences[i]= num;
    }

    int size_= sizeof(page_refferences)/ sizeof(page_refferences[0]);
    run_all_policies(page_refferences, cache_size, hash_size, fp, size_);
    fclose(fp);
}

void workload_looping(int cache_size, int hash_size){
    FILE* fp;
    fp = fopen("workload_looping.csv", "a");

    int page_refferences[NUM_OF_PAGE_TO_REFFERENCE];
    for (int i=0; i< NUM_OF_PAGE_TO_REFFERENCE; i++){
        page_refferences[i]= i%50+1;
    }

    int size_= sizeof(page_refferences)/ sizeof(page_refferences[0]);
    run_all_policies(page_refferences, cache_size, hash_size, fp, size_);
    fclose(fp);
}

void workload_80_20(int cache_size, int hash_size){
    // 80% of the refferences are to the 20% and 20% refference are to the remaining 80%
    FILE* fp;
    fp = fopen("workload_80_20.csv", "a");
    int page_refferences[NUM_OF_PAGE_TO_REFFERENCE];
    for (int i=0; i< 8000; i++)
        page_refferences[i]= i%20+1;
    for (int i=8001; i< 10000; i++)
        page_refferences[i]= 20+i%80+1;
    // uncomment and see the plot for the 80-20 workload
    // for (int i=0; i< 10000; i++)
    //     printf("%d\n", page_refferences[i]);

    shuffle(page_refferences, 10000);

    int size_= sizeof(page_refferences)/ sizeof(page_refferences[0]);
    run_all_policies(page_refferences, cache_size, hash_size, fp, size_);
    fclose(fp);
}


int main(int argc, char* argv[]){
    int cache_size= 10, hash_size= 100;
    for (int cache_size=1; cache_size<=100;cache_size++){
        if (strcmp(argv[1], "RANDOM")==0) // RANDOM
            workload_random(cache_size, hash_size);
        else if (strcmp(argv[1], "80-20")==0) // FIFO
            workload_80_20(cache_size, hash_size);
        else if (strcmp(argv[1], "LOOPING")==0) // LRU
            workload_looping(cache_size, hash_size);
    }
    return 0;
}