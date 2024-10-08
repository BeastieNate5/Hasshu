#ifndef HASH
#include<openssl/evp.h>
#include<openssl/bio.h>
#include<openssl/err.h>
#include <openssl/provider.h>

EVP_MD_CTX* ctx_init();
EVP_MD* get_hash_algo(int mode);
int ctx_set_hash_algo(EVP_MD_CTX *ctx, EVP_MD* hash_algo);
int ctx_update_string(EVP_MD_CTX *ctx, char* string);
char* ctx_return_hash(EVP_MD_CTX *ctx);
char* hash_string(char* string);

#endif
