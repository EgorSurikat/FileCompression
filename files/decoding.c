//
// Created by ed230 on 21.03.2022.
//

#include "decoding.h"

// get information from file (metadata)
void GetInfoFromFile(NODE ** new, FILE * fw, int *LenOfFile, int *countSymb){
    fscanf(fw, "%d %d ", LenOfFile, countSymb);
    unsigned newFreq[256] = {0};
    for (int n = 0; n < *countSymb; ++n) {
        int symbol;
        // get tree from the file
        fscanf(fw, "%d ", &symbol);
        fscanf(fw, "%d ", newFreq + symbol);
        AddNewNode(&(*new), newFreq, symbol);
    }
}

// build encoded message in the form of zeros and ones
void BuildStrFromFile(FILE * fr, char * string){
    BIT2CHAR symb;
    int i = 0;
    while (1) {
        int symbol = fgetc(fr);
        if (symbol == EOF)
            break;
        symb.symb = (char) symbol;

        string[i] = symb.mbit.b1 ? '1' : '0';
        string[i + 1] = symb.mbit.b2 ? '1' : '0';
        string[i + 2] = symb.mbit.b3 ? '1' : '0';
        string[i + 3] = symb.mbit.b4 ? '1' : '0';
        string[i + 4] = symb.mbit.b5 ? '1' : '0';
        string[i + 5] = symb.mbit.b6 ? '1' : '0';
        string[i + 6] = symb.mbit.b7 ? '1' : '0';
        string[i + 7] = symb.mbit.b8 ? '1' : '0';
        i += 8;
    }
    string[i] = '\0';
}

// decoding file from string in the form of zeros and ones
void DecodedString(FILE *fw, NODE *tree, const char *str, int len, unsigned long long lenStr) {
    for (int pos = 0, count = 0; count < len; ++count) {
        int len = 0;
        NODE * tempTree = tree;
        while (tempTree->left || tempTree->right) {
            if (str[pos + len++] == '0')
                // if '0' --> go to the left
                tempTree = tempTree->left;
            else
                // if '1' --> go to the right
                tempTree = tempTree->right;
        }
        fprintf(fw, "%c", tempTree->symb);
        pos += len;
    }
}

// main decoding function
void Decoding(FILE * fr, FILE * fw){

    int lenghtOfFile = 0, countUniSymb = 0;
    NODE * newHead = {0};

    // get information from file (length, count unique symbols, tree)
    GetInfoFromFile(&newHead, fr, &lenghtOfFile, &countUniSymb);

    // make new tree
    newHead = MakeTree(newHead);

    // the string in which the encoded message will be written in the form of zeros and ones
    char *newSrtCodes = (char*) malloc(lenghtOfFile * 32 * sizeof(char));
    BuildStrFromFile(fr, newSrtCodes);

    // decoding file
    DecodedString(fw, newHead, newSrtCodes, lenghtOfFile, strlen(newSrtCodes));
}