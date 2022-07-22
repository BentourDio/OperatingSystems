#ifndef HASHTABLE
#define HASHTABLE

#include "index.h"

struct Hashtable {
    struct Hash_entry ** table;
    int size;
};

struct Hash_entry {
    // struct Index* index_ptr; /*deixnei sto vertix*/
    struct Hash_entry *next; /*sto epomeno entry tou bucket*/

    struct Student_Catalog* student_ptr;

    char* studentID;
    char* name;
    char* surname;
    int post_code;
    int entry_year;
    float gpa;
};

struct Hashtable Hashtable_Creation(int size);

int Htable_Insert(struct Hashtable h,char * studentID,
        char* name, char* surname, int post_code, float gpa, int entry_year, int size);

int Hash_key(char* name, int size);


void Print_Htable(struct Hashtable h);

void Print_Hash_Lists(struct Hash_entry* p);

struct Hash_entry* Hash_Search_St(char* studentID, struct Hash_entry* p);

void DestroyHashTable(struct Hashtable h);

void DestroyHashEntry(struct Hash_entry* ep);

void Htable_Delete_Student(struct Hashtable h,char* studentID, struct Index* student_index_ptr);


#endif

