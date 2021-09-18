#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "rc4.h"

int main(){
    
    char *input = "Very important message";
    char *key = "seaCrypto";

    printf("Input text: %s \n", input);
    printf("Key value: %s \n", key);
    
    size_t inputlen = strlen(input);
    char *base64_encoded = base64_encode(input, inputlen);
    printf("base64 encode: %s \n", base64_encoded);
    
    size_t base64_decode_size = strlen(base64_encoded);
    char * decoded_data = base64_decode(base64_encoded, base64_decode_size);
    printf("base64 decode: %s \n",decoded_data);
    
    unsigned char *ciphertext = malloc(sizeof(int) * strlen(input));
    ciphertext = rc4_encrypt(key, input);
    printf("rc4 encrypt (hex): ");
    for(size_t i = 0, len = strlen(input); i < len; i++)
        printf("%02hhX", ciphertext[i]);

    return EXIT_SUCCESS;
}