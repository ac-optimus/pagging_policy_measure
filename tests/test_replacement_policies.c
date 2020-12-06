/*hashmap using simple array
key-- index,
value-- pointers to the fifo nodes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/fifo.h"
#include "../headers/replacement_policies.h"

#define HASH_SIZE 10
#define CACHE_SIZE 3

int main(int argc, char* argv[]){
    // let the work load be 1, 2, 3,1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5
    // let the cache size be 4
    if (argc <2){
        printf("Please provide workload as argument RANDOM/ FIFO/ LRU.");
        return 1;
    }
    int cache_size=  CACHE_SIZE;
    int hash_size= HASH_SIZE;
    hashmap* cur_hash= create_hashmap(hash_size);
    queue* cur_queue= create_queue(cache_size);
    // int arr[15]= {1, 2, 3, 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int arr[15]= {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    // int arr[15]= {1, 2, 3, 1, 2, 3, 4, 2, 5, 2, 3, 4, 5, 1};
    int status;
    srand(time(0));
    for (int indx=0; indx<12; indx++){
        if (strcmp(argv[1], "RANDOM")==0) // RANDOM
            status= va_to_pa_RANDOM(cur_hash, cur_queue, arr[indx], cache_size, hash_size);
        else if (strcmp(argv[1], "FIFO")==0) // FIFO
            status= va_to_pa_FIFO(cur_hash, cur_queue, arr[indx]);
        else if (strcmp(argv[1], "LRU")==0) // LRU
            status= va_to_pa_LRU(cur_hash, cur_queue, arr[indx]);
        if (status==1)
            printf("search page: %d ------hit------\n", arr[indx]);
        else
            printf("search page: %d ------miss------\n", arr[indx]);
    }
    return 0;
}