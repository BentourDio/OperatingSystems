#ifndef INDEX
#define INDEX

typedef struct Hash_entry* htable_ptr;//forward declaration

struct Index {
    int entry_year;
    float sum_gpa;
    int num_students; //for count function
    
    struct Index* next;
    
    struct Student_Catalog* catalog_first_ptr;
    struct Student_Catalog* catalog_last_ptr;
};

struct Student_Catalog {  
    struct Student_Catalog* previous;         
    struct Student_Catalog* next;            
    struct Hash_entry* htable_ptr;
};

void Insert_Catalog(struct Index *p, struct Hash_entry* htable_ptr);

struct Student_Catalog* Search_Student(struct Index* p, char* studentID);

void Print_Index_Catalog(struct Index* p);
/////////////////////////////////////////////////////////////////////////
struct Index* Search_Indexes(struct Index* index_ptr, int entry_year);

struct Index* InsertIndex(struct Index* p, int entry_year);

void Destroy_Index(struct Index* p);

void DestroyStudentCatalog(struct Student_Catalog* p);

struct Index* Index_Delete_Student(struct Index* p,int entry_year,char* studentID, float gpa);
#endif
