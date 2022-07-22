/*

    Dionysios Mpentour 1115201300115
    
    3 functions to find the prime numbers and they insert the numbers as structures to lists
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <sys/times.h>
#include <time.h>



#include "prime_list.h"
#include "primes.h"

struct Prime_List* prime3(struct Prime_List* ptr, int lb, int ub, int id) {


    //double t1, t2;
    //double cpu_time;
    //struct tms tb1, tb2;
    //double ticspersec;
    int flag_var;
    int i,j;
    clock_t start, end;
    double cpu_time_used;

    //return ptr;
    
    //ticspersec = (double) sysconf(_SC_CLK_TCK);
   // t1 = (double) times(&tb1);
    start=clock();

        for (i = lb ; i <= ub; ++i) {
            flag_var = 0;
            for(j=2; j<=i/2;++j){
                if(i%j==0){
                    flag_var=1;
                    break;
                }
            }
           if(flag_var==0){
                //t2 = (double) times(&tb2);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                
                //printf("$$$$$    clock:%lf\n", cpu_time_used);
                //printf("#### sys/times:%lf\n",t2-t1/ticspersec);
              //  cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));
               
                ptr = Create_Node_With_Time(ptr, i, cpu_time_used,id);
               
               // t1 = (double) times(&tb1);
               
            }
            
        }

    return ptr;
}

int prime_1(int n) {
    int i;
    if (n == 1)
        return (NO);

    for (i = 2; i < n; i++)
        if (n % i == 0)
            return (NO);
    return (YES);
}

struct Prime_List* prime1(struct Prime_List* ptr, int lb, int ub, int id) {
    //printf("THIS IS PRIME1\n");
    if ((lb < 1) || (lb > ub)) {
        printf("usage: prime1 lb ub\n");
        exit(1);
    }

 //   double t1, t2;
   // double cpu_time;
    //struct tms tb1, tb2;
    //double ticspersec;
    clock_t start, end;
    double cpu_time_used;

    //ticspersec = (double) sysconf(_SC_CLK_TCK);
    //t1 = (double) times(&tb1);

    for (int i = lb; i <= ub; i++) {
        start= clock();
        if (prime_1(i) == YES) {
            
            //t2 = (double) times(&tb2);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

           
           // cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));
            printf("#####   run time was  %lf\n",cpu_time_used);


            //printf("%d ",i);
            ptr = Create_Node_With_Time(ptr, i, cpu_time_used,id);

           // t1 = (double) times(&tb1);
        }

    }
    //printf("\n");
    return ptr;
}

int prime_2(int n) {
    int i = 0, limitup = 0;
    limitup = (int) (sqrt((float) n));

    if (n == 1)
        return (NO);
    //printf("limitup is %d for number %d\n",limitup ,n);

    for (i = 2; i <= limitup; i++)
        if (n % i == 0) return (NO);

    return (YES);
}

struct Prime_List* prime2(struct Prime_List* ptr, int lb, int ub, int id) {
    //printf("THIS IS PRIME2\n");
    if ((lb < 1) || (lb > ub)) {
        printf("usage: prime2 lb ub\n");
        exit(1);
    }

    //double t1, t2;
  //  double cpu_time;
    //struct tms tb1, tb2;
    //double ticspersec;
    clock_t start, end;
    double cpu_time_used;

   // ticspersec = (double) sysconf(_SC_CLK_TCK);
   // t1 = (double) times(&tb1);


    for (int i = lb; i <= ub; i++) {
        start = clock();
        if (prime_2(i) == YES) {
            //printf("%d ",i);
           // t2 = (double) times(&tb2);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
           // cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));

            ptr = Create_Node_With_Time(ptr, i, cpu_time_used,id);

          // t1 = (double) times(&tb1);
        }

    }
    //printf("\n");
    return ptr;
}
/*
int main()
{
        int i = (int) sqrt(16);
        printf("%d\n",i);
        return 0;
}*/