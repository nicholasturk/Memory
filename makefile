all: ds_memory.o ds_array.o main.o
	gcc ds_memory.o ds_array.o main.o -o run

ds_memory.o: ds_memory.c ds_memory.h
	gcc -Wall -ansi ds_memory.c -c -o ds_memory.o


ds_list.o: ds_list.c ds_list.h
	gcc -Wall -ansi ds_list.c -c -o ds_list.o


ds_array.o: ds_array.c ds_array.h
	gcc -Wall -ansi ds_array.c -c -o ds_array.o

main.o: main.c ds_array.h ds_list.h ds_memory.h
	gcc -Wall -ansi main.c -c -o main.o

clean:
	rm *.o
