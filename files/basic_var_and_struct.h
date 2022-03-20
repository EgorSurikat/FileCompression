#ifndef FILECOMPRESSION_BASIC_VAR_AND_STRUCT_H
#define FILECOMPRESSION_BASIC_VAR_AND_STRUCT_H
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// array for the number of each symbol in the file
extern unsigned freq[256];

// struct or list and tree
typedef struct node {
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    struct node * left, *right, * next;
}NODE;

// union in order to represent the symbol in bit form
typedef union bit2char {
    char symb;
    struct bit {
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
        unsigned char b8 : 1;
    }mbit;
}BIT2CHAR;

// find length of file
int findLenOfFile(FILE *);

// the function of counting the number of symbols
void freqOfOccurrence(FILE *, unsigned*, long int);

// add new elem to list
void AddNewNode(NODE **, unsigned *, int);

// add new node to tree
void Add2Tree(NODE**, NODE*);

// make new node of tree
NODE * MakeNode(NODE*, NODE*);

// make tree from list
NODE* MakeTree(NODE*);

// print tree on display
void PrintTree(NODE*, int);

// building code of symbols and add tree to the file
void BuildCodes(NODE*, char**, char*, int, FILE*);

// building encoded string
void BuildStr(FILE *, char**, char*, int);

// form a string of bits from a string of symbols and write it to a file
void BuildEncodedStr(FILE*, char *);


#endif //FILECOMPRESSION_BASIC_VAR_AND_STRUCT_H