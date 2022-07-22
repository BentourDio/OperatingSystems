#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "index.h"
#include "hashtable.h"

struct Index* InsertIndex(struct Index* p, int entry_year) {
    struct Index* newIndex = NULL;

    newIndex = (struct Index*) malloc(sizeof (struct Index));

    newIndex->entry_year = entry_year;
    newIndex->num_students = 0;
    newIndex->sum_gpa = 0;

    newIndex->next = p;
    
    newIndex->catalog_first_ptr = NULL;
    newIndex->catalog_last_ptr = NULL;

    return newIndex;
}

void Insert_Catalog( struct  Index *p, struct Hash_entry* htable_ptr) {
    struct Student_Catalog* newStudentCatalog = NULL;

    newStudentCatalog = (struct Student_Catalog *) malloc(sizeof (struct Student_Catalog));

    newStudentCatalog->previous = NULL;
    newStudentCatalog->next = NULL;

    newStudentCatalog->htable_ptr = htable_ptr;
    htable_ptr->student_ptr = newStudentCatalog;

    //if ( htable_ptr->entry_year == 2014) {
       // printf("  ############# inserting to year: %d, record with id: %s \n", htable_ptr->entry_year, htable_ptr->studentID);
    //}

    if (p->catalog_first_ptr == NULL) {/*first item of the list*/
        p->num_students = 1;
        p->sum_gpa = htable_ptr->gpa;
        p->catalog_first_ptr = newStudentCatalog;
        p->catalog_last_ptr = newStudentCatalog;//krataw edw to last
        
    } else {/*insert somwhere in ordered linked list*/
        p->num_students++;
        p->sum_gpa = p->sum_gpa + htable_ptr->gpa;
        
        if(htable_ptr->gpa <= p->catalog_first_ptr->htable_ptr->gpa){
            newStudentCatalog->next = p->catalog_first_ptr;

            p->catalog_first_ptr->previous = newStudentCatalog;//to first allazei me ka8e eggrafi

            p->catalog_first_ptr = newStudentCatalog;
        }
        else if(htable_ptr->gpa >= p->catalog_last_ptr->htable_ptr->gpa){
            
            newStudentCatalog->previous = p->catalog_last_ptr;

            p->catalog_last_ptr->next = newStudentCatalog;

            p->catalog_last_ptr = newStudentCatalog;
        }
        else{
            struct Student_Catalog* temp;
            temp = p->catalog_first_ptr;
            
            while (temp!=p->catalog_last_ptr){
                if(htable_ptr->gpa <= temp->next->htable_ptr->gpa){
                    newStudentCatalog->previous=temp;
                    newStudentCatalog->next=temp->next;
                    temp->next->previous=newStudentCatalog;
                    temp->next=newStudentCatalog;
                    return;
                }
                temp=temp->next;
            }
        }

        
    }

 //   printf("item inserted\n");
}


void Print_Index_Catalog(struct Index* p) {
    struct Student_Catalog* temp;

    if (p == NULL)
        printf("Index is empty\n");
    else {
        printf("Index: students: %d  sumgpa: %f  entry_year:%d \n", p->num_students, p->sum_gpa, p->entry_year);

        temp = p->catalog_first_ptr;
        while (temp != NULL) {
            printf("%s|%s|%s|%d|%f\n", temp->htable_ptr->studentID, temp->htable_ptr->name, temp->htable_ptr->surname, temp->htable_ptr->post_code, temp->htable_ptr->gpa);
            temp = temp->next;
        }
    }
}

struct Index* Search_Indexes(struct Index* index_ptr, int entry_year) {
    struct Index* temp;
    temp = index_ptr;

    while (temp != NULL) {
        if (temp->entry_year == entry_year)
            return temp;
        else
            temp = temp->next;
    }
    return NULL;
}

void Destroy_Index(struct Index* p) {
    struct Index* temp = p;
    struct Index* aux;
    while(temp!=NULL){
        aux=temp;
        DestroyStudentCatalog(aux->catalog_first_ptr);
        temp=temp->next;
        free(aux);
    }

}

void DestroyStudentCatalog(struct Student_Catalog* p)
{
    struct Student_Catalog* temp = p;
    struct Student_Catalog* aux;
    while(temp!=NULL){
        aux=temp;
        temp=temp->next;
        free(aux);
    }
   //free(temp);
}

struct Index* Index_Delete_Student(struct Index* p,int entry_year,char* studentID, float gpa)
{
    struct Index* index_temp =Search_Indexes(p,entry_year);
   // struct Student_Catalog* student_temp = Search_Student(p,studentID);
    //struct Student_Catalog* aux;

    index_temp->num_students--;
    index_temp->sum_gpa = index_temp->sum_gpa - gpa;
    
//    if (index_temp->num_students == 0) { // ???
//        
//    }

    //aux=temp;
    //student_temp->previous->next = student_temp->next;
    //student_temp->next->previous = student_temp->previous;
    //free(student_temp);

    return index_temp;

}

struct Student_Catalog* Search_Student(struct Index* p, char* studentID) {
    struct Index* temp;
    temp = p;
    while (temp->catalog_first_ptr != NULL) {
        if (strcmp(temp->catalog_first_ptr->htable_ptr->studentID, studentID) == 0)
            return (temp->catalog_first_ptr);
        temp->catalog_first_ptr = temp->catalog_first_ptr->next;

    }
    return NULL;
}