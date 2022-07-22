/*

    Dionysios Mpentour 1115201300115
    
    This is the root file which invokes all the other programms and collects
    the data and prints them.



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
#include <float.h>

#include "recordList.h"
#include "prime_list.h"

// ./myprime -l lb -u ub -w NumofChildren
// ./root -l 10 -u 100 -w 3
//int main_child(int argc, char** argv);

int main(int argc, char** argv) {
    int lb, ub, w;

    if (argc != 7) {
        printf("[Error] Wrong arguments Given\nExiting\n");
        return -1;
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            lb = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-u") == 0) {
            ub = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-w") == 0) {
            w = atoi(argv[i + 1]);
        }
    }

    int pipes = w * (w + 1);
    int numbers = (ub - lb) / w; //plithos ari8mos pou 8a metafer8ei ston coordinator
    int cb; //current bound

    struct Record_list* pipe_list_ptr = NULL;

    printf("Root started: [%d,%d] with %d children per node with %d pipes  \n", lb, ub, w, pipes);

    printf("Root: creating pipes ... \n");

    char pipename[4000];

    for (int i = 0; i < w; i++) {
        sprintf(pipename, "c_%d.pipe", i);
        pipe_list_ptr = Create_Record(pipe_list_ptr, pipename);
    }

    for (int i = 0; i < pipes - w; i++) {
        sprintf(pipename, "gc_%d.pipe", i);
        pipe_list_ptr = Create_Record(pipe_list_ptr, pipename);
    }

    Create_Pipes_From_List(pipe_list_ptr);

    pid_t pids[w];

    printf("Root: creating processes ... \n");

    for (int i = 0; i < w; i++) {

        if (i == 0)
            cb = lb;
        else
            cb = cb + numbers;

        pid_t childpid = fork();

        if (childpid == 0) {
        //    int child_argc = 9;
            char childlb[15];
            char childub[15];
            char childw[15];
            char id[10];

            sprintf(id, "%d", i);
            sprintf(childw, "%d", w);

            if (i == 0)
                sprintf(childlb, "%d", cb);
            else
                sprintf(childlb, "%d", cb + 1);
            if (i == w - 1)
                sprintf(childub, "%d", ub);
            else
                sprintf(childub, "%d", cb + numbers);

            // child => exec
            execl("./child", "-l", childlb, "-u", childub, "-w", childw, "-id", id, NULL);

            return 0;
        } else {
            pids[i] = childpid;
        }
    }

    // open pipes with children
    int * pipe_fds_children = malloc(sizeof (int)*w);

    for (int i = 0; i < w; i++) {
        char pipename[4000];
        sprintf(pipename, "c_%d.pipe", i);

        pipe_fds_children[i] = open(pipename, O_RDONLY);
    }


    // retrieve results and store to list
    printf("Root: collecting results ... \n");

    struct Prime_List* plist = NULL;

    double min_cpu_time = DBL_MAX;
    double max_cpu_time = 0.0;

   // double cpu_time[w];
    
    for (int i = 0; i < w; i++) {
        int no;

        while (true) {
            read(pipe_fds_children[i], &no, sizeof (no));
    
    //        printf("%d ",no);

            if (no == -1) {
                break;
            } else {
                double t;
                int id;
                read(pipe_fds_children[i], &t, sizeof (t));
                read(pipe_fds_children[i], &id, sizeof (id));

                plist = Insert_Orderly(plist, no, t, id);
            
                if (t < min_cpu_time) {
                    min_cpu_time = t;
                }
            
                if (t > max_cpu_time) {
                    max_cpu_time = t;
                }
            }
        }

        double cpu_time_temp;

        read(pipe_fds_children[i], &cpu_time_temp, sizeof (cpu_time_temp));
        
      //  cpu_time[i] = cpu_time_temp;
        
    }


    printf("Root: Waiting for processes ... \n");

    for (int i = 0; i < w; i++) {
        waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < w; i++) {
        close(pipe_fds_children[i]);
    }

    // print results
    printf("\n[EXPECTED OUTPUT]\n\n");

    Print_Prime_List_Ln(plist,lb,ub);
    
    printf("Min time: %lf\n", min_cpu_time);
    
    printf("Max time: %lf\n", max_cpu_time);
    
    printf("Num of USR1 Received: Not implemented\n");
    
    Print_Root(plist);
    
    printf("\n[END OF EXPECTED OUTPUT]\n\n");
   

   /* for (int i = 0; i < w; i++) {
        printf("Time of worker %d was %lf msec \n", i, cpu_time[i]);
    }
    */
    // # print times for all workers
    
    // clean up

    

    printf("Root: deleting pipes ... \n");
    
    Destroy_Pipes_From_List(pipe_list_ptr);

    Destroy_Prime_List(plist);

    Destroy_Record_list(pipe_list_ptr);
    
    printf("Root exited\n");

    free(pipe_fds_children);

    return 0;
}

