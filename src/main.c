#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<string.h>

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

bool check_if_file_exist(char* file_path) {
    struct stat buffer;
    
    if (stat(file_path, &buffer) == 0) {
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
    fseek(fp, 0, SEEK_SET);
    return size;
}

char* allocate_hash(long size) {
    char* allocatedP = (char*)malloc(size);

    if (allocatedP == NULL) {
        return NULL;
    }

    return allocatedP;
}

char* hash_string(char* string) {
    return string;
}

bool compare_hash(char* hash, char* word) {
    if (strcmp(hash, word) == 0) {
        return true;
    } else {
        return false;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        display_usage();
        exit(1);
    }

    char* hash_location = argv[1];
    char* wordlist_path = argv[2];
    FILE* hash_file;
    FILE* wordlist_file;
    bool isFile = false;

    if (!check_if_file_exist(wordlist_path)) {
        report_log(1, "Could not open wordlist");
        exit(1);
    } else {
        wordlist_file = fopen(wordlist_path, "r");
    }
    
    int hash_size;
    if (check_if_file_exist(hash_location)) {
        hash_file = fopen(hash_location, "r");
        isFile = true;
        
        if (hash_file == NULL) {
            report_log(1, "Error opening file");
            exit(1);
        }

        hash_size = get_filesize(hash_file);
        printf("\x1b[92m[+]\x1b[0m Located Hash file <%ld bytes>\n", hash_size);
    } 
    // If we can not find a file just treat the arguement as the actual hash
    else {
       hash_size = strlen(hash_location);
       printf("\x1b[92m[+]\x1b[0m Hash size <%ld bytes>\n", hash_size);
    }

    // For null term
    hash_size += 1;
    char* hash = allocate_hash(hash_size);

    if (hash != NULL) {
        printf("\x1b[92m[+]\x1b[0m Successfully allocated <%ld bytes>\n", hash_size);
    } else {
        report_log(1, "Failed to allocate space for hash");
    }

    if (isFile) {
        if (fgets(hash, hash_size, hash_file) == NULL) {
            printf("\x1b[91m[-]\x1b[0m Failed to read contents of hash file\n");
            exit(1);
        }
    } else {
        strcpy(hash, hash_location);
        hash[hash_size-1] = '\0';
    }

    printf("hash: %s\n", hash);
    
    printf("\x1b[92m[+]\x1b[0m Wrote hash to allocated memory\n");
    
    report_log(2, "Cracking password...");

    char buffer[100];
    bool cracked = false;

    while (fgets(buffer, sizeof(buffer), wordlist_file) != NULL) {
        if (compare_hash(hash, buffer) == true) {
            printf("\x1b[92m[+]\x1b[0m Cracked hash: %s\n", buffer);
            exit(0);
        }
    }

    report_log(2, "Exhausted wordlist\n");


    free(hash);

}

