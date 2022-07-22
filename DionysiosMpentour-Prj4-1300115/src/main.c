//Dionysios Mpentour 1115201300115

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#include "functions.h"

// -v -d -l origin destination

int main(int argc, char** argv) {
    const char * origin;
    const char * destination;
    bool verbose, deleted, links;
    int flag = 0;

    clock_t start, end;
    double cpu_time_used;

    if (argc != 8) {
        printf("[Error] Wrong arguments Given\n[Undefined behaviour may occur]\n");
        //return -1;
    }

    for (int i = 0; i < argc - 2; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
        }
        if (strcmp(argv[i], "-d") == 0) {
            deleted = true;
        }
        if (strcmp(argv[i], "-l") == 0) {
            links = true;
        }
        if (strcmp(argv[i], "-f") == 0) {
            flag = atoi(argv[i+1]);
        }
    }
    Initialize_Flag(flag);//simple function to set a global flag, as to determine whether to check modification timestamps
    
    origin = argv[argc - 2];

    destination = argv[argc - 1];

    printf("Origin        : %s \n", origin);
    printf("Destination   : %s \n", destination);
    printf("Deleted       : %s \n", verbose ? "true" : "false");
    printf("Verbose       : %s \n", deleted ? "true" : "false");
    printf("Links         : %s \n", links ? "true" : "false");

    start = clock();

    synchronize(origin, destination, verbose, deleted, links);
    
    if(deleted){
    synchronize_dlt(origin, destination, verbose, deleted, links);
    }
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(verbose){
    
    Print_Statistics();
    
    }
    
    printf("Time passed for conclusion of quic :%f\n", cpu_time_used);
    
    PrintRate(cpu_time_used);
    
    return 0;
}

