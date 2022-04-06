
#ifndef FILECOMPRESSION_DECODING_H
#define FILECOMPRESSION_DECODING_H
#include "coding.h"

// get information from file (metadata)
void GetInfoFromFile(NODE**, FILE*, int *, int *);

// build encoded message in the form of zeros and ones
void BuildStrFromFile(FILE*, char*);

// decoding file from string in the form of zeros and ones
void DecodedString(FILE *fw, NODE *tree, const char *str, int len, unsigned long long lenStr);

// main decoding function
void Decoding(FILE*, FILE*);

#endif //FILECOMPRESSION_DECODING_H
