#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "base64.h"

const char base64_encode_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const int mod_table[] = {0, 2, 1};

char *base64_decode_table = NULL;

void base64_generate_decode_table()
{
    base64_decode_table = malloc(256);
    for (size_t i = 0; i < 64; i++)
        base64_decode_table[(unsigned char)base64_encode_chars[i]] = i;
}

size_t base64_encode_size(size_t inputlen)
{
    size_t encode_size;

    encode_size = inputlen;

    if (inputlen % 3 != 0)
        encode_size += 3 - (inputlen % 3);

    encode_size /= 3;
    encode_size *= 4;
    return encode_size;
}

size_t base64_decode_size(const char *input)
{
    size_t inputlen;
    size_t decode_size;

    if (input == NULL)
        return 0;

    inputlen = strlen(input);
    decode_size = inputlen / 4 * 3;

    if (input[inputlen - 1] == '=')
        decode_size--;
    if (input[inputlen - 2] == '=')
        decode_size--;

    return decode_size;
}

char *base64_encode(const unsigned char *input, size_t inputlen)
{
    size_t encode_size;
    char *output;

    if (input == NULL || inputlen == 0)
        return NULL;

    encode_size = base64_encode_size(inputlen);

    output = malloc(encode_size + 1);

    output[encode_size] = '\0';

    for (size_t i = 0, j = 0; i < inputlen;)
    {
        uint32_t octet_one = i < inputlen ? (unsigned char)input[i++] : 0;
        uint32_t octet_two = i < inputlen ? (unsigned char)input[i++] : 0;
        uint32_t octet_three = i < inputlen ? (unsigned char)input[i++] : 0;

        uint32_t concat = (octet_one << 0x10) + (octet_two << 0x8) + octet_three;

        output[j++] = base64_encode_chars[concat >> 3 * 6 & 0x3F];
        output[j++] = base64_encode_chars[concat >> 2 * 6 & 0x3F];
        output[j++] = base64_encode_chars[concat >> 1 * 6 & 0x3F];
        output[j++] = base64_encode_chars[concat >> 0 * 6 & 0x3F];
    }

    for (size_t i; i < mod_table[inputlen % 3]; i++)
        output[encode_size - 1 - i] = '=';

    return output;
}

unsigned char *base64_decode(const char *input, size_t inputlen)
{
    size_t decode_size;
    unsigned char *output;

    if (input == NULL)
        return NULL;

    decode_size = base64_decode_size(input);

    output = malloc(decode_size);

    if (base64_decode_table == NULL)
        base64_generate_decode_table();

    for (size_t i = 0, j = 0; i < inputlen;)
    {
        uint32_t sextet_one = input[i] == '=' ? 0 & i++ : base64_decode_table[input[i++]];
        uint32_t sextet_two = input[i] == '=' ? 0 & i++ : base64_decode_table[input[i++]];
        uint32_t sextet_three = input[i] == '=' ? 0 & i++ : base64_decode_table[input[i++]];
        uint32_t sextet_four = input[i] == '=' ? 0 & i++ : base64_decode_table[input[i++]];

        uint32_t concat = (sextet_one << 3 * 6) + (sextet_two << 2 * 6) + (sextet_three << 1 * 6) + sextet_four;

        if (j < decode_size)
            output[j++] = (concat >> 2 * 8) & 0xFF;
        if (j < decode_size)
            output[j++] = (concat >> 1 * 8) & 0xFF;
        if (j < decode_size)
            output[j++] = (concat >> 0 * 8) & 0xFF;
    }

    return output;
}