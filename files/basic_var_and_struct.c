#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include "basic_var_and_struct.h"

// array for the number of each symbol in the file
unsigned freq[256] = {0};

// find length of file
int findLenOfFile(FILE * fr){
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    // moving file pointer to start of file
    fseek(fr, 0, SEEK_SET);
    return length;
}

// the function of counting the number of symbols
void freqOfOccurrence(FILE * fr, unsigned *freg, long int length){
    for (int i = 0; i < length; ++i) {
        // update count of symbol for each occurrence
        freq[(unsigned char) fgetc(fr)]++;
    }
}

// add new elem to list
void AddNewNode(NODE** pphead, unsigned *freg, int count) {
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
    printf("%u(%c)%c\n", elem->freq, elem->symb, elem->isSymb);
    PrintTree(elem->left, level + 1);
}

// building code of symbols
void BuildCodes(NODE* elem, char ** symbolCodes, char * codeOfSymbol, int lenght, FILE * fw){
    if (elem->left == NULL && elem->right == NULL) {
        // allocate memory for the symbol code
        symbolCodes[elem->symb] = malloc(sizeof(char) * (lenght + 1));
        strcpy(symbolCodes[elem->symb], codeOfSymbol);

        codeOfSymbol[lenght - 1] = 0;
        printf("%c - %s\n", elem->symb, symbolCodes[elem->symb]);
        // add to the file symbol and its number of occurrences
        fprintf(fw, "%c%d|", elem->symb, elem->freq);
        return;
    }
    if (elem->left != NULL) {
        // sign of the left element - 0
        codeOfSymbol[lenght] = '0';
        BuildCodes(elem->left, symbolCodes, codeOfSymbol, lenght + 1, fw);
        codeOfSymbol[lenght] = 0;
    }
    if (elem->right != NULL) {
        // sign of the right element - 1
        codeOfSymbol[lenght] = '1';
        BuildCodes(elem->right, symbolCodes, codeOfSymbol, lenght + 1, fw);
        codeOfSymbol[lenght] = 0;
    }
}

// building encoded string
void BuildStr(FILE * fr, char ** symbolCodes, char* newStr, int len){
    for (int i = 0; i < len; ++i)
        // go through the file and replace each symbol with its code and write it to the string
        strcat(newStr, symbolCodes[fgetc(fr)]);

    // add zeros to the string so that an integer number of bytes can be written to the file
    while (strlen(newStr) % 8 != 0)
        strcat(newStr, "0");
    printf("%s\n", newStr);
}

// form a string of bits from a string of symbols and write it to a file
void BuildEncodedStr(FILE * fw, char * strCode){
    // counting the number of bytes
    unsigned long long int count = strlen(strCode) / 8;

    BIT2CHAR symb;
    // creating a string that will then be written to a file
    char * res = (char*)malloc((count) * sizeof(char));

    for (int i = 0; i < count; i += 1) {
        // each character 0 or 1 is written in a separate bit
        symb.mbit.b1 = (unsigned)strCode[i*8 + 0];
        symb.mbit.b2 = (unsigned)strCode[i*8 + 1];
        symb.mbit.b3 = (unsigned)strCode[i*8 + 2];
        symb.mbit.b4 = (unsigned)strCode[i*8 + 3];
        symb.mbit.b5 = (unsigned)strCode[i*8 + 4];
        symb.mbit.b6 = (unsigned)strCode[i*8 + 5];
        symb.mbit.b7 = (unsigned)strCode[i*8 + 6];
        symb.mbit.b8 = (unsigned)strCode[i*8 + 7];
        // get the symbol
        res[i] = symb.symb;
    }
    // write the received encrypted string to a file
    fprintf(fw, "%s", res);
}
