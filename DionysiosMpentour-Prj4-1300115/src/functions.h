//Dionysios Mpentour 1115201300115


#ifndef STRUCTS_H
#define STRUCTS_H

#define BUFFSIZE 1024

struct stat myStat(const char * src, char *type_src);

bool askUserForVerification(const char * entry);

void directory_missing(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links) ;

void file_missing(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links);

void file_file(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links);

void directory_directory(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links);

void directory_file(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links);

void file_directory(const char * src, struct stat mybuf_src, const char * dest, struct stat mybuf_dest, bool verbose, bool deleted, bool links);

void remove_dir(const char* dir, bool verbose, bool deleted, bool links);

void process(const char * src, const char * dest, bool verbose, bool deleted, bool links); 

void synchronize(const char * src, const char * dest, bool verbose, bool deleted, bool links);

void delete_file(const char* dir, bool verbose, bool deleted, bool links);

void process_dlt(const char * src, const char * dest, bool verbose, bool deleted, bool links);

void synchronize_dlt(const char* src, const char* dest,bool verbose, bool deleted, bool links);

void Print_Statistics();

void PrintRate(double cpu_time_used);

void Initialize_Flag(int flag);
#endif