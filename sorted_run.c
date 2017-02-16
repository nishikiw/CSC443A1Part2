#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "merge.h"


int compare (const void *a, const void *b) {
	Record one = *(Record*)a;
	Record two = *(Record*)b;
	int a_f = one.UID2;
	int b_f = two.UID2;
	return (a_f - b_f);
}


void sort(Record * buffer, int total_records){
	/**
	* Arguments:
	* 1 - an array to sort
	* 2 - size of an array
	* 3 - size of each array element
	* 4 - function to compare two elements of the array
	*/
	qsort(buffer, total_records, sizeof(Record), compare);
}




void phase1(char* input_file, int mem_size, int block_size){

	FILE *fp_read, *fp_write;
	int total_records;
    int left_records;
    int main_available;
    int num_records_chunk;

    if(block_size > mem_size){
    	exit(0);
    }
    // how many memory Main memory can hold (exclude memory for qsort)
    main_available = mem_size / 2;

    // the number of records in one buffer read
    int num_of_blocks =  main_available / block_size;
    num_records_chunk = num_of_blocks * block_size / sizeof(Record);
    

    // allocate a buffer in main
    Record * buffer = (Record *) calloc (num_records_chunk, sizeof (Record));

	if (!(fp_read= fopen (input_file , "r" ))) {
		printf ("Could not open file \"%s\" for reading \n", input_file);
		exit(0);
    }

    /*first get the size of opening file*/
    fseek(fp_read, 0, SEEK_END);
    int file_size = ftell(fp_read);
	total_records = file_size / sizeof(Record);

    fseek(fp_read, 0, SEEK_SET); 
  
    
    left_records = total_records;
    int load_records;
    int chunck_num = 1;
    while(left_records > 0){
        // read records into main memory and sort them
        load_records=fread(buffer, sizeof(Record), num_records_chunk, fp_read);
  
		if (load_records > 0){
			 //sort records in main memory
    	    sort(buffer, load_records);
    	    //write sorted list into disk
    	    char string[25];
    	    sprintf(string, "sorted_list%d.dat", chunck_num);
    	    
    	    if (!(fp_write = fopen ( string , "wb" ))) {  
    	    	printf ("Could not open file \"sorted_list\" for reading \n");
    	    	exit(0);
    	    }
    	    fwrite (buffer, sizeof(Record), load_records, fp_write);
    	    fclose(fp_write);
		}
	
		printf("next_round: \n\n\n");

		//decrement on the left_records
		left_records -= load_records;
		chunck_num ++;
	}

	free(buffer);
	fclose(fp_read);


}



int main(int argc, char **argv) {

	char *input_file = argv[1];
	int mem_size = atoi(argv[2]);
    int block_size = atoi(argv[3]);
    phase1(input_file, mem_size, block_size);

}







