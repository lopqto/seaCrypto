#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "ceasar.h"

char *ceasar_encode(const char *input, size_t inputlen, unsigned short shift)
{
    char *output = malloc(inputlen);
    for (size_t i = 0; i < inputlen; i++)
    {
        if (isupper(input[i]))
            output[i] = (input[i] - 'A' + shift) % 26 + 'A';

        else if (islower(input[i]))
            output[i] = (input[i] - 'a' + shift) % 26 + 'a';
        else
            output[i] = input[i];
    }

    return output;
}

char *ceasar_decode(const char *input, size_t inputlen, unsigned short shift)
{
    return ceasar_encode(input, inputlen, shift);
}
