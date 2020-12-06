// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include "fifo.h"



typedef struct _hashmap{
    int size;
    q_node** mapping;
}hashmap;


hashmap* create_hashmap(int size){
    // array of pointers to q
    hashmap* hash= (hashmap*)(malloc(sizeof(hashmap)));
    hash->size= size;
    hash->mapping= (q_node**)(malloc(sizeof(q_node*)*size));
    for (int indx=0; indx< size; indx++){
        hash->mapping[indx]= NULL;
    }
    return hash;
}

int va_to_pa_FIFO(hashmap* hash, queue* cur_queue, int page_num){
    // check if curqueue is full, if full then pop from rear and add to the front
    // return 1 if a hit else return 0
    if (hash->mapping[page_num] != NULL)
        return 1;  //hit

    if (is_full(cur_queue)){ // make some space
        hash->mapping[cur_queue->rear->page_number]= NULL;
        dequeue(cur_queue);
    }
    hash->mapping[page_num]= enqueue(cur_queue, page_num);
    return 0;
}

// a=b=c=d
// c=a=b=d

void remove_a_queue_node(queue* cur_queue, q_node* cur_node){
    // delete a particular node from from the queue

    // check cur_node is rear
    if (cur_node== cur_queue->rear)
        cur_queue->rear= cur_node->prev;
    if (cur_node== cur_queue->front)
        cur_queue->front= cur_node->nxt;


    q_node* prev_ptr= cur_node->prev;
    q_node* next_ptr= cur_node->nxt;

    // cur_node->prev = NULL;

    // cur_node->nxt= NULL;
    if (prev_ptr != NULL)
        prev_ptr->nxt= next_ptr;
    if (next_ptr != NULL)
        next_ptr->prev= prev_ptr;
    // printf("previous-- %d\n", cur_node->prev->page_number);
    cur_queue->filled-=1;

    free(cur_node);

    // printf("walla\n");
}

int va_to_pa_LRU(hashmap* hash, queue* cur_queue, int page_num){
    // return 1 for hit and 0 for miss

    if (hash->mapping[page_num] != NULL){ // hit
        // bring it to the front and stitch the queue nodes accodringly such that order is not disturbed
        q_node* cur_node= hash->mapping[page_num];
        remove_a_queue_node(cur_queue, cur_node);
        hash->mapping[page_num]= enqueue(cur_queue, page_num);
        return 1;
    }
    // miss
    if (is_full(cur_queue)){ // make some space
        hash->mapping[cur_queue->rear->page_number]= NULL;
        dequeue(cur_queue);
    }
    hash->mapping[page_num]= enqueue(cur_queue, page_num);
    return 0;
}

int get_random_index(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


int va_to_pa_RANDOM(hashmap* hash, queue* cur_queue, int page_num, int cache_size, int hash_size){
    // return 1 for hit and 0 for miss
    if (hash->mapping[page_num] != NULL){
        // hit
        return 1;
    }
    // miss
    if (is_full(cur_queue)){ // make some space
        // select a random node and replace this with the new page number
        q_node** array= (q_node**)malloc(sizeof(q_node*)*cache_size);
        int i=0;
        for (int indx= 0; indx< hash_size; indx++){
            if (hash->mapping[indx]!=NULL){
                array[i]= hash->mapping[indx];
                i++;
            }
        }
        int replace_page_num= get_random_index(0, cache_size-1);  // get a random number to replace
        // printf("random index selected is-- %d, and the value %d is to be replaced by %d\n", replace_page_num, array[replace_page_num]->page_number, page_num);
        hash->mapping[array[replace_page_num]->page_number]=NULL;
        array[replace_page_num]->page_number= page_num;
        hash->mapping[page_num]=array[replace_page_num];

    }
    else
        hash->mapping[page_num]= enqueue(cur_queue, page_num);
    return 0;
}

