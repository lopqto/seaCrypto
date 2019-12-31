/*
pure c implemention of RC4 encryption algorithm
refrence: https://en.wikipedia.org/wiki/RC4
shout-out to: 
    - https://gist.github.com/rverton/a44fc8ca67ab9ec32089
    - https://gist.github.com/cdleary/188393
Hamidreza Babaee, first day of January 2020 (Happy new year!)
*/

/*
@secret => encryption key
@plaintext => the text you wish to encrypt
#return => unsigned char *encryptedtext = malloc(sizeof(int) * strlen(plaintext));
*/
unsigned char * encrypt(char *secret, char *plaintext);

// TODO: add decyption