#ifndef CEASAR_H
#define CEASAR_H

char *ceasar_encode(const char *input, size_t inputlen, unsigned short shift);
char *ceasar_decode(const char *input, size_t inputlen, unsigned short shift);

#endif