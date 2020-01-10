/*
Name: Nicholas Sturk
Email: nsturk@uoguelph.ca
student id: 1058650
*/

#include "ds_memory.h"
#include <stdio.h>

struct ds_counts_struct{

    int reads;
    int writes;

};

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size){

    FILE *fp = fopen(filename, "wb+");
    if (fp == NULL) {
        return 1;
    }
    int i = 0;

    for (i = 0; i < MAX_BLOCKS; ++i){
        struct ds_blocks_struct block;
        block.length = i == 0 ? size : 0;
        block.start = 0;
        block.alloced = '0';
        fwrite(&block, sizeof(struct ds_blocks_struct), 1, fp);
    }

    fwrite("0", 1, size, fp);

    fclose(fp);

    return 0;
}

int ds_init(char *filename){

    int i = 0;
    ds_file.fp = fopen(filename, "rb+");
    if (ds_file.fp == NULL){
        return 1;
    }

    for (i = 0; i < MAX_BLOCKS; ++i){
        fread(&ds_file.block[i], sizeof(struct ds_blocks_struct), 1,
              ds_file.fp);
    }

    ds_counts.reads = 0;
    ds_counts.writes = 0;

    return 0;
}

long ds_malloc(long amount){

    int i;
    for (i = 0; i < MAX_BLOCKS; ++i){
        if (ds_file.block[i].length >= amount && ds_file.block[i].alloced == '0'){
            long tempL = ds_file.block[i].length;
            ds_file.block[i].length = amount;
            ds_file.block[i].alloced = '1';
            int j;
            for (j = 0; j < MAX_BLOCKS; ++j){
                if (ds_file.block[j].length == 0){
                    ds_file.block[j].start = ds_file.block[i].start + amount;
                    ds_file.block[j].length = tempL - amount;
                    return ds_file.block[i].start;
                }
            }
        }
    }
    return -1;
}

void ds_free(long start){

    int i = 0;
    for(i = 0; i < MAX_BLOCKS; ++i){
        if(ds_file.block[i].start == start){
            ds_file.block[i].alloced = '0';
        }
    }
}

void *ds_read(void *ptr, long start, long bytes){

    fseek(ds_file.fp, 0, SEEK_END);
    int check = ftell(ds_file.fp);
    if(start + bytes > check){
        return NULL;
    }

    fseek(ds_file.fp, sizeof(struct ds_blocks_struct) * 4096 + start, SEEK_SET);
    fread(ptr, 1, bytes, ds_file.fp);
    ds_counts.reads += 1;
    return ptr;
}

long ds_write(long start, void *ptr, long bytes){

    fseek(ds_file.fp, 0, SEEK_END);
    int check = ftell(ds_file.fp);
    if(start + bytes > check){
        return -1;
    }

	fseek(ds_file.fp, sizeof(struct ds_blocks_struct) * 4096 + start, SEEK_SET);
	fwrite(ptr, 1, bytes, ds_file.fp);
	ds_counts.writes += 1;
	return start;
}

int ds_finish(){

	int i = 0;
	fseek(ds_file.fp, 0, SEEK_SET);
	for(i = 0; i < MAX_BLOCKS; ++i){
		fwrite(&ds_file.block[i], sizeof(struct ds_blocks_struct), 1, ds_file.fp);
	}
	printf("reads: %d\n", ds_counts.reads);
	printf("writes: %d\n", ds_counts.writes);

	i = fclose(ds_file.fp);
    if(i == 0){
        return 1;
    } else{
        return 0;
    }
}

void ds_test_init(void){

    int i;
    printf("Block #     start     length     alloced\n");
    for(i = 0; i < 20; ++i){
        printf("      %d        %ld          %ld          %c\n", i, 
        ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
    }

    printf("\nreads = %d\n", ds_counts.reads);
    printf("\nwrites = %d\n", ds_counts.writes);
}





















