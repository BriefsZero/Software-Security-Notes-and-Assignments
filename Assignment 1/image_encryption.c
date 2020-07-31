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

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,

unsigned char *iv, unsigned char *ciphertext)

{

// implement the encryption function based on the above example
	EVP_CIPHER_CTX *cont;
	int len;
	int cipher_len;
	if (!(cont = EVP_CIPHER_CTX_new())) 
	{
        printf("1\n");
		handleErrors();
	}

	if(1 != EVP_EncryptInit_ex(cont, EVP_aes_256_cbc(), NULL, key, iv))
	{
        printf("2\n");
		handleErrors();
	}

	if(1 != EVP_EncryptUpdate(cont, ciphertext, &len, plaintext, plaintext_len))
	{
        printf("3\n");
		handleErrors();
	}
	cipher_len = len;

	if(1 != EVP_EncryptFinal_ex(cont, ciphertext+len, &len)) 
	{
        printf("4\n");
		handleErrors();
	}
	cipher_len += len;

	EVP_CIPHER_CTX_free(cont);
	return cipher_len;

}

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}


int main(int argc, char **argv)

{

char * fileName="pic_original.bmp";

//======================= STEP 0=====================================//

/* Key initialization.

It will be automaticalled padded to 128 bit key */
unsigned char *key = "297433387890123456789012345678901";

//======================= STEP 1=====================================//

/* IV initialization.

The IV size for *most* modes is the same as the block size.

* For AES128 this is 128 bits

*/

unsigned char *iv = "0123456789012345";


//======================= STEP 2=====================================//

//read the file from given filename in binary mode

printf("%s", "Start to read the .bmp file \n");
FILE * fptr = fopen(fileName, "rb");
if (fptr == NULL) {
    perror("Couldn't open file");
    } 


fseek(fptr, 0, SEEK_END);
int fsize = ftell(fptr);
fseek(fptr, 0, SEEK_SET);
unsigned char *img = malloc(fsize+1);
    
int c;



do 
{
    c=fgetc(fptr);
    if(feof(fptr)) {
        break;
    }
    for(int i=0;i<=7;i++)
    {
        if(c&(1<<(7-i)))
        {
            strcat('1', img);
        }
        else
        {
            strcat('0', img);
        }
    }
    
} while(1);
fclose(fptr);
printf("Finieshed reading \n");




//======================= STEP 3=====================================//

/*allocate memory for bitmapHeader and bitmapImage.
then read bytes for these variables */
int size = sizeof(img);

unsigned char bitmapHeader[54];
unsigned char bitmapImage[size-54];
int sizes = sizeof(bitmapImage);
//allocate memory for the final ciphertext


/* as this is a .bmp file we read the header,
the first 54 bytes, into bitmapHeader*/
for(int i=0;i<54;i++) 
{
	bitmapHeader[i] = img[i];
}
printf("Finieshed reading \n");
//read the bitmap image content until the end of the .bmp file
int x = 54;
for(int i=0;i<size;i++) {
	bitmapImage[i] = img[i+x];
}

//======================= STEP 4=====================================//

// encrypt the bitmapImage with the given studentId key

unsigned char ciphertext[128];
unsigned char final_cipher[sizes];
unsigned char subset[128];
for(int i=0;i<size+1;i++)
{
    if (i != 0 && i % 128 == 0) {
        printf("encrypt \n");
        encrypt(subset, 128, key, iv, ciphertext);
        strcat(final_cipher, ciphertext);
    }
    else {
        subset[i%128] = bitmapImage[i];
    }
}
printf("Finished \n");


//======================= STEP 5=====================================//

/*merge header and bitmap to the final ciphertext
and output it into a .bmp file*/

unsigned char buf[8];


int j = 0;
for(int i=0;i<54;i++) 
{
	final_cipher[i] = bitmapHeader[i];
}

for(int i=54; i<184974; i++) 
{
	final_cipher[i] = bitmapImage[i-54];
}

char bytefrom(unsigned char*txt)
{
    char res = 0;
    for(int i=0;i<8;i++)
    {
        if(txt[i]=='1')
        {
            res |= (1 <<(7-i));

        }
    }
    return res;
}


FILE * ptr_bmp_out=fopen("ecnrypted.bmp","wb");
int sizeofciph = sizeof(final_cipher);

for(int i=0;i<sizeofciph;i++) 
{
    buf[j++] = final_cipher[i];

    if(j==8)
        {
            fputc(bytefrom(buf),ptr_bmp_out);
            j=0;
        }
}
fclose(ptr_bmp_out);
return 1;

}
