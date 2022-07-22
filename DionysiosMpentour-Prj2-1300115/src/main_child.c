/*

    Dionysios Mpentour 1115201300115

    This is the intermmidiate between the coordinator and the workers
    This file collects invokes the workers and collects data from them to send
    to root programm



*/





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#include "prime_list.h"

// ./myprime -l lb -u ub -w NumofChildren

//int main_grandchild(int argc, char** argv){}

int main(int argc, char** argv) {
    int lb, ub, w;
    int i, identity;
    int prime_f = 0;
    int numbers;
    int cb; //current bound for worker
    int j; //integer to set the id of each worker

    if (argc != 7 && argc != 8) {
        printf("[Error] Wrong arguments Given (%d) \nExiting\n", argc);
        return -1;
    }

    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            lb = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-u") == 0) {
            ub = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-w") == 0) {
            w = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-id") == 0) {
            identity = atoi(argv[i + 1]);
        }
    }

  //  printf("            the identity is %d\n", identity);

    numbers = (ub - lb) / w; //einai to plithos ari8mwn poy 8a analabei ka8e worker
    j = w;
    //printf("[##########]            THE NUMBERS ARE %d\n",numbers );


    char * outputpipe = "bla";
    char * inputpipes = "blue";

    printf("Child %d started: [%d,%d] with %d children per node: writing to pipe: %s, reading pipes: %s \n", identity, lb, ub, w, outputpipe, inputpipes);

    pid_t pids[w];

    //    printf("Child %d : creating processes ... [%d, %d] \n", identity, l, );

    for (int i = 0; i < w; i++) {

        prime_f++;
        j--;


        if (prime_f == 4)
            prime_f = 1;

        if (i == 0)
            cb = lb;
        else
            cb = cb + numbers;

        pid_t childpid = fork();




        if (childpid == 0) {


            // int child_argc = 9;
            char childlb[15];
            char childub[15];
            char childw[15];
            char id[15];
            char pf[5];

            if (i == 0) {
                sprintf(childlb, "%d", cb);
            } else {
                sprintf(childlb, "%d", cb +1); //gia na apofugw to diplotupo ston 1o ari8mo tou kato oriou
            }

            sprintf(id, "%d", identity * w + i);
            sprintf(childw, "%d", w);

            if (i == w - 1)//dld o teleutaios worker
                sprintf(childub, "%d", ub);
            else
                sprintf(childub, "%d", cb + numbers);

            sprintf(pf, "%d", prime_f);

            //char * child_argv[] = {
            //  "main_grandchild", "-l", childlb, "-u", childub, "-w", childw, "3", "-id", id
            //};

            // child => exec

            execl("./grandchild", "-l", childlb, "-u", childub, "-w", childw, "-id", id, "-p", pf, NULL);
            printf("wtf happened\n");
            //  int j =  main_grandchild(child_argc, child_argv);
            //printf("gchild procces with pid:%d \n",getpid());
            return 0;
        } else {
            pids[i] = childpid;
        }
    }

    // open pipes with parent
    int pipe_fd_parent;

    char pipename[4000];
    sprintf(pipename, "c_%d.pipe", identity);

    pipe_fd_parent = open(pipename, O_WRONLY);


    // open pipes with grandchildren
    int * pipe_fds_grandchildren = malloc(sizeof (int)*w);

    for (int i = 0; i < w; i++) {
        char pipename[4000];
        sprintf(pipename, "gc_%d.pipe", identity * w + i);

        pipe_fds_grandchildren[i] = open(pipename, O_RDONLY);
    }



    // retrieve results and store to list
    printf("Child %d: collecting results ... \n", identity);

    struct Prime_List* plist = NULL;

    double cpu_time = 0.0;

    for (int i = 0; i < w; i++) {
        int no;

        while (true) {
            read(pipe_fds_grandchildren[i], &no, sizeof (no));

            if (no == -1) {
                break;
            } else {
                double t;
                int id;
                read(pipe_fds_grandchildren[i], &t, sizeof (t));
                read(pipe_fds_grandchildren[i], &id, sizeof (id));

                plist = Insert_Orderly(plist, no, t, id);
            }
        }

        read(pipe_fds_grandchildren[i], &cpu_time, sizeof (cpu_time));
    }

    // forward result to parent

    struct Prime_List* temp = plist;

    while (temp != NULL) {
        write(pipe_fd_parent, &temp->number, sizeof (temp->number));
        write(pipe_fd_parent, &temp->t, sizeof (temp->t));
        write(pipe_fd_parent, &temp->id, sizeof (temp->id));
        temp = temp->next;
    }
    //printf("\tthis is fukin child\n");
    //Print_Prime_List_Ln(plist);

    int donkey = -1;

    write(pipe_fd_parent, &donkey, sizeof (donkey));

    write(pipe_fd_parent, &cpu_time, sizeof (cpu_time));

    close(pipe_fd_parent);

    printf("Child %d: Waiting for processes ... \n", identity);


    for (int i = 0; i < w; i++) {
        waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < w; i++) {
        close(pipe_fds_grandchildren[i]);
    }

    close(pipe_fd_parent);

    Destroy_Prime_List(plist);

    printf("Child %d exited\n", identity);

    free(pipe_fds_grandchildren);

    return 0;
}
