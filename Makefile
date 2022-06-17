CC = gcc

derle: ./TreeFork.c
	$(CC) TreeFork.c -o TreeFork

objTreeFork: ./TreeFork.c
	$(CC) -c TreeFork.c -o TreeFork.o

calistir: ./TreeFork
	./TreeFork 2

cleanTxt:
	rm *.txt

cleanExe: 
	rm -f TreeFork

cleanObj:
	rm -f TreeFork.o

val:
	valgrind --tool=memcheck --leak-check=full ./TreeFork 2
