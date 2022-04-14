#ifndef FILECOMPRESSION_DECODING_H
#define FILECOMPRESSION_DECODING_H
#include "coding.h"

// get information from file (metadata)
void GetInfoFromFile(NODE**, FILE*, int *, int *);

// build encoded message in the form of zeros and ones
void BuildStrFromFile(FILE*, FILE*, NODE*, int*);

// decoding file from string in the form of zeros and ones
const char * DecodedString(FILE *, NODE *, const char *, int*, int, int, int*, int);

// main decoding function
void Decoding(FILE*, FILE*);

void ProgressBar(int, int);

#endif //FILECOMPRESSION_DECODING_H
