#ifndef POSTCODE_INDEX
#define POSTCODE_INDEX

struct PostCodeIndex {
    int postcode;
    int counter;
    
    struct PostCodeIndex* next;
    struct PostCodeIndex* previous;

    int rank;

//    struct PostCodeIndex* post_last_ptr;
};

struct PostCodeIndex * Insert_PostCode(struct PostCodeIndex *p, int postcode);

struct PostCodeIndex* Search_PostCode(struct PostCodeIndex* p, int postcode);

void DestoyPostIndex(struct PostCodeIndex* p);

struct PostCodeIndex* PostCode_Delete_Student(struct PostCodeIndex* p,int post_code);

struct PostCodeIndex* MovePostNode(struct PostCodeIndex* p,struct PostCodeIndex* root);

void PrintRank(struct PostCodeIndex* p,int num);

//void Print_Index_PostCode(struct Index* p);
/////////////////////////////////////////////////////////////////////////
//struct Index* Search_Indexes(struct Index* index_ptr, int entry_year);

//struct Index* InsertIndex(struct Index* p, int entry_year);
#endif