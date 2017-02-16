#include "merge.h"

int main (int argc, char **argv) {
	//process and validate command-line arguments

	MergeManager manager;
	
	char *input_prefix = argv[1];
	int num_trunks = atoi(argv[2]);
	int main_memory = atoi(argv[3]);
	int block_size = atoi(argv[4]);
	
	
	int buffer_size_temp = main_memory/(num_trunks+1);
	
	int buffer_capacity = 
	

	//initialize all fields according to the input and the results of Phase I
	return merge_runs (&manager);
}