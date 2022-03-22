
#ifndef FILECOMPRESSION_DECODING_H
#define FILECOMPRESSION_DECODING_H
#include "coding.h"

// get information from file
void GetInfoFromFile(NODE**, FILE*, int *, int *);

// build encoded message in the form of zeros and ones
void BuildStrFromFile(FILE*, char*);


void DecodedString(FILE *fw, NODE *tree, const char *str, int len, unsigned long long lenStr);


void Decoding(FILE*, FILE*);

#endif //FILECOMPRESSION_DECODING_H
