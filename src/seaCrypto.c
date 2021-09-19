#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "rc4.h"
#include "xor.h"
#include "ceasar.h"

int main()
{

    char *input = "Very important message";
    char *key = "seaCrypto";
    unsigned short shift = 13;
    size_t inputlen = strlen(input);
    size_t keylen = strlen(key);

    printf("Input text: %s \n", input);
    printf("Key value: %s \n", key);
    printf("Shift value: %d \n", shift);

    printf("#############\n");

    char *base64_encoded = base64_encode(input, inputlen);
    printf("base64 encode: %s \n", base64_encoded);

    size_t base64_decode_size = strlen(base64_encoded);
    char *decoded_data = base64_decode(base64_encoded, base64_decode_size);
    printf("base64 decode: %s \n", decoded_data);
    printf("#############\n");
    unsigned char *ciphertext = malloc(sizeof(int) * strlen(input));
    ciphertext = rc4_encrypt(key, input);
    printf("rc4 encrypt (hex): ");
    for (size_t i = 0; i < inputlen; i++)
        printf("%02hhX", ciphertext[i]);

    printf("\n");
    printf("#############\n");

    char *xor_encoded = xor_encode(input, key, inputlen, keylen);
    printf("xor encode (hex): ");
    for (size_t i = 0; i < inputlen; i++)
        printf("%02hhX", xor_encoded[i]);
    printf("\n");
    char *xor_decoded = xor_decode(xor_encoded, key, inputlen, keylen);
    printf("xor decode: %s \n", xor_decoded);

    printf("#############\n");

    char *ceasar_encoded = ceasar_encode(input, inputlen, 13);
    printf("ceasar encode: %s \n", ceasar_encoded);
    /* in ceasar encoding input length is equal to output length */
    char *ceasar_decoded = ceasar_decode(ceasar_encoded, inputlen, 13);
    printf("ceasar decode: %s \n", ceasar_decoded);

    return EXIT_SUCCESS;
}