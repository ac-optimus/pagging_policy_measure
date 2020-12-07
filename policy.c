/*
This file containd all functions related with various policies.
Each policy returns the hit rate
*/

#include "definitions.h"

float policy_FIFO(struct workload * w, int cache_size)
{
	//printf("------ running FIFO --- \n");

	float hit_rate = 0;
   	float hits_fifo= 0;
	int status;
	int hash_size= w->size;

    hashmap* cur_hash_fifo= create_hashmap(hash_size);
    queue* cur_queue_fifo= create_queue(cache_size);
    for (int page_no=0; page_no<hash_size; page_no++){
        status= cache_FIFO(cur_hash_fifo, cur_queue_fifo, w->work[page_no]);
        if (status==1)
            hits_fifo+=1;

    }
	hit_rate= hits_fifo/hash_size;
	return hit_rate;
}

float policy_LRU(struct workload * w, int cache_size)
{
	//printf("------ running LRU --- \n");

	float hit_rate = 0;
	float hits_lru=0;
	int status;
	int hash_size= w->size;

	hashmap* cur_hash_lru= create_hashmap(hash_size);
    queue* cur_queue_lru= create_queue(cache_size);
    for (int page_no=0; page_no<hash_size; page_no++){
        status= cache_LRU(cur_hash_lru, cur_queue_lru, w->work[page_no]);
        if (status==1)
            hits_lru+=1;
    }
	hit_rate= hits_lru/hash_size;
	return hit_rate;
}

float policy_LRUapprox(struct workload * w, int cache_size)
{
	//printf("------ running LRU APPROX --- \n");
	float hit_rate = 0;
   	float hits_lru_approx= 0;
    int status;
	int hash_size= w->size;

	hashmap* cur_hash_lru_approx= create_hashmap(hash_size);
    queue* cur_queue_lru_approx= create_queue(cache_size);
    int bits[hash_size];
    for (int indx= 0; indx < hash_size; indx++)
        bits[indx]=-1;
    for (int page_no= 0; page_no < hash_size; page_no++){
        status= cache_LRU_APRROX(cur_hash_lru_approx, cur_queue_lru_approx, bits, w->work[page_no], cache_size, hash_size);
        if (status==1)
            hits_lru_approx+=1;
    }
	hit_rate= hits_lru_approx/hash_size;
	return hit_rate;
}

float policy_RANDOM(struct workload * w, int cache_size)
{
	//printf("------ running RANDOM --- \n");
	float hit_rate = 0;
   	float hits_random= 0;
    int status;
	int hash_size= w->size;

	hashmap* cur_hash= create_hashmap(hash_size);
    queue* cur_queue= create_queue(cache_size);
    for (int page_no=0; page_no< hash_size; page_no++){
        status= cache_RANDOM(cur_hash, cur_queue, w->work[page_no], cache_size, hash_size);
        if (status==1)
            hits_random+=1;
    }
	hit_rate= hits_random/hash_size;
	return hit_rate;
}
