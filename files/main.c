#include "coding.h"
#include "decoding.h"
#include <time.h>


int StartDecoding(){

    char fileToDecomp[90] = {0};
    strcat(fileToDecomp, "C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\");

    printf("Please, input name of the file, witch will be decompress:\n");
    char fileNameToDecomp[20] = {0};
    scanf("%s", &fileNameToDecomp);
    strcat(fileToDecomp, fileNameToDecomp);

    // open the file which has the encoded information
    FILE * fileR = fopen(fileToDecomp, "rb");
    if (!fileR) {
        printf("\nincorrect data\n");
        return 0;
    }

    char fileToOut[90] = {0};
    strcat(fileToOut, "C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\");

    printf("Please, input name of the file, where the decoded information will be recorded:\n");
    char fileNameToOut[20] = {0};
    scanf("%s", &fileNameToOut);
    strcat(fileToOut, fileNameToOut);

    FILE * newf = fopen(fileToOut, "wb");
    if (!newf) {
        printf("\nincorrect data\n");
        return 0;
    }

    Decoding(fileR, newf);

    printf("\ndecoding successfully finished\n");
}


int StartCoding(){

    char fileToComp[90] = {0};
    strcat(fileToComp, "C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\");

    printf("Please, input name of the file, witch will be compress:\n");
    char fileNameToComp[20] = {0};
    scanf("%s", &fileNameToComp);
    strcat(fileToComp, fileNameToComp);

    FILE * fr = fopen(fileToComp, "rb");
    if (!fr) {
        printf("\nincorrect data\n");
        return 0;
    }

    char fileToCod[90] = {0};
    strcat(fileToCod, "C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\");

    printf("Please, input name of the file, where the encoded information will be recorded:\n");
    char fileNameToCod[20] = {0};
    scanf("%s", &fileNameToCod);
    strcat(fileToCod, fileNameToCod);

    // open the file in which the encoded information will be stored
    FILE * fw = fopen(fileToCod, "wb");
    if (!fw) {
        printf("\nincorrect data\n");
        return 0;
    }
    // length of file
    long long length = findLenOfFile(fr);

    clock_t t0 = clock();

    Coding(fr, fw, length);

    clock_t t1 = clock();

    double time_in_seconds = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("\ncoding successfully finished\n");
    printf("time of processing - %lf\n", time_in_seconds);

}



int main() {
    printf("Welcome to FileCompression!\n");
    while (1) {
        printf("---------------------------------------------\nWhat do you want?\n");
        char input[15] = {0};
        scanf("%s", &input);

        if (strcmp(input, "coding") == 0)
            StartCoding();

        else if (strcmp(input, "decoding") == 0)
            StartDecoding();

        else if (strcmp(input, "end") == 0)
            break;

        else
            printf("\nincorrect data\n");
    }
    return 0;
}