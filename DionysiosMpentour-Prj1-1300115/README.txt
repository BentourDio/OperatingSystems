DIONYSIOS MPENTOUR 1115201300115

In this project all data structures and functions that interact with the data have been implemented.In addition to the hashtable and the inverted index I have created a PostCodeIndex linked list which holds as data the zip code and the number of students that live in the area with that specific zip code.

My project consists of 14 files which are:
main.c 						#main function of the project
app.c app.h 					#application files which control the data structures
hashtable.c hashtable.h 			#files which has the hashtable struct definition and relevant functions
index.c index.h 				#files which has the index struct definition and relevant functions
postcode_index.c postcode_index.h  		#same as before for postcodeindex
file1.txt file2.txt 				#which are the files that were given to us for input in piazza 
makefile 					#separate compile
readme

To compile the project simply type make. 
You can run this project by typing make run1 or make run2 which will run the project with input file1.txt/file2.txt respectively. 
You can also run this project by typing 	make valgrind 		which will run it using valgrind and file2.txt

mngstd runs with no errors, warnings or valgrind errors

Running the mngstd i collect the number of lines in the input file which correspond to the multitude of student registries. So i set that to the size of hashtable entries as to avoid if possible all collisions.
Then i create the hashtable. the hashtable has 2 data. One is the size and the other a pointer to an array of pointers hash_entry which point to the simply linked list of Hash_entries. The Hash_entry is consisted of each student's information and a pointer to the student catalog(more to that will follow).

After that the Load_file function is called which reads the file line by line and inserts the information in the hashtable (I use the djb2 hashing function) and also creates each node of the simple linked index list. Index list's data consist of the entry year, the sum_gpa and the number of students with that entry year.
It also has a pointer a double linked list named student catalog. The Student Catalog's data is a Hash_entry pointer which points to the register's node of that student in the Hashtable. The Student_catalog list is ordered from lowest gpa to highest.
Lastly the postal code index is also created which is double linked list, which is also ordered from lowest number of students with that zip code to highest.

After the completion of the data structures command promt goes online and the user can interact with the programm via the command line.
All commands run as specified and also print the outcome as specified in piazza.

Insert: I insert the same way as in Load_File and all data structures get updated.

Delete: Deletion is completed after i search the student in the hastable. From the hashtable i have acces to the student catalog_list of the index so the deletion is completed in O(1). I then update the index and postcode numbers.

Number: The number of each year is kept in the index node, so i simply print that number after searching of the year index and confirming it has >0 students or actually exists.

Top: I have a kept a pointer which points to the last node of the catalog list of the index year. So i just print from there the number of students that are asked. the acess is O(1) because of that pointer.

Average: I keep the the total sum of the year's gpa in the index node so i just print the sum_gpa/number_students of that year.

Minimum: The first node of each year's index has the lowest gpa so i print him. I don't print if others have the same gpa as him in that year. I could implement it but because of lack of time I couldn't.

Count: Each index year has the number of students so no need to run the catalog list.

Post_Rank: Same as the Top function since it is ordered. I only print the 1 post node. If some areas antagonize for a rank while they have the same number of students living in their respective area, the one that is closer to end of the list is chosen. This could be fixed but as mentioned I didn't have much time to implement it.

Look_up: works as intented. I get the key from the studend id and the hash function and then i find the registry through the hashtable position.

Exit: the programm exits after deleting all data in ordered fashion.

custom
print: all the contents of each data structure get printed.

top (year): for that year print the ids of the students enrolled


make clean: deletes all files executables.
