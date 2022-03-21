#include "coding.h"

// array for the number of each symbol in the file
unsigned freq[256] = {0};

// find length of file
long long findLenOfFile(FILE * fr){
    fseek(fr, 0L, SEEK_END);
    long long length = ftell(fr);
    // moving file pointer to start of file
    fseek(fr, 0, SEEK_SET);
    return length;
}

// the function of counting the number of symbols
void freqOfOccurrence(FILE * fr, unsigned *freg, long long length){
    for (int i = 0; i < length; ++i) {
        // update count of symbol for each occurrence
        freq[(unsigned char) fgetc(fr)] += 1;
    }
}

// add new elem to list
void AddNewNode(NODE** pphead, const unsigned *freg, int count) {
    while (*pphead) {
        // finding a suitable position for new node of list
        if ((*pphead)->freq > freg[count])
            break;
        pphead = &((*pphead)->next);
    }
    NODE* pnew = (NODE*)malloc(sizeof(NODE));
    pnew->symb = (char)count;
    pnew->freq = (int)freq[count];
    // pointer to the next elem
    pnew->next = *pphead;
    // left and right = NULL to avoid using unallocated memory in the future
    pnew->left = NULL;
    pnew->right = NULL;
    *pphead = pnew;
}

// add new node to tree
void Add2Tree(NODE** head, NODE* elem){
    while (*head) {
        // finding a suitable position for new elem of tree
        if ((*head)->freq > elem->freq)
            break;
        head = &((*head)->next);
    }
    elem->next = *head;
    *head = elem;
}

// make new node of tree
NODE * MakeNode(NODE* left, NODE* right){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    // the sum of the frequencies of the two elements (left and right)
    new->freq = left->freq + right->freq;
    new->isSymb = 0;
    new->symb = 0;
    new->left = left;
    new->right = right;
    new->next = 0;
    return new;
}

// make tree from list
NODE * MakeTree(NODE* elem){
    while (elem && elem->next){
        NODE * left = elem;
        // sign of the left element - 0
        left->isSymb = '0';
        NODE * right = elem->next;
        // sign of the right element - 1
        right->isSymb = '1';
        // add to tree new node
        Add2Tree(&(elem->next->next), MakeNode(left, right));
        elem = elem->next->next;
    }
    return elem;
}

// print tree on display
void PrintTree(NODE* elem, int level){
    if (!elem) return;
    // recursively go through the tree to the right
    PrintTree(elem->right, level + 1);
    for (int i = 0; i < level; i += 1)
        printf("\t");
    if (!elem->left && !elem->right)
        printf("%u={%d}\n", elem->symb,elem->freq);
    else
        printf("<\n");
    PrintTree(elem->left, level + 1);
}

// building code of symbols
void BuildCodes(NODE* elem, CODETABLE * tableCode, char * codeOfSymbol, int lenght, FILE * fw){
    if (elem->left == NULL && elem->right == NULL) {
        // allocate memory for the symbol code
        tableCode[elem->symb].codeOfSymbol = malloc(sizeof(char) * (lenght + 1));
        codeOfSymbol[lenght] = 0;
        strcpy(tableCode[elem->symb].codeOfSymbol, codeOfSymbol);
        tableCode[elem->symb].lenOfCode = lenght;
        codeOfSymbol[lenght - 1] = 0;
        //printf("%c - %s\n", elem->symb, tableCode[elem->symb].codeOfSymbol);
        // add to the file symbol and its number of occurrences
        //fprintf(fw, "%c%d|", elem->symb, elem->freq);
        return;
    }
    if (elem->left != NULL) {
        // sign of the left element - 0
        codeOfSymbol[lenght] = '0';
        BuildCodes(elem->left, tableCode, codeOfSymbol, lenght + 1, fw);
        codeOfSymbol[lenght] = 0;
    }
    if (elem->right != NULL) {
        // sign of the right element - 1
        codeOfSymbol[lenght] = '1';
        BuildCodes(elem->right, tableCode, codeOfSymbol, lenght + 1, fw);
        codeOfSymbol[lenght] = 0;
    }
}

// building encoded string
void BuildStr(FILE * fr, CODETABLE * tableCode, char* newStr, int len){
    char *testStr = newStr;
    //printf("111111111111111111111111\n");
    for (int i = 0; i < len; ++i) {
        //printf("%d\n", i);
        // go through the file and replace each symbol with its code and write it to the string
        int symb = fgetc(fr);
        //tableCode[symb].codeOfSymbol[tableCode[symb].lenOfCode] = 0;
        memcpy(newStr, tableCode[symb].codeOfSymbol, tableCode[symb].lenOfCode);
        newStr += tableCode[symb].lenOfCode;
    }

    // add zeros to the string so that an integer number of bytes can be written to the file
    //printf("3333333333333333333333\n");
    while (strlen(testStr) % 8 != 0) {
        memcpy(newStr, "0", 1);
        newStr += 1;
    }
    //printf("222222222222222222222222\n");
    //printf("%s - %d\n", testStr, strlen(testStr));
}

// form a string of bits from a string of symbols and write it to a file
void BuildEncodedStr(FILE * fw, char * strCode){
    // counting the number of bytes
    unsigned long long int count = strlen(strCode) / 8;
    //printf("aaaaaaaaa");
    //printf("\n%d\n", count);

    BIT2CHAR symb;
    // creating a string that will then be written to a file
    char * res = (char*)malloc((count) * sizeof(char));

    for (int i = 0; i < count; i += 1) {
        // each character 0 or 1 is written in a separate bit
        symb.mbit.b1 = strCode[i*8 + 0] == '1';
        symb.mbit.b2 = strCode[i*8 + 1] == '1';
        symb.mbit.b3 = strCode[i*8 + 2] == '1';
        symb.mbit.b4 = strCode[i*8 + 3] == '1';
        symb.mbit.b5 = strCode[i*8 + 4] == '1';
        symb.mbit.b6 = strCode[i*8 + 5] == '1';
        symb.mbit.b7 = strCode[i*8 + 6] == '1';
        symb.mbit.b8 = strCode[i*8 + 7] == '1';
        // get the symbol
        res[i] = symb.symb;
    }
    //res[count] = '\0';
    // write the received encrypted string to a file
    //fprintf(fw, "%s", res);
    //printf("fffffffffffffffffffffffffffff");
    fwrite(res, 1, count, fw);
    //printf("%s", res);
}


void PrintNode2File(NODE * elem, FILE * fw){
    while (elem->next) {
        fprintf(fw, "%d %d ", elem->symb, elem->freq);
        elem = elem->next;
    }
    fprintf(fw, "%d %d\n", elem->symb, elem->freq);
}

void PrintNode(NODE * elem){
    while (elem->next) {
        printf("%u\t=%d\n", elem->symb, elem->freq);
        elem = elem->next;
    }
    printf("%u\t=%d\n", elem->symb, elem->freq);
}

void Coding(FILE* fr, FILE * fw, int length){

    // print to file lenght of the file
    fprintf(fw, "%d ", length);

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
            ++countOfDifSymb;
        }
    }
    // print to the file count of unique symbols
    fprintf(fw, "%d ", countOfDifSymb);
    PrintNode2File(head, fw);

    //PrintNode(head);

    // make binary tree from the list
    head = MakeTree(head);
    //PrintTree(head, 0);

    // two-dimensional array with symbol codes
    //char * symbolCode[256] = {};
    // string with code of one symbol
    char codeSymb[33] = "";

    CODETABLE symbolCode[256] = {0};

    // filling a two-dimensional array with codes and ADD TREE to the file
    BuildCodes(head, symbolCode, codeSymb, 0, fw);

    // string, where each source symbol is replaced with its bit code
    char * srtCodes = (char*) calloc(length * 32, sizeof(char));
    //int lenBinString = 0;
    BuildStr(fr, symbolCode, srtCodes, length);

    // form a string of symbols from a string of bits and write it to a file
    BuildEncodedStr(fw, srtCodes);
    // close al file
    fclose(fw);
}
