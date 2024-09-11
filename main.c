#include<stdio.h>
#include<stdlib.h>

#define MAX_HASH_SIZE = 4096

void display_usage() {
  printf("Usage: <tool_name> <hash> <mode>\n");
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
      display_usage();
      exit(1);
    }
}
