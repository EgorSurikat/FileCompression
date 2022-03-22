#include "coding.h"
#include "decoding.h"


int main() {
    FILE * fr = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\test_1", "rb");
    if (!fr) return 1;

    // open the file in which the encoded information will be stored
    FILE * fw = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\output", "wb");
    if (!fw) return 1;
    // length of file
    long long length = findLenOfFile(fr);

    Coding(fr, fw, length);

    printf("---------------------------------------------\n");

    // open the file which has the encoded information
    FILE * fileR = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\output", "rb");
    if (!fileR) return 1;

    FILE * newf = fopen("C:\\Users\\ed230\\CLionProjects\\FileCompression\\tests_files\\decoded", "wb");
    if (!newf) return 1;

    Decoding(fileR, newf);

    return 0;
}