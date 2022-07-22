#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "app.h"
#include "index.h"
#include "hashtable.h"
#include "postcode_index.h"

int table_size;

static struct Hashtable htable; //global hashtable struct

static struct Index* index_ptr = NULL; //global index pointer

static struct PostCodeIndex* postcode_index_ptr = NULL;

void set_tableSize(FILE* fp) {
    int lines = 1;
    int ch;

    while (!feof(fp)) {
        ch = fgetc(fp);

        if (ch == '\n') {
            lines++;
        }
    }
    table_size = lines;
    printf("THE TABLE SIZE IS %d\n", lines);
}

void Create_Htable() {
    htable = Hashtable_Creation(table_size);
}

void Load_File(FILE * fp) {
    char studentID[500];
    char name[500];
    char surname[500];
    int postal_code;
    int entry_year;
    float gpa;

    int f;


    int counter = 0;

    while (1) {
        if (fscanf(fp, "%s %s %s %d %d %f", studentID, name, surname, &postal_code, &entry_year, &gpa) != 6) {
            break;
        }

        printf("inserting: %s \n", studentID);

        if (Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]) != NULL) {
            printf("[Warning] register failed for id: %s  (already exists) ", studentID);
            continue; // exit if needed
        }

        f = Htable_Insert(htable, studentID, name, surname, postal_code,
                gpa, entry_year, htable.size);
        if (f == -1) {
            printf("### register failed for id: %s  (error) ", studentID);
            exit(1);
        }

        struct Hash_entry* htable_ptr = Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]);

        struct Index* index_temp = Search_Indexes(index_ptr, entry_year);

        if (index_temp == NULL) {//den uparxei kapoio index me auto to date
            index_ptr = InsertIndex(index_ptr, entry_year); //to entry year brisketai sthn 1h 8esh gia auth thn eggrafh

            index_temp = index_ptr;
        }

        Insert_Catalog(index_temp, htable_ptr);

        //
        struct PostCodeIndex * postcode_temp = Search_PostCode(postcode_index_ptr, postal_code);

        if (postcode_temp == NULL) {
            postcode_index_ptr = Insert_PostCode(postcode_index_ptr, postal_code);
        } else {
            postcode_temp->counter++;
            if(postcode_temp->next!=NULL && postcode_temp->next->counter <= postcode_temp->counter  ){
                int temp_postcode = postcode_temp->postcode;
                int temp_post_counter = postcode_temp->counter;
                //swap the data between two objects
                postcode_temp->counter = postcode_temp->next->counter;
                postcode_temp->postcode = postcode_temp->next->postcode;
                postcode_temp->next->postcode = temp_postcode;
                postcode_temp->next->counter = temp_post_counter;
            }
        }

        counter++;

        // printf("%s|%s|%s|%d|%d|%f\n", studentID, name, surname, postal_code,entry_year,gpa);


    }

    //printf("Processed lines: %d \n", counter);

}

void Print_Index() {
    struct Index* temp;
    temp = index_ptr;

    while (temp != NULL) {
        printf("The year of this index is %d\n", temp->entry_year);
        Print_Index_Catalog(temp);
        temp = temp->next;

    }
}

void Print_Postcode_Index() {
    struct PostCodeIndex* temp;
    temp = postcode_index_ptr;

    while (temp != NULL) {
        printf("The postcode %d has %d\n", temp->postcode, temp->counter);
        temp = temp->next;

    }
}

void APP_Print_Htable() {
    Print_Htable(htable);
}

void Command_Prompt() {
    char buffer[2048];
    printf("Command Prompt is online\n");
    while (1) {
        printf("..>");

        if (fgets(buffer, sizeof (buffer), stdin) == NULL) {
            break;
        }

        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        if ((strcmp(buffer, "print")) == 0) {
            printf("----------------------------Hashtable\n");
            APP_Print_Htable();
            printf("----------------------------INDEX\n");
            Print_Index();
            printf("----------------------------POST\n");
            Print_Postcode_Index();
        }

        if (strcmp(buffer, "exit") == 0) {            
            break;
        }
        if (strncmp(buffer, "insert", 6) == 0 || buffer[0] == 'i') {
            char *p1;
            char *p2;
            char *p3;
            char *p4;
            char *p5;
            char *p6;
            char *p7;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");
            p3 = strtok(NULL, " \t");
            p4 = strtok(NULL, " \t");
            p5 = strtok(NULL, " \t");
            p6 = strtok(NULL, " \t");
            p7 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL && p5 != NULL && p6 != NULL && p7 != NULL) {
                Insert_Student(p2, p3, p4, atoi(p5), atoi(p6), atof(p7));
            }
        }
        if (strncmp(buffer, "look-up", 7) == 0 || buffer[0] == 'l') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Look_Up(p2);
            }
        }
        if (strncmp(buffer, "delete", 6) == 0 || buffer[0] == 'd') {
            char *p1;
            char *p2;


            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Delete_Student(p2);
            }
        }
        if (strncmp(buffer, "number", 6) == 0 || buffer[0] == 'n') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Number_Year(atoi(p2));
            }
        }
        if (strncmp(buffer, "top", 3) == 0 || buffer[0] == 't') {
            char *p1;
            char *p2;
            char *p3;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");
            p3 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL && p3 != NULL) {
                Top_Num_Year(atoi(p3), atoi(p2));
            }
        }
         if (buffer[0] == 's') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Top_Num_Year(atoi(p2), -1);
            }
        }
        if (strncmp(buffer, "average", 7) == 0 || buffer[0] == 'a') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Average_Year(atoi(p2));
            }
        }
        if (strncmp(buffer, "minimum", 7) == 0 || buffer[0] == 'm') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                Minimum_Year(atoi(p2));
            }
        }
        if (strncmp(buffer, "count", 5) == 0 || buffer[0] == 'c') {
            char *p1;

            p1 = strtok(buffer, " \t");

            if (p1 != NULL) {
                Count();
            }
        }
        if (strncmp(buffer, "postal code", 11) == 0 || buffer[0] == 'p') {
            char *p1;
            char *p2;

            p1 = strtok(buffer, " \t");
            p2 = strtok(NULL, " \t");

            if (p1 != NULL && p2 != NULL) {
                //TODO postal code/ it prints 1 object and not all if student_num== 2zip
                Post_Rank(atoi(p2));
            }
        }
    }
    //end while
    printf("    -exit programm\n");
    Exit();
}

//functions of command promt

void Look_Up(char* studentID) {
    struct Hash_entry * temp;
    temp = Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]);
    if (temp != NULL) {
        printf("%s %s %s %d %d %f\n",temp->studentID, temp->surname, temp->name, temp->post_code, temp->entry_year, temp->gpa);
    } else
        printf("    - Student %s does not exist\n", studentID);

}

void Insert_Student(char* studentID, char* name, char* surname, int postal_code, int entry_year, float gpa) {
    int f;

    if (Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]) != NULL) {
        printf("    - Student %s exists\n", studentID);
        return; // exit if needed
    }

    f = Htable_Insert(htable, studentID, name, surname, postal_code,
            gpa, entry_year, htable.size);
    if (f == -1) {
        printf("### register failed for id: %s  (error) ", studentID);
        exit(1);
    }

    struct Hash_entry* htable_ptr = Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]);

    struct Index* index_temp = Search_Indexes(index_ptr, entry_year);

    if (index_temp == NULL) {//den uparxei kapoio index me auto to date
        index_ptr = InsertIndex(index_ptr, entry_year); //to entry year brisketai sthn 1h 8esh gia auth thn eggrafh

        index_temp = index_ptr;
    }

    Insert_Catalog(index_temp, htable_ptr);

    //
    struct PostCodeIndex * postcode_temp = Search_PostCode(postcode_index_ptr, postal_code);

    if (postcode_temp == NULL) {
        postcode_index_ptr = Insert_PostCode(postcode_index_ptr, postal_code);
    } else {
        postcode_temp->counter++;
        if(postcode_temp->next!=NULL && postcode_temp->next->counter <= postcode_temp->counter  ){
            int temp_postcode = postcode_temp->postcode;
            int temp_post_counter = postcode_temp->counter;
            //swap the data between two objects
            postcode_temp->counter = postcode_temp->next->counter;
            postcode_temp->postcode = postcode_temp->next->postcode;
            postcode_temp->next->postcode = temp_postcode;
            postcode_temp->next->counter = temp_post_counter;
        }
    }
    printf("    - Student %s  inserted\n", studentID);
}

void Delete_Student(char* studentID) {
    struct Hash_entry* temp = Hash_Search_St(studentID, htable.table[Hash_key(studentID, htable.size)]);
    if (temp == NULL) {
        printf("    - Student %s does not exist\n", studentID);
        return; // exit if needed
    }

    postcode_index_ptr = PostCode_Delete_Student(postcode_index_ptr, temp->post_code);

    struct Index* student_index_ptr = Index_Delete_Student(index_ptr, temp->entry_year, studentID, temp->gpa);

    Htable_Delete_Student(htable, studentID, student_index_ptr);

    printf("    - Record %s deleted\n",studentID);
}

void Number_Year(int year) {
    struct Index* temp;
    temp = Search_Indexes(index_ptr, year);
    if (temp != NULL) {
        printf("- %d student(s) in %d\n",temp->num_students,temp->entry_year);
    } else{
        if(temp==NULL || temp->num_students==0)
        printf("    - No students enrolled in %d\n",year);
    }
}

void Top_Num_Year(int year, int num) {
    struct Index* temp;
    temp = Search_Indexes(index_ptr, year);
    if (temp == NULL || temp->num_students==0) {
        printf("    - No students enrolled in %d\n",year);
        return;
    }
    struct Student_Catalog* temp2 = temp->catalog_last_ptr;
   // printf("Top_Num_Year %d\n", year);
    
    if (num != -1) {//a custom mode for debugging for me as i had some issues with previous pointers
        for (int i = 0; i < num && temp2 != NULL; i++) {
            printf("    -list (%s)\n",
                    temp2->htable_ptr->studentID/* temp2->htable_ptr->name, temp2->htable_ptr->surname, temp2->htable_ptr->entry_year, temp2->htable_ptr->post_code, temp2->htable_ptr->gpa*/);
            temp2 = temp2->previous;
        }
    } else {
        temp2 = temp->catalog_last_ptr;
        for (int i = 0; temp2 != NULL; i++) {
            printf("    -list (%s)\n", temp2->htable_ptr->studentID/* temp2->htable_ptr->name, temp2->htable_ptr->surname, temp2->htable_ptr->entry_year, temp2->htable_ptr->post_code, temp2->htable_ptr->gpa*/);
            temp2 = temp2->previous;
        }
    }
        
}

void Average_Year(int year) {
    struct Index* temp;
    temp = Search_Indexes(index_ptr, year);
    if (temp == NULL||temp->num_students==0) {
        printf("    - No students enrolled in %d\n",year);
        return;
    }

    //ave_gpa = (temp->sum_gpa/num_students);
    printf("    -%f\n",(temp->sum_gpa / temp->num_students));
}

void Minimum_Year(int year) {
    struct Index* temp = Search_Indexes(index_ptr, year);

    if (temp == NULL||temp->num_students==0) {
        printf("    - No students enrolled in %d\n",year);
    }
    else
        printf("    - list(%s)\n",temp->catalog_first_ptr->htable_ptr->studentID);
}

void Count() {
    struct Index* temp = index_ptr;
    while (temp != NULL) {
        if(temp->num_students==0)
            printf("       -No stundets enrolled in %d\n",temp->entry_year);

        printf("    - list ({%d , %d})\n", temp->entry_year, temp->num_students);
        temp = temp->next;
    }
}

void Post_Rank(int num) {
    if(num>0)
        PrintRank(postcode_index_ptr,num);
    else
        printf("dont mess with me\n");
}

void Exit() {
    DestoyPostIndex(postcode_index_ptr);
    Destroy_Index(index_ptr);
    DestroyHashTable(htable);
}