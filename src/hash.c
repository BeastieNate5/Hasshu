//#include<hash.h>
#include"../include/hash.h"
#include<string.h>

EVP_MD_CTX* ctx_init() {
  EVP_MD_CTX *ctx = NULL;
  ctx = EVP_MD_CTX_new();
    
  if (ctx == NULL) {
    return NULL;
  }

  return ctx;
}

EVP_MD* get_hash_algo(char* algo) {
  EVP_MD *hash_algo = NULL;

  hash_algo = EVP_MD_fetch(NULL, algo, NULL);
    
  if (hash_algo == NULL) {
    return NULL;
  }

  return hash_algo;
}

int ctx_set_hash_algo(EVP_MD_CTX* ctx, EVP_MD* hash_algo) {
  if (!EVP_DigestInit_ex2(ctx, hash_algo, NULL)) {
    return 0;
  }
  return 1;
}

int ctx_update_string(EVP_MD_CTX* ctx, char* string) {
  if (!EVP_DigestUpdate(ctx, string, strlen(string))) {
    return 0;
  }

  return 1;
}

char* ctx_return_hash(EVP_MD_CTX* ctx) {
  unsigned int hash_size = EVP_MD_get_size(EVP_MD_CTX_get0_md(ctx));
  unsigned char* output = (unsigned char*)malloc(hash_size);
  char* hash_string;

  if (!output) {
    return NULL;
  }

  if (!EVP_DigestFinal_ex(ctx, output, &hash_size)) {
    return NULL;
  }

  if (!EVP_DigestInit_ex2(ctx, NULL, NULL)) {
    return NULL;
  }
  
  hash_string = (char*)malloc(hash_size * 2 + 1);
  
  for (int i = 0; i < hash_size; i++) {
    sprintf(hash_string + (i * 2), "%02x", output[i]);
  }
  
  free(output);
  // Must be freed
  return hash_string;

}
