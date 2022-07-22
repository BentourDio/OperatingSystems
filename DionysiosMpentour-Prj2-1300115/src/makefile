
# In order to execute this "Makefile" just type "make"
#

OBJS 	= recordList.o primes.o prime_list.o
SOURCE	= recordList.c main_root.c primes.c prime_list.c 
HEADER  = recordList.h primes.h prime_list.h 
OUT1 	= myprime
OUT2 	= child
OUT3	= grandchild
CC		= gcc
FLAGS   = -g -ggdb -c -ansi  -Wall -std=c89 -std=c99
FLAGS2  = -g -ggdb -ansi  -Wall -std=c89 -std=c99
LFLAGS	= -lm
# -g option enables debugging mode 
# -c flag generates object code for separate files

all:$(OUT1) $(OUT2) $(OUT3)

$(OUT1): main_root.o $(OBJS)
	$(CC) $(FLAGS2) main_root.o $(OBJS) -o $(OUT1) $(LFLAGS)

$(OUT2): main_child.o $(OBJS)
	$(CC) $(FLAGS2) main_child.o $(OBJS) -o $(OUT2) $(LFLAGS)

$(OUT3):main_grandchild.o $(OBJS)
	$(CC) $(FLAGS2) main_grandchild.o $(OBJS) -o $(OUT3) $(LFLAGS)

main_root.o: main_root.c
	$(CC) $(FLAGS) main_root.c

main_child.o: main_child.c
	$(CC) $(FLAGS) main_child.c

main_grandchild.o: main_grandchild.c
	$(CC) $(FLAGS) main_grandchild.c

recordList.o: recordList.c
	$(CC) $(FLAGS) recordList.c

primes.o: primes.c 
	$(CC) $(FLAGS) primes.c 

prime_list.o: prime_list.c 
	$(CC) $(FLAGS) prime_list.c 

# create/compile the individual files >>separately<< 



#valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all

clean:
	rm -f $(OBJS) main_root.o main_child.o main_grandchild.o $(OUT1) $(OUT2) $(OUT3)

run:
	./myprime -l 10 -u 100 -w 3
run2:
	./myprime -l 10 -u 100000 -w 30