#include"../include/hash.h"
#include<string.h>


EVP_MD_CTX* ctx_init() {
  OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
  OSSL_PROVIDER *default_provider = OSSL_PROVIDER_load(NULL, "default");

  EVP_MD_CTX *ctx = NULL;
  ctx = EVP_MD_CTX_new();
    
  if (ctx == NULL) {
    return NULL;
  }

  return ctx;
}

EVP_MD* get_hash_algo(int mode) {
  EVP_MD *hash_algo = NULL;
  
  switch (mode) {
      case 1:
        hash_algo = EVP_MD_fetch(NULL, "SHA1", NULL);
        break;
      case 2:
        hash_algo = EVP_MD_fetch(NULL, "SHA224", NULL);
        break;
      case 3:
        hash_algo = EVP_MD_fetch(NULL, "SHA256", NULL);
        break;
      case 4:
        hash_algo = EVP_MD_fetch(NULL, "SHA384", NULL);
        break;
      case 5:
        hash_algo = EVP_MD_fetch(NULL, "SHA512", NULL);
        break;
      case 6:
        hash_algo = EVP_MD_fetch(NULL, "SHA3-224", NULL);
        break;
      case 7:
        hash_algo = EVP_MD_fetch(NULL, "SHA3-256", NULL);
        break;
      case 8:
        hash_algo = EVP_MD_fetch(NULL, "SHA3-384", NULL);
        break;
      case 9:
        hash_algo = EVP_MD_fetch(NULL, "SHA3-512", NULL);
        break;
      case 10:
        hash_algo = EVP_MD_fetch(NULL, "SHA512-224", NULL);
        break;
      case 11:
        hash_algo = EVP_MD_fetch(NULL, "SHA512-256", NULL);
        break;
      case 12:
        hash_algo = EVP_MD_fetch(NULL, "MD4", NULL);
        break;
      case 13:
        hash_algo = EVP_MD_fetch(NULL, "MD5", NULL);
        break;
      case 14:
        hash_algo = EVP_MD_fetch(NULL, "MD5-SHA1", NULL);
        break;
      case 15:
        hash_algo = EVP_MD_fetch(NULL, "MDC2", NULL);
        break;
      case 16:
        hash_algo = EVP_MD_fetch(NULL, "whirlpool", NULL);
        break;
      case 17:
        hash_algo = EVP_MD_fetch(NULL, "SHAKE128", NULL);
        break;
      case 18:
        hash_algo = EVP_MD_fetch(NULL, "SHAKE256", NULL);
        break;
      case 19:
        hash_algo = EVP_MD_fetch(NULL, "SM3", NULL);
        break;
      case 20:
        hash_algo = EVP_MD_fetch(NULL, "BLAKE2S-256", NULL);
        break;
      case 21:
        hash_algo = EVP_MD_fetch(NULL, "BLAKE2B-512", NULL);
        break;
      default:
        return NULL;
  }

  if (!hash_algo) {
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



