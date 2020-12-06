/* perfomance measure of lru approx on 80-20 workload*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/fifo.h"
#include "../headers/replacement_policies.h"

#define NUM_OF_PAGE_TO_REFFERENCE 100000
#define NUM_UNIQUE_PAGES 100

#include "../headers/workloads.h"


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


int main(int argc, char* argv[]){
    int cache_size= 10, hash_size= 100;
    FILE* fp;
    if (strcmp(argv[1], "RANDOM")==0) // RANDOM
        fp = fopen("../summary/workload_random_lru_approx.csv", "a");
    else if (strcmp(argv[1], "80-20")==0) // 80-20
        fp = fopen("../summary/workload_80_20_lru_approx.csv", "a");
    else if (strcmp(argv[1], "LOOPING")==0) // LOOPING
        fp = fopen("../summary/workload_looping_lru_approx.csv", "a");
    fprintf(fp, "RANDOM,LRU,FIFO,LRU_APPROX\n");


    for (int cache_size=1; cache_size<=100;cache_size++){
        if (strcmp(argv[1], "RANDOM")==0) // RANDOM
            workload_random(cache_size, hash_size, fp);
        else if (strcmp(argv[1], "80-20")==0) // FIFO
            workload_80_20(cache_size, hash_size, fp);
        else if (strcmp(argv[1], "LOOPING")==0) // LRU
            workload_looping(cache_size, hash_size, fp);
    }
    fclose(fp);
    return 0;
}