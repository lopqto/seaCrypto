#ifndef BASE64_H
#define BASE64_H

char *base64_encode(const unsigned char *input, size_t inputlen);
unsigned char *base64_decode(const char *input, size_t inputlen);

#endif