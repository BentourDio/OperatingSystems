#Dionysios Mpentour 1115201300115
#This is a simple makefile. Just type "make" to compile the programm


OBJS 	= main.o functions.o
SOURCE	= main.c functions.c
HEADER  = functions.h
OUT		= quic
CC		= gcc
FLAGS   = -g -ggdb -c -Wall
FLAGS2  = -l

# -g option enables debugging mode
# -c flag generates object code for separate files

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.c
	$(CC) $(FLAGS) main.c

funtions.o: funtions.c
	$(CC) $(FLAGS) funtions.c

run:
	./quic -v -d -l -f 0 source dest

run2:
	./quic -v -d -l -f 1 source dest 


valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./quic -v -d -l -f 0 source dest

clean:
	rm -f $(OBJS) main.o funtions.o $(OUT)