/*
Name: Nicholas Sturk
Email: nsturk@uoguelph.ca
student id: 1058650
*/

#include <stdio.h>
#define MAX_BLOCKS 4096

struct ds_blocks_struct {
    long start;
    long length;
    char alloced;
};

struct ds_file_struct {
    FILE *fp;
    struct ds_blocks_struct block[MAX_BLOCKS];
};

int ds_create(char *filename, long size);
int ds_init(char *filename);
long ds_malloc(long amount);
void ds_free(long start);
void *ds_read(void *ptr, long start, long bytes);
long ds_write(long start, void *ptr, long bytes);
int ds_finish();
void ds_test_init(void);
