C = gcc
CFLAGS = -O3 -Wall 
CFLAGS += -D_LARGEFILE_SOURCE
CFLAGS += -fno-exceptions
CFLAGS += -finline-functions
CFLAGS += -funroll-loops
CFLAGS += -D_FILE_OFFSET_BITS=64
CFLAGS += -std=c99
 
# Source files
WRITE_BLOCKS_SRC=write_blocks_seq.c
DISK_SORT_SRC=disk_sort.c
SORTED_RUN_SRC=sorted_run.c
 
# Binaries
all: write_blocks_seq disk_sort sorted_run
 
#sequential writing in blocks
write_blocks_seq: $(WRITE_BLOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o $@ 
disk_sort: $(DISK_SORT_SRC)
	$(CC) $(CFLAGS) $^ -o $@
sorted_run: $(SORTED_RUN_SRC)
	$(CC) $(CFLAGS) $^ -o $@
 

clean:  
	rm write_blocks_seq disk_sort sorted_run