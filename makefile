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
MERGE_EXTERNAL_SRC=merge_external.c
MAIN_SRC=main.c
READ_RAM_SEQ_SRC=read_ram_seq.c
 
# Binaries
all: write_blocks_seq read_ram_seq main
 
#sequential writing in blocks
write_blocks_seq: $(WRITE_BLOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o $@ 
read_ram_seq: $(READ_RAM_SEQ_SRC)
	$(CC) $(CFLAGS) $^ -o $@ 
main: $(DISK_SORT_SRC) $(SORTED_RUN_SRC) $(MERGE_EXTERNAL_SRC) $(MAIN_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:  
	rm write_blocks_seq main sorted_list*.dat records_sorted.dat read_ram_seq