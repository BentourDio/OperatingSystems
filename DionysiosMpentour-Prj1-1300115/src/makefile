
# In order to execute this "Makefile" just type "make"
# 

OBJS 	= app.o hashtable.o index.o main.o postcode_index.o
SOURCE	= app.c hashtable.c index.c main.c postcode_index.c
HEADER  = app.h hashtable.h index.h postcode_index.h
OUT  	= mngstd
CC	= gcc
FLAGS   = -g -ggdb -c -ansi  -Wall -std=c89 -std=c99

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

app.o: app.c
	$(CC) $(FLAGS) app.c

hashtable.o: hashtable.c
	$(CC) $(FLAGS) hashtable.c

index.o: index.c
	$(CC) $(FLAGS) index.c

postcode_index.o: postcode_index.c
	$(CC) $(FLAGS) postcode_index.c

valgrind:
	valgrind  --leak-check=full --show-leak-kinds=all ./mngstd -i file2.txt -c config.txt

run1:
	./mngstd -i file1.txt -c config.txt

run2:
	./mngstd -i file2.txt -c config.txt

clean:
	rm -f $(OBJS) $(OUT)