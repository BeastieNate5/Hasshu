#include<stdio.h>
#include<string.h>
#include<hash.h>
#include<stdlib.h>

char* md5(char* string) {
    unsigned char* output;
    unsigned int len = 0;

    EVP_MD_CTX *ctx = NULL;
    ctx = EVP_MD_CTX_new();
    EVP_MD *sha256 = NULL;

    if (ctx == NULL) {
        return NULL;
    }

    sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);

    if (sha256 == NULL) {
        return NULL;
    }

    if (!EVP_DigestInit_ex(ctx, sha256, NULL)) {
        return NULL;
    }

    if (!EVP_DigestUpdate(ctx, string, strlen(string))) {
        return NULL;
    }

    output = OPENSSL_malloc(EVP_MD_get_size(sha256));

    if (output == NULL) {
        return NULL;
    }

    if (!EVP_DigestFinal_ex(ctx, output, &len)) {
        return NULL;
    }
    
    // Needs to be freed by caller
    char* hashed_string = malloc(EVP_MD_get_size(sha256) * 2 + 1);

    for (int i = 0; i < EVP_MD_get_size(sha256); i++) {
        sprintf(hashed_string + (i * 2), "%02x", output[i]);
    }



    return hashed_string;

}


