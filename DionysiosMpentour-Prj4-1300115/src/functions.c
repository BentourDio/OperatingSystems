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

int entities_read = 0;
int entities_deleted = 0;
int bytes_written = 0;
int entities_copied = 0;
int flag_date = 0;
//int time_passed = 0;

void Initialize_Flag(int flag){
    flag_date = flag;
}

struct stat myStat(const char * src, char *type_src) {
    struct stat mybuf_src = {0};

    if (stat(src, &mybuf_src) == -1) {
        *type_src = ' ';
        return mybuf_src;
    }

    switch (mybuf_src.st_mode & S_IFMT) {
        case S_IFREG:
            *type_src = 'f';
            break;
        case S_IFDIR:
            *type_src = 'd';
            break;
        default:
            *type_src = '?';
            printf("Supported type are only: directories and files \n");
            exit(1);
    }
    return mybuf_src;
}


bool askUserForVerification(const char * entry) {
    return true;
    
    char buf[10];
    printf("Do you want to delete: %s ? \n", entry);
    fgets(buf, sizeof(buf), stdin);
    
    if (buf[0] == 'y') {
        return true;
    } else {
        return false;
    }
}


void directory_missing(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) {
    // create directory on destination
    if(verbose){
        printf("Directory %s is created\n",dest);
    }
    mkdir(dest, 0755);
}

void file_missing(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) { // p17
    //creating a missing file on destination directory
    int n, from, to;
    char buf[BUFFSIZE];

    mode_t fdmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if ((from = open(src, O_RDONLY)) < 0) {
        perror("open");
        exit(1);
    }

    if ((to = open(dest, O_WRONLY | O_CREAT, fdmode)) < 0) {
        perror("open");
        exit(1);
    }

    while ((n = read(from, buf, sizeof (buf))) > 0) {
        write(to, buf, n);
    }
    //printf("before change mtime:%.12s %s\n",ctime(&mybuf_dest.st_mtime) + 4,dest);
    mybuf_dest.st_mtime = mybuf_src.st_mtime;
    //printf("after  change mtime:%.12s %s\n",ctime(&mybuf_dest.st_mtime) + 4,dest);

   /* if(mybuf_dest.st_mtime == mybuf_src.st_mtime){
        printf("EIMAI ILI8IOS\n");
    }*/
    bytes_written = bytes_written + mybuf_src.st_size;
    entities_copied++;
    
    if(verbose){
        printf("File %s %7ld mb is created\n",dest,mybuf_dest.st_size);
    }
    close(from);
    close(to);
}

void file_file(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) {
   //overwriting the file in destination directory if size or date is different
    if (mybuf_src.st_size != mybuf_dest.st_size) {
        if(verbose){
            printf("file %s %7ld mb is deleted", dest, mybuf_dest.st_size);
        }
        unlink(dest);
        entities_deleted++;
        file_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
        //bytes_written = bytes_written + mybuf_src.st_size;
    }
    else if (flag_date == 1 && (mybuf_src.st_mtime != mybuf_dest.st_mtime)) {
        
        //printf("%s :%.12s\t %s:",ctime(&mybuf_src.st_ctime) + 4)
        if(verbose){
            printf("file %s %.12s is deleted\n", dest, ctime(&mybuf_src.st_ctime) + 4);
        }
        unlink(dest);
        entities_deleted++;
        file_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
        //bytes_written = bytes_written + mybuf_src.st_size;
    }
    else {
        //printf("[no new file to overwrite]\n");
        return;
    }
}

void directory_directory(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) {
    
    return;
}

void directory_file(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) {
    // remove file, create directory
    printf("Directory %s conflicts with file: %s (y/n)", src, dest);
    if (askUserForVerification(dest)) {
        unlink(dest);
        entities_deleted++;
        entities_copied++;
        directory_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }
}

void file_directory(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) {
    // remove directory, copy file
    remove_dir(dest,verbose, deleted, links);
    rmdir(dest);
    file_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
}

void remove_dir(const char* dir,bool verbose, bool deleted, bool links){
    DIR *dp;
    struct dirent* p;
    size_t path_len = strlen(dir);

    if ((dp = opendir(dir)) == NULL) {
        perror("opendir");
        return;
    }

    if(askUserForVerification(dir)){
        while ((p = readdir(dp)) != NULL){
            if (p->d_ino == 0 || strcmp(p->d_name, ".") == 0 || strcmp(p->d_name, "..") == 0) 
                continue;
            char* buff;
            size_t len;

            len = path_len + strlen(p->d_name) + 2;
            buff = malloc(len);

            if(buff){
                struct stat statbuff;

                snprintf(buff, len, "%s/%s", dir, p->d_name);
                if(!stat(buff,&statbuff)){
                    if(S_ISDIR(statbuff.st_mode)){
                        remove_dir(buff,verbose, deleted, links);
                        if(verbose){
                            printf("Directory %s is being deleted\n",dir);
                        }
                        entities_deleted++;
                        //rmdir(dir);
                    }
                    else{
                        if(verbose){
                            printf("File %s is being deleted\n",buff);
                        }
                        unlink(buff);
                        entities_deleted++;
                    }
                }
                free(buff);
            }
            
        }
    }
    closedir(dp);
}

void process(const char * src, const char * dest, bool verbose, bool deleted, bool links) {
    /*
        Comparisons between files take place, in order to determine in which
        conflicts occur
    */

    char type_src;
    char type_dest;

    struct stat mybuf_src = myStat(src, &type_src);//i pass the 2nd argument and change the value in myStat
    struct stat mybuf_dest = myStat(dest, &type_dest);

    if (type_src != 'f' && type_src != 'd') {
        return;
    }

    /*
    if (verbose) {
        printf("%c %7d %.12s %-60s => %s \n", type_src, (int) mybuf_src.st_size, ctime(&mybuf_src.st_mtime) + 4, src, dest);
    }
    */

    if (type_src == 'f' && type_dest == 'f') {
        file_file(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

    if (type_src == 'f' && type_dest == 'd') {
        file_directory(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

    if (type_src == 'd' && type_dest == 'f') {
        directory_file(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

    if (type_src == 'd' && type_dest == 'd') {
        directory_directory(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

    if (type_src == 'f' && type_dest == ' ') {
        file_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

    if (type_src == 'd' && type_dest == ' ') {
        directory_missing(src, mybuf_src, dest, mybuf_dest,verbose, deleted, links);
    }

}

void synchronize(const char * src, const char * dest, bool verbose, bool deleted, bool links) {
    /*
        this function synchronizes the two files, meaning it copies and deleties files
        if either of those action is needed
    */

    DIR *dp;
    struct dirent *entry;

    if ((dp = opendir(src)) == NULL) {
        perror("opendir");
        return;
    }

    process(src, dest, verbose, deleted, links);/*this is for the case the destination directory is not created*/

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_ino == 0 || strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        entities_read++;

        char *src_childname = (char *) malloc(strlen(src) + strlen(entry->d_name) + 2);
        strcpy(src_childname, src);
        strcat(src_childname, "/");
        strcat(src_childname, entry->d_name);

        char *dest_childname = (char *) malloc(strlen(dest) + strlen(entry->d_name) + 2);
        strcpy(dest_childname, dest);
        strcat(dest_childname, "/");
        strcat(dest_childname, entry->d_name);

        if (entry->d_type == DT_DIR) {//check if the entry is a file or dir
            synchronize(src_childname, dest_childname, verbose, deleted, links);//synchronze if needed
        } else {
            process(src_childname, dest_childname, verbose, deleted, links);//create the directory
        }

        free(src_childname);//freeing the two mallocs

        free(dest_childname);

        src_childname = NULL;
    }
    closedir(dp);
}

void synchronize_dlt(const char* src, const char* dest,bool verbose, bool deleted, bool links){
    /*
    In this function i check the destination directory if it has any extra files/directories, that 
    do not exist anymore in the source directory, and if found i delete them
    */
    DIR* dp;
    struct dirent* entry;

    if ( (dp = opendir(dest)) == NULL){
        perror("opendir");
        return;
    }
    
    while ((entry = readdir(dp))!=NULL){
        if (entry->d_ino == 0 || strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
            continue;
        char *src_childname = (char *) malloc(strlen(src) + strlen(entry->d_name) + 2);
        strcpy(src_childname, src);
        strcat(src_childname, "/");
        strcat(src_childname, entry->d_name);

        char *dest_childname = (char *) malloc(strlen(dest) + strlen(entry->d_name) + 2);
        strcpy(dest_childname, dest);
        strcat(dest_childname, "/");
        strcat(dest_childname, entry->d_name);

        if (entry->d_type == DT_DIR) {//check if the entry is a file or dir
            process_dlt(src_childname, dest_childname, verbose, deleted, links);
            synchronize_dlt(src_childname, dest_childname, verbose, deleted, links);
        }
        else {
            process_dlt(src_childname, dest_childname, verbose, deleted, links);
        }
        free(src_childname);//freeing the two mallocs

        free(dest_childname);

        src_childname = NULL;
    }
    closedir(dp);
}

void process_dlt(const char * src, const char * dest, bool verbose, bool deleted, bool links){
    char type_src;
    char type_dest;
    //printf("\n\n\n this is process dlt\n");
    struct stat mybuf_src = myStat(src, &type_src);//i pass the 2nd argument and change the value in myStat
    struct stat mybuf_dest = myStat(dest, &type_dest);
    //printf("\\t\t\t source type is [%c] & dest type is [%c]\n",type_src,type_dest);
    if (type_src == ' ' && type_dest == 'f') {
        delete_file(dest,verbose, deleted, links);
    }
    
    if (type_dest == 'd' && type_src == ' ') {
        //printf("geia");
        remove_dir(dest,verbose, deleted, links);
        rmdir(dest);
    }
}

void delete_file(const char* dest, bool verbose, bool deleted, bool links){
    if(askUserForVerification(dest)){
        unlink(dest);
        entities_deleted++;
    }
}

void Print_Statistics(){
    printf("Entities read    :%d \n",entities_read);
    printf("Entitied removed :%d\n", entities_deleted);
    printf("Entities copied  :%d\n",entities_copied);
    printf("Bytes written    :%f mb\n",(double)bytes_written* 0.000001);

}

void PrintRate(double cpu_time_used){
    printf("Rate of copying is %f mb/sec\n",(double)bytes_written* 0.000001/cpu_time_used);
}