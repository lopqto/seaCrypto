#ifndef XOR_H
#define XOR_H

char *xor_encode(char *input, char *key, int inputlen, int keylen);
char *xor_decode(char *input, char *key, int inputlen, int keylen);

#endif