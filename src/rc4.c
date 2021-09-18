#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rc4.h"

#define rc4_key_size 256 

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
Key-scheduling algorithm (KSA): The key-scheduling algorithm is used to initialize the permutation in the array "S".
"keylength" is defined as the number of bytes in the key and can be in the range 1 ≤ keylength ≤ 256.
*/
unsigned char * KSA(char *secret) {
    
    unsigned char *S = malloc(rc4_key_size);

    int len = strlen(secret);
    int j = 0;

    for(int i = 0; i < rc4_key_size; i++)
        S[i] = i;

    for(int i = 0; i < rc4_key_size; i++) {
        j = (j + S[i] + secret[i % len]) % rc4_key_size;

        swap(&S[i], &S[j]);
    }

    return S;
}

/*
Pseudo-random generation algorithm (PRGA): For as many iterations as are needed, the PRGA modifies the state and outputs a byte of the keystream.
*/
unsigned char * PRGA(unsigned char *S, char *plaintext) {

    int i = 0;
    int j = 0;

    unsigned char *encryptedtext = malloc(sizeof(int) * strlen(plaintext));

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % rc4_key_size;
        j = (j + S[i]) % rc4_key_size;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % rc4_key_size];

        encryptedtext[n] = rnd ^ plaintext[n];

    }

    return encryptedtext;
}

unsigned char * rc4_encrypt(char *secret, char *plaintext) {

    unsigned char *S = malloc(rc4_key_size);
    S = KSA(secret);

    return PRGA(S, plaintext);

}