/*

    Dionysios Mpentour 1115201300115
    Structures and functions about the named pipes.


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "recordList.h"

struct Record_list* Create_Record(struct Record_list* list_ptr, char* pipename) {

    struct Record_list* temp;

    temp = (struct Record_list*) malloc(sizeof (struct Record_list));

    if (list_ptr == NULL) {//einai to prwto RecordID poy ginetai eggrafi
        temp->next = NULL;
        list_ptr = temp;
    } else {//eisagwgi stin arxi tis listas
        temp->next = list_ptr;
        list_ptr = temp;
    }

    temp->pipeName = (char*) malloc(sizeof (char)*(strlen(pipename) + 1));
    strcpy(temp->pipeName, pipename);

    return list_ptr;
}

void Destroy_Record_list(struct Record_list* list_ptr) {
    struct Record_list * temp;
    struct Record_list * next;
    temp = list_ptr;
    while (temp != NULL) {
        next = temp->next;
        free(temp->pipeName);
        free(temp);
        temp = next;
    }
    list_ptr = NULL;
}

void Print_Record_List(struct Record_list* list_ptr) {
    struct Record_list* temp;
    temp = list_ptr;

    if (temp == NULL) {
        printf("RecordID is empty.\n");
    } else {
        while (temp != NULL) {
            printf("%s\n", temp->pipeName);
            temp = temp->next;
        }
    }
}

void Create_Pipes_From_List(struct Record_list* list_ptr) {
    struct Record_list* temp;
    temp = list_ptr;

    if (temp == NULL) {
        return;
    } else {
        while (temp != NULL) {
            unlink(temp->pipeName);
            
            int error = mkfifo(temp->pipeName, 0666);
            
            if (error== -1) {
                printf("Error while creating %s \n", temp->pipeName);
                exit(1);
            }
            temp = temp->next;
        }
    }
}

void Destroy_Pipes_From_List(struct Record_list* list_ptr) {
    struct Record_list* temp;
    temp = list_ptr;

    if (temp == NULL) {
        return;
    } else {
        while (temp != NULL) {
            unlink(temp->pipeName);
            
            temp = temp->next;
        }
    }
}
//
//struct Record_list* FindRecord(struct Record_list* r, char* recordID, int d, int m, int y) {
//    struct Record_list* temp;
//    temp = r;
//
//    while (temp != NULL) {
//        if (strcmp(temp->pipeID, recordID) == 0) {
//            if ((temp->exit_day == 0) || datecmp(d, m, y, temp->entry_day, temp->entry_month, temp->entry_year) > 0) {//which means the patient did not have exit date
//                temp->exit_day = d;
//                temp->exit_month = m;
//                temp->exit_year = y;
//                return r;
//            }
//        }
//        temp = temp->next;
//    }
//    printf("recordID did not match any patient\n");
//    return r;
//}
//
//int CheckRecordID(struct Record_list* r, char* recordID) {
//    struct Record_list* temp;
//    temp = r;
//
//    while (temp != NULL) {
//        if (strcmp(temp->pipeID, recordID) == 0) {
//            //printf("the taken recordID is %s with country %s and the append recordID is %s\n",temp->recordID,temp->country,recordID);
//            return -1;
//        }
//        temp = temp->next;
//    }
//    //printf("recordID did not match any patient\n");
//    return 0;
//}
