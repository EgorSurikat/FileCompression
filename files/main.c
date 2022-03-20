#include "basic_var_and_struct.h"


int main() {
    FILE * fr = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\test_1", "rb");
    if (!fr) return 1;
    // length of file
    long int length = findLenOfFile(fr);
    // how many times does each character occur in the file
    freqOfOccurrence(fr, freq, length);
    // moving file pointer to start of file
    fseek(fr, 0, SEEK_SET);

    // count of different symbols
    int countOfDifSymb = 0;

    NODE *head = {0};
    for (int i = 0; i <256; i += 1) {
        if (freq[i] != 0) {
            // add symbol in struct if he is in the file
            AddNewNode(&head, freq, i);
            countOfDifSymb += 1;
        }
    }
    // make binary tree from the list
    head = MakeTree(head);
    PrintTree(head, 0);

    // open the file in which the encoded information will be stored
    FILE * fw = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\output", "w");
    fprintf(fw, "%d ", countOfDifSymb);

    // two-dimensional array with symbol codes
    char * symbolCode[256] = {};
    // string with code of one symbol
    char codeSymb[32] = "";
    // filling a two-dimensional array with codes and ADD TREE to the file
    BuildCodes(head, symbolCode, codeSymb, 0, fw);

    // string, where each source symbol is replaced with its bit code
    char * srtCodes = (char*) calloc(length * 32, sizeof(char));
    BuildStr(fr, symbolCode, srtCodes, length);

    // form a string of symbols from a string of bits and write it to a file
    BuildEncodedStr(fw, srtCodes);
    // close all files
    fclose(fw);
    fclose(fr);
    return 0;
}