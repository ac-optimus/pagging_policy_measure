/* fifo implementation using doubly linked list
enter the queue using enqueue at front  and get dequeue from rear*/



// node structure
typedef struct _q_node{
    unsigned page_number; // the page number stored in this QNode
    struct _q_node *nxt;
    struct _q_node *prev;
}q_node;


// queue data structure
typedef struct _queue{
    q_node* rear;
    q_node* front;
    int filled;
    int size;
}queue;



// create a queue
queue* create_queue(int size){
    // creates an istance of struct queue
    queue* cur_queue= (queue*)(malloc(sizeof(queue)));
    cur_queue->size= size;
    cur_queue->filled= 0;
    cur_queue->front= cur_queue->rear= NULL;
    return cur_queue;
}


//check if queue is empty
int is_empty(queue* cur_queue){
    // return 0 if queue is not empty else return 1
    if (cur_queue->rear == NULL)  // nothing to dequeu
        return 1;
    return 0;
}


int is_full(queue* cur_queue){
    // return 1 if queue is full else return 0
    if (cur_queue->filled== cur_queue->size)
        return 1;
    return 0;
}


// enqueue
q_node* enqueue(queue* cur_queue, int enqueue_val){
    // if fail return 1, else return 1
    // adds to the front
    if (is_full(cur_queue)==1){
        printf("Queue already full\n");
        return NULL;
    }

    q_node* new_queue_node= (q_node*)malloc(sizeof(q_node));
    new_queue_node->page_number= enqueue_val;
    cur_queue->filled+=1;
    // add to the front
    if (is_empty(cur_queue))
        cur_queue->front= cur_queue->rear= new_queue_node;
    else{
        cur_queue->front->prev= new_queue_node;
        new_queue_node->nxt= cur_queue->front;
        cur_queue->front= new_queue_node;
    }
    return new_queue_node;
}

// dequeue
int dequeue(queue* cur_queue){
    // return the value at the rear of the queue
    // if queue is empty return a message that is empty
    // can not deqeue if already empty
    if (is_empty(cur_queue)){
        printf("Nothing inside the queue\n");
        return -1;
    }
    // remove elment from the rear
    q_node* node= cur_queue->rear;
    int val= node->page_number;

    if (cur_queue->rear== cur_queue->front)
        cur_queue->rear= cur_queue->front = NULL; // the queue is empty now
    else
    // have atleast two elements
        cur_queue->rear= cur_queue->rear->prev;
    free(node);
    // printf("----%d---\n",cur_queue->filled);
    cur_queue->filled-=1;
    // printf("----%d---\n",cur_queue->filled);
    return val;
}


