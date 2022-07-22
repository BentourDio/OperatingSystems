#ifndef PRIMES
#define PRIMES

#define YES 1
#define NO  0

//#include "prime_list.h"


typedef struct Prime_List* ptr;//forward declaration

struct Prime_List* prime3(struct Prime_List* ptr,int lb,int ub,int id);

int prime_1(int n);

struct Prime_List* prime1(struct Prime_List* ptr,int lb, int ub,int id);	

int prime_2(int n);

struct Prime_List* prime2(struct Prime_List* ptr,int lb, int ub, int id);

#endif
