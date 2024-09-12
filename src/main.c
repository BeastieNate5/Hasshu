#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/stat.h>

#define MAX_HASH_SIZE = 4096

void display_usage() {
    printf("Usage: hasshu <hash> <wordlist>\n");
}

void report_log(int status, char* message) {
    char* icon;
    if (status == 0) {
        icon = "\x1b[92m[+]\x1b[0m";
    } else if (status == 1) {
        icon = "\x1b[91m[-]\x1b[0m";
    } else if (status == 2) {
        icon = "\x1b[93m[!]\x1b[0m";
    }

    printf("%s %s\n", icon, message);
}

bool check_if_file_exist(char* hash_location) {
    struct stat buffer;
    
    if (stat(hash_location, &buffer) == 0) {
        return true;
    } else {
        return false;
    }

}

long get_filesize(FILE* fp) {

    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) < 0) {
        return -1;
    }

    long size = ftell(fp);

    return size;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        display_usage();
        exit(1);
    }

    char* hash_location = argv[1];
    char* wordlist_location = argv[2];
    
    int hash_size;
    if (check_if_file_exist(hash_location)) {
        FILE* hash_file = fopen(hash_location, "r");
        
        if (hash_file == NULL) {
            report_log(1, "Error opening file");
            exit(1);
        }

        hash_size = get_filesize(hash_file);
    } 
    // If we can not find a file just treat the arguement as the actual hash
    else {
       hash_size = sizeof(hash_location);
    }
    
   printf("\x1b[92m[+]\x1b[0m Located Hash file <%ld bytes>\n", hash_size); 

}

