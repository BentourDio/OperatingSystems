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
#include <sys/ipc.h>
#include <sys/shm.h>


#include <semaphore.h>

//./saladmaker -t1 lb -t2 ub -s shmid
//./chef -n numOfSlds -m mantime

//int main_saladmaker(int argc, char **argv);

int main(int argc, char **argv) {
    int salads, mantime;
    double cpu_used;
    //int ingr0 = 0, ingr1 = 0, ingr2 = 0;
    FILE* fp;
    char sharedFile[20];
    clock_t start, end;

    srand(time(0));

    if (argc != 5) {
        printf("[Error] Wrong arguments Given\nExiting\n");
        return -1;
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            salads = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-m") == 0) {
            mantime = atoi(argv[i + 1]);
        }
    }
    // num salad, ingredient 1 & 2 & 3 +_4 semaphores
    int MEMORY_SIZE = sizeof (int) + 4 * sizeof (sem_t);

    int shm_id = shmget(IPC_PRIVATE, MEMORY_SIZE, 0666 | IPC_CREAT);

    sprintf(sharedFile,"%d",shm_id);

    /* Attach the segment */
    char * mem = (char *) shmat(shm_id, (void*) 0, 0);

   // printf("salads are %d\n",salads);

    memcpy(mem, &salads, sizeof (int));


    if (*(int *) mem == -1) {
        perror("Attachment.");
        return -1;
    } else {
        printf("Just Attached Shared Memory whose content is: %d\n",*mem);
    }

    char * ptr = mem;

    printf("initializing memory segment with id: %d  \n", shm_id);

    
    //memcpy(ptr, &salads, sizeof (int));

    sem_t * semlock_P = (sem_t*) (ptr + sizeof (int));
    sem_t * semlock_1 = (sem_t*) (ptr + sizeof (int) + 1 * sizeof (sem_t));
    sem_t * semlock_2 = (sem_t*) (ptr + sizeof (int) + 2 * sizeof (sem_t));
    sem_t * semlock_3 = (sem_t*) (ptr + sizeof (int) + 3 * sizeof (sem_t));
    
    if (sem_init(semlock_P, 1, 0) == -1) {
        perror("Chef: Failed to initialize semaphore for chef");
        exit(1);
    } else {
        printf("Chef: Semaphore created for chef \n");
    }

    if (sem_init(semlock_1, 1, 0) == -1) {
        perror("Chef: Failed to initialize semaphore for maker 0");
        exit(1);
    } else {
        printf("Chef: Semaphore created for maker 0 \n");
    }


    if (sem_init(semlock_2, 1, 0) == -1) {
        perror("Chef: Failed to initialize semaphore for maker 1");
        exit(1);
    } else {
        printf("Chef: Semaphore created for maker 1\n");
    }


    if (sem_init(semlock_3, 1, 0) == -1) {
        perror("Chef: Failed to initialize semaphore for maker 2");
        exit(1);
    } else {
        printf("Chef: Semaphore created for maker 2\n");
    }


    int pr = -1;
    start = clock();
    for (int i = 0; i < salads; i++) {

        int r = rand() % 3;
        
        if (pr == r )
            r = (r+1) % 3;
        pr = r;

        fp = fopen(sharedFile,"a");


        printf("Chef: loop %d of %d - Wake up salader maker with id = %d \n", i, salads, r);
        
        // produce incredients and place to workbench
        
        switch(r){
            case 0:
                end =clock();
                cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
                fprintf(fp,"[00:00:00:%lf] [%d] [chef] [selecting ingredients ntomata piperia]\n",cpu_used,getpid());
                
                sem_post(semlock_1);
                break;
            case 1:
                end =clock();
                cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
                fprintf(fp,"[00:00:00:%lf] [%d] [chef] [selecting ingredients ntomata kremmidi]\n",cpu_used,getpid());
                sem_post(semlock_2);
                break;
            case 2:
                end =clock();
                cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
                fprintf(fp,"[00:00:00:%lf] [%d] [chef] [selecting ingredients kremmidi piperia]\n",cpu_used,getpid());
                sem_post(semlock_3);
                break;
            default:
                printf("### invalid r \n");
                exit(1);
        }
        
        // wait for salad maker to take the incredient
        end =clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(fp,"[00:00:00:%lf] [%d] [Chef]: Waiting for maker to take the incredient \n",cpu_used,getpid());
        
        sem_wait(semlock_P);
        end =clock();
        cpu_used = (double) (end - start)/CLOCKS_PER_SEC;
        fprintf(fp,"[00:00:00:%lf] [%d] [Chef]: [Man time for resting] \n",cpu_used,getpid());
        printf("chef:sleeping started\n");
        sleep(mantime);        
        printf("Chef: Sleeping finished \n");
        fclose(fp);
    }

    // notify all that process is complete    
    sem_post(semlock_1);
    sem_post(semlock_2);
    sem_post(semlock_3);


    //printf("Chef: Waiting for processes ... \n");
    
    /*for (int i=0;i<3;i++) {
        waitpid(pids[i], NULL, 0);
    }*/
    

    if (sem_destroy(semlock_P) == -1) {
        perror("Chef: Failed to destroy semaphore for chef");
        exit(1);
    }

    if (sem_destroy(semlock_1) == -1) {
        perror("Chef: Failed to destroy semaphore for maker 0");
        exit(1);
    }

    if (sem_destroy(semlock_2) == -1) {
        perror("Chef: Failed to destroy semaphore for maker 1");
        exit(1);
    }

    if (sem_destroy(semlock_3) == -1) {
        perror("Chef: Failed to destroy semaphore for maker 2");
        exit(1);
    }

    if (shmdt(mem) == -1) {
        perror("Chef: Detachment.");
    }

    int err = shmctl(shm_id, IPC_RMID, 0);
    if (err == -1) {
        perror("Chef: Removal.");
    } else {
        printf("Chef: Just Removed Shared Segment. Return code: %d\n", (int) (err));
    }

    return 0;
}