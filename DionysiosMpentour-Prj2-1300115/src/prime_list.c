/*

    Dionysios Mpentour 1115201300115
    Structs which contain the data for the prime numbers and functions to insert, print and
    delete structures.



*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "prime_list.h"


struct Prime_List* Create_Node(struct Prime_List* list_ptr, int number){

    struct Prime_List* temp;

    temp = (struct Prime_List*) malloc(sizeof (struct Prime_List));

    if (list_ptr == NULL) {//einai to prwto RecordID poy ginetai eggrafi
        temp->next = NULL;
        list_ptr = temp;
    } else {//eisagwgi stin arxi tis listas
        temp->next = list_ptr;
        list_ptr = temp;
    }

    temp->number = number;

    return list_ptr;
}

struct Prime_List* Create_Node_With_Time(struct Prime_List* list_ptr, int number, double t, int id) {
    struct Prime_List* temp;

    temp = (struct Prime_List*) malloc(sizeof (struct Prime_List));

    if (list_ptr == NULL) {//einai to prwto RecordID poy ginetai eggrafi
        temp->next = NULL;
        list_ptr = temp;
    } else {//eisagwgi stin arxi tis listas
        if (list_ptr->number)
        temp->next = list_ptr;
        list_ptr = temp;
    }

    temp->number = number;
    temp->t = t;
    temp->id = id;

    return list_ptr;
}

struct Prime_List* Insert_Orderly(struct Prime_List* list_ptr, int number, double t, int id){
    struct Prime_List* temp;

    temp = (struct Prime_List*) malloc(sizeof (struct Prime_List));

    struct Prime_List* current = list_ptr;

    temp->number = number;
    temp->t = t;
    temp->id = id;

//printf("\t\t\t\twtf\n");
    if (list_ptr == NULL) {//einai to prwto RecordID poy ginetai eggrafi
        temp->next = NULL;
        list_ptr = temp;
    } 
    else if(list_ptr->number > temp->number){
        temp->next =list_ptr;
        list_ptr = temp;
    }
    else {//eisagwgi se taxinomimeni lista
        while((current->next !=NULL) && (current->next->number < temp->number)){
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }
    return list_ptr;

}

void Destroy_Prime_List(struct Prime_List* list_ptr) {
    struct Prime_List * temp;
    struct Prime_List * next;
    temp = list_ptr;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    list_ptr = NULL;
}

void Print_Prime_List(struct Prime_List* list_ptr) {
    struct Prime_List* temp;
    temp = list_ptr;

    if (temp == NULL) {
        printf("RecordID is empty.\n");
    } else {
        while (temp != NULL) {
            printf("%d ", temp->number);
            temp = temp->next;
        }
    }
    printf("\n");
}

void Print_Prime_List_Ln(struct Prime_List* list_ptr,int lb,int ub) {
    struct Prime_List* temp;
    temp = list_ptr;
    printf("Primes in [%d,%d] are: ",lb,ub);
    if (temp == NULL) {
        printf("RecordID is empty.\n");
    } else {
        while (temp != NULL) {
            printf("%d %lf ", temp->number, temp->t);
            temp = temp->next;
        }
    }
    printf("\n");
}

void Print_Root(struct Prime_List* list_ptr){
    struct Prime_List* temp;
    temp = list_ptr;
    if (temp==NULL){
        printf("[ERROR] list empty\n");
        return;
    }
    else{
        while (temp!=NULL){
            double sum= temp->t;
            while (temp->next!=NULL && temp->id==temp->next->id){
                sum = sum + temp->t;
                temp = temp->next;
            }

            printf("Time for W%d: W%d-%lf msecs \n",temp->id,temp->id,sum);
            temp = temp->next;
        }
    }
}
