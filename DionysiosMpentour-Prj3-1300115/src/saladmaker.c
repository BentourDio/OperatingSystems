/*

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
#include <semaphore.h>

#include <sys/shm.h>


//./saladmaker -t1 lb -t2 ub -s shmid

int main(int argc, char **argv) {

    int lb, ub, shm_id, id;
    char processFile[100];
    clock_t start, end;
    double cpu_used;
    char logFile[20];

    if (argc != 9) {
        printf("[Error] Wrong arguments Given\nExiting\n");
        return -1;
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t1") == 0) {
            lb = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-t2") == 0) {
            ub = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-s") == 0) {
            shm_id = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-id") == 0) {
            id = atoi(argv[i + 1]);
        }
    }
    //naming the files for the logging
    sprintf(processFile,"saladmaker%d with pid: %d",id, getpid());

    sprintf(logFile,"%d", shm_id);
    //creating a unique process logfile
    FILE *fp1 = fopen(processFile,"a");

    printf("Saladmaker%d: started with arguments: ID:%d, SHMID:%d, %d %d \n", id, id, shm_id, lb, ub);


    /* Attach the segment */
    char * mem = (char *) shmat(shm_id, (void*) 0, 0);
    char * ptr = mem;

    if (*(int *) mem == -1) {
        perror("Salad maker: Attachment.");
        return -1;
    } else {
        printf("Saladmaker%d: Just Attached Shared Memory whose content is: %d \n", id, *mem);
    }

    sem_t * semlock_P = (sem_t*) (ptr + sizeof (int));
    sem_t * semlock_C = (sem_t*) (ptr + sizeof (int) + (id + 1) * sizeof (sem_t));

    int salads = 0;
    start = clock();
    while (true) {
        int temp;
        FILE* ftemp;
        ftemp = fopen(logFile,"a");
        
        end = clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(ftemp,"[00:00:00:%lf] [%d] [Saladmaker%d]: [waiting for ingredients]  \n",cpu_used, getpid(), id);
        //      CS start
        sem_wait(semlock_C);
        end = clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(ftemp,"[00:00:00:%lf] [%d] [Saladmaker%d]: [get ingredients]  \n",cpu_used, getpid(), id);
        fprintf(ftemp,"[00:00:00:%lf] [%d] [Saladmaker%d]: [start making salad]  \n",cpu_used, getpid(), id);
        memcpy(&temp, ptr, sizeof (int));//copying the nymber of salads to temp
        if (temp == 0) {
            sem_post(semlock_P);
            break;
        }
        
        temp--;
        memcpy(ptr, &temp, sizeof (int));

        salads++;
        end = clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(ftemp,"[00:00:00:%lf] [%d] [Saladmaker%d]:salad %d complete... \n",cpu_used, getpid(),id, salads);
        
      /*  end = clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        printf("time online has been %lf\n",cpu_used);
        fprintf(ftemp, "%lf secs used by maker %d and salad number %d\n", cpu_used*(10^5), id, salads);
*/
        fclose(ftemp);
        sem_post(semlock_P);

        //      CS end
        end = clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(fp1,"[00:00:00:%lf] [%d] [Saladmaker%d] [completed salad %d\n",cpu_used, getpid(), id,salads);

        if (temp == 0) {
            break;
        }
    }

    printf("Salad maker %d finished, Total salads: %d \n", id, salads);
    fclose(fp1);


    return 0;
}