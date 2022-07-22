#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"

struct Hashtable Hashtable_Creation(int size) {
    struct Hashtable h;
    int i;


    h.table = (struct Hash_entry**) malloc(sizeof (struct Hash_entry*)*size);

    for (i = 0; i < size; i++) {
        h.table[i] = NULL;
    }

    h.size = size;

    return (h);
}

int Htable_Insert(struct Hashtable h, char * studentID, char* name, char* surname, int post_code, float gpa, int entry_year, int size) {
    int pos;

    struct Hash_entry *entry, *temp;

    pos = Hash_key(studentID, size);

    if (h.table[pos] == NULL) {//create new hash list
        entry = (struct Hash_entry *) malloc(sizeof (struct Hash_entry));
        if (entry != NULL) {
            entry->studentID = malloc(sizeof (char)*(strlen(studentID) + 1));
            strcpy(entry->studentID, studentID);
            entry->next = NULL;

            entry->name = malloc(sizeof (char)*(strlen(name) + 1));
            strcpy(entry->name, name);

            entry->surname = malloc(sizeof (char)*(strlen(surname) + 1));
            strcpy(entry->surname, surname);

            entry->post_code = post_code;

            entry->entry_year = entry_year;

            entry->gpa = gpa;


        } else
            return -1;

        h.table[pos] = entry;
        return 0;
    }
    //insert in existing hash list
    temp = h.table[pos]; //inserting at the first item of the list
    entry = (struct Hash_entry *) malloc(sizeof (struct Hash_entry));
    if (entry != NULL) {
        entry->studentID = malloc(sizeof (strlen(studentID) + 1));
        strcpy(entry->studentID, studentID);
        entry->next = temp; //new entry now points to first entry of list

        entry->name = malloc(sizeof (char)*(strlen(name) + 1));
        strcpy(entry->name, name);

        entry->surname = malloc(sizeof (char)*(strlen(surname) + 1));
        strcpy(entry->surname, surname);

        entry->post_code = post_code;

        entry->entry_year = entry_year;

        entry->gpa = gpa;
    } else
        return -1;
    h.table[pos] = entry;

    return 0;
}

/*hash function with returns a key for the hash array
//        djb2
//http://www.cse.yorku.ca/~oz/hash.html
//*/
int Hash_key(char* name, int size) {
    unsigned long hash = 5381;
    int c = 0;

    while (1) {
        c = *name;
        name++;
        if (c == '\0') {
            break;
        }
        hash = ((hash << 5) + hash) + c;
    }

    hash = hash % size;


    return (hash);
}

void Print_Htable(struct Hashtable h) {
    //struct Hashtable temp;
    for (int i = 0; i < h.size; i++) {
        Print_Hash_Lists(h.table[i]);
    }

}

void Print_Hash_Lists(struct Hash_entry* p) {
    struct Hash_entry* temp;
    temp = p;
    while (temp != NULL) {
        printf("studentID=%s|name=%s|surname=%s|postal code=%d|average grade=%f|entry year=%d\n ", temp->studentID,
                temp->name, temp->surname, temp->post_code, temp->gpa, temp->entry_year);
        temp = temp->next;
    }//TODO prepei na balw to entry date giati den exw prosbasi sto index apo edw
}

struct Hash_entry* Hash_Search_St(char* studentID, struct Hash_entry* p) {
    struct Hash_entry *temp;

    temp = p;
    while (temp != NULL) {
        if (strcmp(temp->studentID, studentID) == 0)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

void DestroyHashTable(struct Hashtable h) {
    int i;
    struct Hash_entry* temp;

    for (i = 0; i < h.size; i++) {

        temp = h.table[i];

        DestroyHashEntry(temp);
    }
    free(h.table);

}

void DestroyHashEntry(struct Hash_entry* ep) {
    struct Hash_entry* temp, *aux;
    temp = ep;
    while (temp != NULL) {
        aux = temp;
        temp = temp->next;
        free(aux->studentID);
        free(aux->name);
        free(aux->surname);
        free(aux);
    }
}

void Htable_Delete_Student(struct Hashtable h, char* studentID, struct Index* student_index_ptr) {
    struct Hash_entry* temp; // = Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]);
    struct Hash_entry* aux;
    struct Hash_entry* prev = NULL;
    /*if (temp == NULL) {
        printf("[Warning] register failed for id: %s  (doesn't exist) ", studentID);
        return; // exit if needed
    }*/
    temp = h.table[Hash_key(studentID, h.size)];
    while (temp != NULL) {
        if (strcmp(temp->studentID, studentID) == 0) {
            aux = temp;
            /*
             i delete the object in index list from here 
             since i have access and i update head later
             */

            if (aux->student_ptr == student_index_ptr->catalog_first_ptr && aux->student_ptr == student_index_ptr->catalog_last_ptr) {
                student_index_ptr->catalog_first_ptr = NULL;
                student_index_ptr->catalog_last_ptr = NULL;
            } else if (aux->student_ptr == student_index_ptr->catalog_first_ptr) {
                student_index_ptr->catalog_first_ptr = student_index_ptr->catalog_first_ptr->next;
                student_index_ptr->catalog_first_ptr->previous = NULL;
            } else if (aux->student_ptr == student_index_ptr->catalog_last_ptr) {
                student_index_ptr->catalog_last_ptr = student_index_ptr->catalog_last_ptr->previous;
                student_index_ptr->catalog_last_ptr->next = NULL;
            } else {
                aux->student_ptr->previous->next = aux->student_ptr->next;
                aux->student_ptr->next->previous = aux->student_ptr->previous;
            }
            
            if (aux == h.table[Hash_key(studentID, h.size)]){
                if (prev != NULL) {
                    printf("world does not make sense \n");
                    exit(7);
                }
                h.table[Hash_key(studentID, h.size)] = h.table[Hash_key(studentID, h.size)]->next;
            } else {
                prev->next = prev->next->next;
            }


            free(aux->student_ptr);
            free(aux->studentID);
            free(aux->name);
            free(aux->surname);
            free(aux);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}