#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "a1.h"

/**
* Compares two records a and b 
* with respect to the value of the integer field f.
* Returns an integer which indicates relative order: 
* positive: record a > record b
* negative: record a < record b
* zero: equal records
*/
int compare (const void *a, const void *b) {
	Record one = *(Record*)a;
	Record two = *(Record*)b;
	int a_f = one.uid2;
	int b_f = two.uid2;
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


// Print all the records in order in the buffer.
void print_records(Record * buffer, int total_records){
	for (int i = 0; i < total_records; i++){
		printf("uid2 = %d, uid1 = %d\n", buffer[i].uid2, buffer[i].uid1);
	}
}


int main(int argc, char **argv){
	
	FILE *fp_read;
	
	char *file_name = argv[1];			// Get the binary file's name.
	int buffer_size = atoi(argv[2]);	// Get the buffer size. Note that block size is 4KB.
	
	int num_records = buffer_size / sizeof(Record);
	Record * buffer = (Record *) calloc (num_records, sizeof (Record));
	
	/* open text file for reading */
    if (!(fp_read= fopen ( file_name , "r" ))) {
		printf ("Could not open file \"%s\" for reading \n", file_name);
		return (-1);
    }
	
	/*first get the size of opening file*/
    fseek(fp_read, 0, SEEK_END);
    int file_size = ftell(fp_read);
	int total_records = file_size / sizeof(Record);
	if (num_records > total_records){
		num_records = total_records;
	}
    fseek(fp_read, 0, SEEK_SET); 
	
	if (fread(buffer, sizeof(Record), num_records, fp_read) > 0){
		//printf("Original records:\n");
		//print_records(buffer, num_records);
		
		sort(buffer, num_records);
		
		//printf("Records sorted by uid2:\n");
		//print_records(buffer, num_records);
	}
	else{
		printf ("Could not read file \"%s\".\n", file_name);
		return (-1);
	}
	
	return 0;
}