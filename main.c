#include "ds_list.h"
#include "ds_array.h"
#include "ds_memory.h"
#include <stdio.h>

int main(){

	ds_create("list.bin", 1000);
	ds_create_array();
	ds_init_array();
	ds_read_elements("numbers.txt");
	show_array();
	ds_finish_array();
	return 0;

}