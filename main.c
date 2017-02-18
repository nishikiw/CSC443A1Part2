#include "merge.h"


int main (int argc, char **argv) {
	//process and validate command-line arguments

	MergeManager manager;
	
	char *input_prefix = "sorted_list";
	
	char *input_file = argv[1];
	int mem_size = atoi(argv[2]);
    int block_size = atoi(argv[3]);
    int num_trunks = phase1(input_file, mem_size, block_size, input_prefix);
	printf("start test with memory size: %dMB  block size Byte: %d\n", mem_size/1024/1024, block_size);
	int blocks_per_buffer = mem_size/(num_trunks+1) / block_size;
	if (blocks_per_buffer < 1){
		printf("Main memory size too small for merging.\n");
		exit(1);
	}
	int buffer_capacity = blocks_per_buffer * block_size / sizeof(Record);

	//initialize all fields according to the input and the results of Phase I
	return merge_runs (&manager, num_trunks, input_prefix, buffer_capacity);
}