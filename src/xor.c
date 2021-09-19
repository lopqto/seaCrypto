#include <stdlib.h>
#include <string.h>

#include "xor.h"

char *xor_encode(char *input, char *key, int inputlen, int keylen)
{
    char *output = (char *)malloc(sizeof(char) * inputlen);

    for (size_t i = 0; i < inputlen; i++)
    {
        output[i] = input[i] ^ key[i % keylen];
    }

    return output;
}

char *xor_decode(char *input, char *key, int inputlen, int keylen)
{
    /* :) */
    return xor_encode(input, key, inputlen, keylen);
}