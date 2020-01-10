/*
Name: Nicholas Sturk
Email: nsturk@uoguelph.ca
student id: 1058650
*/

#include <stdio.h>
#include "ds_array.h"
#include "ds_memory.h"

long elements;

int ds_create_array(){
	int x;
	x = ds_init("numbers.txt");
	if(x == 1){
		return -1;
	} else{
		long temp = 0;
		temp = ds_malloc(sizeof(long));
		ds_write(temp, &temp, 8);
		ds_malloc(sizeof(int) * MAX_ELEMENTS);
		x = ds_finish();
		if(x == 0){
			return -1;
		} else{
			return 0;
		}
	}
}


int ds_init_array(){
	int x = ds_init("array.bin");
	if(x == 1){
		return -1;
	}else{
		ds_read(&elements, 0, sizeof(long));
		return 0;
	}
}


int ds_replace(int value, long index){
	if (index > elements || index < 0){
		return -1;
	} else{
		ds_write(index * 4 + 8, &value, 4);
		return 0;
	}
}


int ds_insert(int value, long index){
	if (index > elements + 1 || index < 0 || index > MAX_ELEMENTS){
		return -1;
	} else{

		int i;
		int old;
		int new;
		long temp;
		new = value;
		elements += 1;

		for(i = index; i < elements; i++){
			temp = i * sizeof(int) + 8;
			ds_read(&old, temp, 4);
			ds_write(temp, &new, 4);
			new = old;
		}
		return 0;
	}
}


int ds_delete(long index){
	if (index > elements || index < 0 || index > MAX_ELEMENTS){
		return -1;
	} else{
		int i;
		long temp;
		long next;
		int new;
		for(i = index; i < elements - 1; i++){
			temp = i * sizeof(int) + 8;
			next = i * sizeof(int) + 12;
			ds_read(&new, next, sizeof(int));
			ds_write(temp, &new, sizeof(int));
		}

		elements -= 1;
		return 0;
	}
}


int ds_swap(long index1, long index2){
	if(index1 > elements || index2 > elements || index1 < 0 || index2 < 0){
		return -1;
	} else{
		int val1;
		int val2;
		long pos1;
		long pos2;

		pos1 = index1 * 4 + 8;
		pos2 = index2 * 4 + 8;

		ds_read(&val1, pos1, 4);
		ds_read(&val2, pos2, 4);

		ds_write(pos2, &val1, 4);
		ds_write(pos1, &val2, 4);

		return 0;
	}
}


long ds_find(int target){
	long pos;
	int check;
	long i;
	for (i = 0; i < elements; i++){
		pos = i * 4 + 8;
		ds_read(&check, pos, 4);
		if (check == target) {
			return i;
		}
	}
	return -1;
}


int ds_read_elements(char *filename){
	FILE *fp = fopen(filename, "r");
	int i = 0;
	int temp;
	while(!feof (fp)){
		fscanf(fp, "%d", &temp);
		ds_insert(temp, i);
		i++;
	}
	if(i > MAX_ELEMENTS || fp == NULL){
		return -1;
	}
	fclose(fp);
	return 0;
}


int ds_finish_array(){
	ds_write(0, &elements, 8);
	int x = ds_finish();
	if(x == 1){
		return -1;
	} else{
		return 0;
	}
}

void show_array(void){
	ds_test_init();
	printf("\nelements = %ld\n\n", elements);
	int i, tempVal, tempPos;
	for(i = 0; i < elements; i++){
		tempPos = i * 4 + 8;
		ds_read(&tempVal, tempPos, 4);
		printf("%d :  %d\n", i, tempVal);
	}

	printf("\n");
}

