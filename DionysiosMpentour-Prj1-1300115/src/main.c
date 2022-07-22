#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    "app.h"

int main(int argc, char *argv[]) {
    FILE* fp;


    if( argc != 5 ){
        printf("[Error] Wrong arguments Given\nExiting\n");
        return -1;
    }
    if(argv[1]!=NULL && strcmp(argv[1],"-i")==0)
        fp = fopen(argv[2],"r");

    if((argv[3]!=NULL && strcmp(argv[3],"-i")==0))
        fp = fopen(argv[4],"r");

    if(argv[3]!=NULL && strcmp(argv[3],"-c"))
        printf("I dont use the config file\n");

    if(argv[1]!=NULL && strcmp(argv[1],"-c"))
        printf("I dont use the config file\n");

    set_tableSize(fp);//i set the hashtable size the same size as the input file lines

    Create_Htable();

    fseek(fp, 0, SEEK_SET);

    
    Load_File(fp);
    
    fclose(fp);

    Command_Prompt();

    printf("EXITING MAIN\n");

    return 0;
}