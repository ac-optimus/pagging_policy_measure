#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include "replacement_policies.h"
#include "workload.c"
#include "policy.c"
// #include "definitions.h"



int main(int argc, char* argv[])
{
	// create a workoad
	// pass a flag alond with the workload as argument to use LRU Approx as well.
	WorkloadsT p= LOOP;
    FILE* fp;
	int use_LRUapprox=0;
	if (argc==3){   // add LRU Approx in analysis
		use_LRUapprox=1;
			// printf("enters\n");
			if (strcmp(argv[1], "RANDOM")==0){ // RANDOM
				p = RANDOM;
				fp = fopen("summary/workload_random_LRUapprox.csv", "a");
			}
			else if (strcmp(argv[1], "LOCAL")==0){ // 80-20
				p= LOCAL;
				fp = fopen("summary/workload_local_LRUapprox.csv", "a");
			}
			else if (strcmp(argv[1], "LOOP")==0){ // LOOPING
				p= LOOP;
				fp = fopen("summary/workload_looping_LRUapprox.csv", "a");
			}
		}
		else{
			if (strcmp(argv[1], "RANDOM")==0){ // RANDOM
				p = RANDOM;
				fp = fopen("summary/workload_random.csv", "a");
			}
			else if (strcmp(argv[1], "LOCAL")==0){ // 80-20
				p= LOCAL;
				fp = fopen("summary/workload_local.csv", "a");
			}
			else if (strcmp(argv[1], "LOOP")==0){ // LOOPING
				p= LOOP;
				fp = fopen("summary/workload_looping.csv", "a");
			}
		}

	struct workload* w= generate_workload(p, NUM_UNIQUE_PAGES, 10000);
    fprintf(fp, "RANDOM,LRU,FIFO,LRU_APPROX\n");
	// call the policies
	float hit_rate_fifo, hit_rate_lru, hit_rate_random, hit_rate_lru_approx;

    for (int cache_size=1; cache_size<=NUM_UNIQUE_PAGES; cache_size++){
		hit_rate_fifo= policy_FIFO(w, cache_size);
		// add for LRU, LRU_APPROX and RANDOM
		hit_rate_lru= policy_LRU(w, cache_size);
		hit_rate_random= policy_RANDOM(w, cache_size);
		if (use_LRUapprox== 1){
			hit_rate_lru_approx= policy_LRUapprox(w, cache_size);
			fprintf(fp, "%f, %f, %f, %f\n", hit_rate_random, hit_rate_lru, hit_rate_fifo, hit_rate_lru_approx);
		}
		else
		    fprintf(fp, "%f, %f, %f\n", hit_rate_random, hit_rate_lru, hit_rate_fifo);
	}
	fclose(fp);
	return 0;
}