/*
Name: Nicholas Sturk
Email: nsturk@uoguelph.ca
student id: 1058650
*/

#include <stdio.h>
#include "ds_list.h"
#include "ds_memory.h"

void ds_create_list(){

	ds_init("list.bin");
	long temp = -1;
	ds_malloc(sizeof(long));
	ds_write(0, &temp, sizeof(long));
	ds_finish();
}

int ds_init_list(){
	int x = ds_init("list.bin");
	if (x == 1){
		return -1;
	} else{
	return 0;
	}
}

int ds_replace(int value, long index){

	struct ds_list_item_struct new;
	long pos;

	pos = traverse_list(index);
	if(pos == -1){
		return -1;
	} else{
		ds_read(&new, pos, sizeof(struct ds_list_item_struct));
		new.item = value;
		ds_write(pos, &new, sizeof(struct ds_list_item_struct));
		return 0;
	}

}

int ds_insert(int value, long index){

	struct ds_list_item_struct previous;
	struct ds_list_item_struct new;

	long previous_loc = 0;
	int i;

	ds_read(&previous.next, 0, sizeof(long));

	for(i = index; i > 0; i--){
		if(previous.next == -1){
			return -1;
		} else{
			previous_loc = previous.next;
			ds_read(&previous, previous_loc, sizeof(struct ds_list_item_struct));
		}
	}

	new.item = value;
	new.next = previous.next;

	previous.next = ds_malloc(sizeof(struct ds_list_item_struct));
	ds_write(previous.next, &new, sizeof(struct ds_list_item_struct));

	if(previous_loc == 0){
		previous_loc = previous.next;
		ds_write(0, &previous_loc, sizeof(long));
	} else{
		ds_write(previous_loc, &previous, sizeof(struct ds_list_item_struct));
	}

	return 0;
}

int ds_delete(long index){

	struct ds_list_item_struct old;
	struct ds_list_item_struct new;
	long pos = traverse_list(index);

	if(pos == -1){
		return -1;
	} else{
		ds_read(&old, pos, sizeof(struct ds_list_item_struct));
		ds_read(&new, old.next, sizeof(struct ds_list_item_struct));
		old = new;
		ds_free(pos);
		ds_write(pos, &old, sizeof(struct ds_list_item_struct));
		return 0;
	}


return 0;
}

int ds_swap(long index1, long index2){

	int item1, item2;
	long pos1, pos2;

	struct ds_list_item_struct struct_one;
	struct ds_list_item_struct struct_two;

	pos1 = traverse_list(index1);
	pos2 = traverse_list(index2);

	if (pos1 == -1 || pos2 == -1){
		return -1;
	} 

	ds_read(&struct_one, pos1, sizeof(struct ds_list_item_struct));
	ds_read(&struct_two, pos2, sizeof(struct ds_list_item_struct));

	item1 = struct_one.item;
	item2 = struct_two.item;

	struct_two.item = item1;
	struct_one.item = item2;

	ds_write(pos1, &struct_one, sizeof(struct ds_list_item_struct));
	ds_write(pos2, &struct_two, sizeof(struct ds_list_item_struct));
	
	return 0;
}

long ds_find(int target){
	struct ds_list_item_struct previous;
	long previous_loc;
	long i = 0;

	ds_read(&previous.next, 0, sizeof(long));

	while(1 == 1){
		if(previous.next == -1){
			return -1;
		} else{
			previous_loc = previous.next;
			ds_read(&previous, previous_loc, sizeof(struct ds_list_item_struct));
			if(previous.item == target){
				break;
			}
		}
		i++;
	}
	return i;
}

int ds_read_elements(char *filename){
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		return -1;
	}
	int i = 0;
	int temp;
	while(!feof (fp)){
		fscanf(fp, "%d\n", &temp);
		ds_insert(temp, i);
		i+=1;
	}
	fclose(fp);
return 0;
}

int ds_finish_list(){
	int x = ds_finish();
	if (x == 0){
		return -1;
	}
return 0;	
}

void show_list(){
	long loc = 0;
	struct ds_list_item_struct li;
	ds_test_init();
	ds_read(&loc, 0, sizeof(long));
	while(loc != -1){
		ds_read(&li, loc, sizeof(li));
		printf("\nloc = %ld item = %d next = %ld\n", loc, li.item, li.next);
		loc = li.next;
	}
}

long traverse_list(long index){
	struct ds_list_item_struct previous;
	long previous_loc;
	int i;

	ds_read(&previous.next, 0, sizeof(long));

	for(i = index; i > 0; i--){
		if(previous.next == -1){
			return -1;
		} else{
			previous_loc = previous.next;
			ds_read(&previous, previous_loc, sizeof(struct ds_list_item_struct));
		}
	}
	return previous.next;
}









