#ifndef APP
#define APP


void set_tableSize(FILE* fp);

void Create_Htable();

void Load_File(FILE * fp); 

void Print_Index();

void APP_Print_Htable();

void Command_Prompt();

void Look_Up(char* studentID);

void Exit();//done

void Post_Rank(int num);//done

void Count();//done

void Minimum_Year(int year);//done

void Average_Year(int year);//done

void Top_Num_Year(int year,int num);//done

void Number_Year(int year);//done

void Delete_Student(char* studentID);//done

void Insert_Student(char* studentID,char* name,char* surname,int postal_code,int entry_year,float gpa);
//done
#endif
