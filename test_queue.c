
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

int main(void){
    queue* cur_queue= create_queue(10); // queue of size 10
    int status;
    status= dequeue(cur_queue); // dequeue from an empty queue
    // enqueuee(0);
    printf("-------------------time to enqueue-------------------\n");
    q_node* status1;
    for (int i=0; i<12; i++){
        status1= enqueue(cur_queue, i);
        if (status1!=NULL)
            printf("enqueued -- %d\n", status1->page_number);
        else
            printf("can not enqueue\n");
    }
    // time to deque them
    printf("-------------------time to dequeue-------------------\n");
    for (int j=0; j<19; j++){
        status= dequeue(cur_queue);
        printf("value/status is -- %d\n", status);
    }
    return 0;
}