#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "merge.h"


void phase1(char* input_file, int mem_size, int block_size){

	FILE *fp_read, *fp_write;
	int total_records;
    int left_records;
    int main_available;
    int num_records_chunk;


    if(block_size > mem_size){
    	exit(1);
    }

    // how many memory Main memory can hold (exclude memory for qsort)
    main_available = mem_size / 2;

    // the number of records in one buffer read
    int num_of_blocks =  main_available / block_size;
    int num_records_chunk = num_of_blocks * block_size / sizeof(Record);
    

    // allocate a buffer in main
    Record * buffer = (Record *) calloc (num_records_chunk, sizeof (Record));

	if (!(fp_read= fopen (input_file , "r" ))) {
		printf ("Could not open file \"%s\" for reading \n", file_name);
		return (-1);
    }

    /*first get the size of opening file*/
    fseek(fp_read, 0, SEEK_END);
    int file_size = ftell(fp_read);
	int total_records = file_size / sizeof(Record);
    fseek(fp_read, 0, SEEK_SET); 
    
 
    left_records = total_records;

    int load_records;
    while(left_records > 0){
        // read records into main memory and sort them
        load_records=fread(buffer, sizeof(Record), num_records_block, fp_read);

		if (load_records > 0){

			 //sort records in main memory
    	    sort(buffer, load_records);

    	    //write sorted list into disk
    	    if (!(fp_write = fopen ( "sorted_list.dat" , "wb" ))) {  
    	    	printf ("Could not open file \"records.dat\" for reading \n");
    	    	return (-1);
    	    }
    	    fwrite (buffer, sizeof(Record), load_records, fp_write);

		}
		//decrement on the left_records
		left_records = total_records - load_records;
	}
}



int main(int argc, char **argv) {

	char *input_file = argv[1];
	int mem_size = atoi(argv[2]);
    int block_size = atoi(argv[3]);
    phase1(input_file, mem_size, block_size);

}







