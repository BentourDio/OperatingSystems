#ifndef LIST
#define LIST

struct Prime_List {
    int number; //key
    struct Prime_List* next;
    double t;
    int id;
};

struct Prime_List* Create_Node(struct Prime_List* list_ptr, int number);

struct Prime_List* Create_Node_With_Time(struct Prime_List* list_ptr, int number, double t,int id);

struct Prime_List* Insert_Orderly(struct Prime_List* list_ptr, int number, double t, int id);

void Destroy_Prime_List(struct Prime_List*);

void Print_Prime_List(struct Prime_List*);

void Print_Prime_List_Ln(struct Prime_List*,int lb, int ub);

void Print_Root(struct Prime_List* list_ptr);

void Print_Root_Range(struct Prime_List*,int w);

#endif

/*
OUTPUT (per invocation of program):

Primes in [lb,ub] are: result1 time1 result2 time2 result3 time3 result4 time4 ... resulti  timei...
Min Time for Workers : mintime msecs
Max Time for Workers : maxtime msecs
Num of USR1 Received : numUSR1rec-by-root/number-of-workers-activated
Time for W0: W0-time msecs
Time for W1: W1-time msecs
Time for W2: W2-time msecs
Time for W3: W3-time msecs
....
*/