
// hash_size and NUM_UNIQUE_PAGES are the same
void run_all_policies(int page_refferences[], int cache_size, int hash_size, FILE* fp, int size);


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


void workload_random(int cache_size, int hash_size, FILE* fp){

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
}

void workload_looping(int cache_size, int hash_size, FILE* fp){

    int page_refferences[NUM_OF_PAGE_TO_REFFERENCE];
    for (int i=0; i< NUM_OF_PAGE_TO_REFFERENCE; i++){
        page_refferences[i]= i%50+1;
    }

    int size_= sizeof(page_refferences)/ sizeof(page_refferences[0]);
    run_all_policies(page_refferences, cache_size, hash_size, fp, size_);
}

void workload_80_20(int cache_size, int hash_size, FILE* fp){
    // 80% of the refferences are to the 20% and 20% refference are to the remaining 80%
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
}

