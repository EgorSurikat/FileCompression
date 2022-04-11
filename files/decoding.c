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
        int count;
        fscanf(fw, "%d ", &count);
        newFreq[symbol] = count;
        AddNewNode(new, newFreq, symbol);
    }
}

// build encoded message in the form of zeros and ones
void BuildStrFromFile(FILE * fr, FILE * fw, NODE * tree, int *len){
    BIT2CHAR symb;
    char *string = (char*) calloc(10001, sizeof(char));
    char * startStr = string;
    int i = 0;
    while (1) {
        int symbol = fgetc(fr);
        if (symbol == EOF)
            break;
        symb.symb = (char) symbol;

        string[0] = symb.mbit.b1 ? '1' : '0';
        string[1] = symb.mbit.b2 ? '1' : '0';
        string[2] = symb.mbit.b3 ? '1' : '0';
        string[3] = symb.mbit.b4 ? '1' : '0';
        string[4] = symb.mbit.b5 ? '1' : '0';
        string[5] = symb.mbit.b6 ? '1' : '0';
        string[6] = symb.mbit.b7 ? '1' : '0';
        string[7] = symb.mbit.b8 ? '1' : '0';
        string += 8;
        i += 8;
        if (i > 9968) {
            // we decode the filled string and write the file, while preserving the remainder
            const char * ogris = DecodedString(fw, tree, startStr, len, i, 0);
            i = (int)(string - ogris);
            memcpy(startStr, ogris, i);
            string = startStr + i;
        }
    }
    DecodedString(fw, tree, startStr, len, i, 1);
}

// decoding file from string in the form of zeros and ones
const char * DecodedString(FILE *fw, NODE *tree, const char *str, int* len, int capacity, int eof) {
    int pos;
    for (pos = 0; *len > 0 && (pos < capacity - 32 || pos < capacity && eof); --(*len)) {
        int length = 0;
        NODE * tempTree = tree;
        while (tempTree->left || tempTree->right) tempTree = str[pos + length++] == '0' ? tempTree->left : tempTree->right;
        pos += length;
        fprintf(fw, "%c", tempTree->symb);
    }
    return str + pos;
}

// main decoding function
void Decoding(FILE * fr, FILE * fw){

    int lenghtOfFile = 0, countUniSymb = 0;
    NODE * newHead = {0};

    // get information from file (length, count unique symbols, tree)
    GetInfoFromFile(&newHead, fr, &lenghtOfFile, &countUniSymb);

    // make new tree
    newHead = MakeTree(newHead);

    // string with code of one symbol
    char codeSymbol[33] = "";

    // struct with codes of symbols
    CODETABLE symbolCodes[256] = {0};

    // filling a two-dimensional array with codes and ADD TREE to the file
    BuildCodes(newHead, symbolCodes, codeSymbol, 0, fw);

    // build encoded message in the form of zeros and ones
    BuildStrFromFile(fr, fw, newHead, &lenghtOfFile);

    // close all files
    fclose(fr);
    fclose(fw);
}