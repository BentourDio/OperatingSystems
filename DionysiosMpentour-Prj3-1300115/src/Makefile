
# In order to execute this "Makefile" just type "make"
#

OBJS 	  = 
SOURCE	= 	
HEADER  = 	
OUT1 	  = chef
OUT2 		= saladmaker
CC			= gcc
FLAGS   = -g -ggdb -c -ansi  -Wall -std=c89 -std=c99
FLAGS2  = -g -ggdb -ansi  -Wall -std=c89 -std=c99
LFLAGS	= -lm -lpthread
# -g option enables debugging mode
# -c flag generates object code for separate files

all:$(OUT1) $(OUT2)

$(OUT1): chef.o $(OBJS)
	$(CC) $(FLAGS2) chef.o $(OBJS) -o $(OUT1) $(LFLAGS)

$(OUT2): saladmaker.o $(OBJS)
	$(CC) $(FLAGS2) saladmaker.o $(OBJS) -o $(OUT2) $(LFLAGS)

chef.o: chef.c
	$(CC) $(FLAGS) chef.c

saladmaker.o: saladmaker.c
	$(CC) $(FLAGS) saladmaker.c $(FLAGS2)



# create/compile the individual files >>separately<<
run:
	./chef -n 10 -m 2


#valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all

clean:
	rm -f $(OBJS) chef.o saladmaker.o $(OUT1) $(OUT2)