#ifndef RECORDIDLIST
#define RECORDIDLIST

// records get inserted in this COMMON list

struct Record_list {
    char* pipeName; //key
    struct Record_list* next;
};

struct Record_list* Create_Record(struct Record_list* list_ptr, char* pipename);

void Destroy_Record_list(struct Record_list*);

void Print_Record_List(struct Record_list*);

void Create_Pipes_From_List(struct Record_list*);

void Destroy_Pipes_From_List(struct Record_list*);

//struct Record_list* FindRecord(struct Record_list* r, char* recordID, int d, int m, int y);

//int CheckRecordID(struct Record_list* r, char* recordID);

#endif