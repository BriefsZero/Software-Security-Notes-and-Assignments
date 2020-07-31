#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handleErrors()
{
   printf("Wrong encryption progress\n");
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    
    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();
    
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
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    
    ciphertext_len += len;
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    
    return ciphertext_len;
    
}
int main(int argc, char **argv)
{

    char * fileName="pic_original.bmp";

    //======================= STEP 0=====================================//
    /*Key initialization.
     It will be automaticalledly padded to 128 bit key
     */
 
    //======================= STEP 1=====================================//
    /*IV initialization.
     The IV size for *most* modes is the same as the block size.
     For AES128 this is 128 bits
     */
    
    //======================= STEP 2=====================================//
    /*read the file from given filename in binary mode*/
    printf("Start to read the .bmp file \n");
    
    //======================= STEP 3=====================================//
    /*allocate memory for bitmapHeader and bitmapImage,
     then read bytes for these variables.*/
    
    //allocate memory for the final ciphertext

    /*as this is a .bmpfile, we need to read the header
     (the first 54 bytes) into bitmapHeader*/
    
    //read the bitmap image content until the end of the .bmp file
    
    //======================= STEP 4=====================================//
    //encrypt the bitmapImage with the given studentID key
    
    //======================= STEP 5=====================================//
    /*merge header and bitmap to the final ciphertext
     and output it into a .bmp file*/
    
    return 1;
}
