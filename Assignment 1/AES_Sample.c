int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,

unsigned char *iv, unsigned char *ciphertext)

{

EVP_CIPHER_CTX *ctx;

int len;


int ciphertext_len;

/* Create and initialise the context */

if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

/* Initialise the encryption operation. IMPORTANT - ensure you use a key

* and IV size appropriate for your cipher

*/

if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))

handleErrors();

/* Provide the message to be encrypted, and obtain the encrypted output.

* EVP_EncryptUpdate can be called multiple times if necessary

*/

if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))

handleErrors();

ciphertext_len = len;

/* Finalise the encryption. Further ciphertext bytes may be written at

* this stage.

*/

if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();

ciphertext_len += len;

/* Clean up */

EVP_CIPHER_CTX_free(ctx);

return ciphertext_len;

}

