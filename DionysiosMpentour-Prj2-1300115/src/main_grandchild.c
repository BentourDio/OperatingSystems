/*

    Dionysios Mpentour 1115201300115

    Worker file. Receives data from main_child.c and invokes the functions
    to find the prime numbers



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
#include <sys/times.h>

#include "primes.h"
#include "prime_list.h"
// ./myprime -l lb -u ub -w NumofChildren -p primeFunction

int main(int argc, char** argv) {
    // printf("main_grandchild entered\n");
    int lb, ub, w;
    int i, id = getpid();
    int p_num = 0;

    //double t1, t2, cpu_time;
    //struct tms tb1, tb2;
    //double ticspersec;

    //ticspersec = (double) sysconf(_SC_CLK_TCK);
    //t1 = (double) times(&tb1);

    //  printf("the arguments are %d\n",argc);

    if (argc != 7 && argc != 10) {
        printf("[Error] Wrong arguments Given\nExiting\n");
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
            id = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-p") == 0) {
            p_num = atoi(argv[i + 1]);
        }

    }

    char pipename[4000];

    printf("Grandchild %d started: [%d,%d], pipe: gc_%d.pipe with %d children per node \n", id, lb, ub, id, w);
    sprintf(pipename, "gc_%d.pipe", id);

    int pipe_fd = open(pipename, O_WRONLY);



    struct Prime_List* plist = NULL;

    if (p_num == 1) {
        plist = prime1(plist, lb, ub,id);

    }
    if (p_num == 2) {
        plist = prime2(plist, lb, ub,id);
    }
    if (p_num == 3) {
        // printf("THIS IS PRIME3\n");
        plist = prime3(plist, lb, ub,id);
    }


   // Print_Prime_List_Ln(plist);

   // t2 = (double) times(&tb2);
   // cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));
  double  cpu_time = 0;
    // semd results

    struct Prime_List* temp = plist;

    while (temp != NULL) {
        write(pipe_fd, &temp->number, sizeof(temp->number));
        write(pipe_fd, &temp->t, sizeof(temp->t));
        write(pipe_fd, &temp->id, sizeof(temp->id));
        temp = temp->next;
    }

    int donkey = -1;

    write(pipe_fd, &donkey, sizeof(donkey));

    write(pipe_fd, &cpu_time, sizeof(cpu_time));

    close(pipe_fd);

    //destroy functions
    Destroy_Prime_List(plist);



    //printf("Run time was %lf sec (REAL time) although we used the CPU for %lf sec (CPU time).\nGrandchild %d exited\n",
      //      (t2 - t1) / ticspersec, cpu_time / ticspersec, id);

    return 0;
}
