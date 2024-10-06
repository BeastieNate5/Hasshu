#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<string.h>
//#include<hash.h>
#include"../include/hash.h"

#define MAX_HASH_SIZE 200
#define MAX_WORD_SIZE 200

void display_usage() {
    printf("Usage: hasshu <hash> -m <mode> -w <wordlist>\n");
}

void display_table() {
    printf("TABLE\n");
}

void display_help() {
    printf("This is the help menu\n");
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

void remove_newline(char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if (*(string+i) == '\n') {
            *(string+i) = '\0';
        }
    }
}

bool compare_hash(char* hash, char* word) {
    if (strcmp(hash, word) == 0) {
        return true;
    } else {
        return false;
    }
};

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        display_usage();
        exit(1);
    }
    
    char* wordlist_path = NULL;
    int mode = -1;
    
    int opt = 1;
    while ((opt = getopt(argc, argv, "htm:w:") ) != -1) {
        switch (opt) {
            case 'h':
                display_usage();
                exit(0);
            case 't':
                display_table();
                exit(0);
            case 'w':
                wordlist_path = optarg;
                break;
            case 'm':
                mode = atoi(optarg);
                if (!mode) {
                  display_usage();
                  exit(1);
                }
                break;
            default:
                display_usage();
                exit(1);
        }
    }
    
    char* hash_location = argv[argc-1];
    
    if (wordlist_path == NULL || mode == -1 || argc < 6) {
      display_usage();
      exit(1);
    }
    
    
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
        printf("\x1b[92m[+]\x1b[0m Located Hash file (%d bytes)\n", hash_size);
    } 
    // If we can not find a file just treat the arguement as the actual hash
    else {
       hash_size = strlen(hash_location);
       printf("\x1b[92m[+]\x1b[0m Hash size (%d bytes)\n", hash_size);
    }


    if (hash_size > MAX_HASH_SIZE) {
      printf("\x1b[91m[-]\x1b[0m Hash exceeded max hash size (hash > %d)\n", MAX_HASH_SIZE);
      exit(1);
    }

    // For null term
    hash_size += 1;
    char* hash = allocate_hash(hash_size);

    if (hash != NULL) {
        printf("\x1b[92m[+]\x1b[0m Successfully allocated (%d bytes)\n", hash_size);
    } else {
        report_log(1, "Failed to allocate space for hash");
    }

    if (isFile) {
        if (fgets(hash, hash_size, hash_file) == NULL) {
            printf("\x1b[91m[-]\x1b[0m Failed to read contents of hash file\n");
            exit(1);
        }
        remove_newline(hash);
    } else {
        strcpy(hash, hash_location);
        hash[hash_size-1] = '\0';
    }

    
    printf("\x1b[92m[+]\x1b[0m Wrote hash to allocated memory\n");
    
    report_log(2, "Setting up hashing algo");
    EVP_MD_CTX* ctx = ctx_init();
    EVP_MD* hash_algo = get_hash_algo("SHA-256");

    if (!ctx || !hash_algo || !ctx_set_hash_algo(ctx, hash_algo)) {
        report_log(1, "Failed to init hashing algo");
        exit(1); 
    }

    report_log(2, "Cracking password...");

    char buffer[MAX_WORD_SIZE];
    char* hash_buffer;
    bool cracked = false;

    while (fgets(buffer, sizeof(buffer), wordlist_file) != NULL) {
        remove_newline(buffer);
        
        if (!ctx_update_string(ctx, buffer)) {
            printf("\x1b[91m[-]\x1b[0m Failed to setup string for hash {%s}\n", buffer);
            continue;
        }

        hash_buffer = ctx_return_hash(ctx);

        if (!hash_buffer) {
            printf("\x1b[91m[-]\x1b[0m Failed to hash {%s}\n", buffer);
            continue;
        }

        if (compare_hash(hash, hash_buffer) == true) {
            printf("\x1b[92m[+]\x1b[0m Cracked hash: \x1b[1m%s\x1b[0m\n", buffer);
            cracked = true;
        }
    }
    
    if (!cracked) { 
      report_log(2, "Exhausted wordlist\n");
    }

    EVP_MD_CTX_free(ctx);
    EVP_MD_free(hash_algo);
    free(hash);

}

