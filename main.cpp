#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLOR_RESET         "\x1b[0m"
#define COLOR_RED          "\x1b[31m"
#define ASSERT(x) if (!(x)) { printf(COLOR_RED "\nThe programm has been aborted.\n"\
                                               "Line %d of file %s, function %s.\n\n" COLOR_RESET,\
                                            __LINE__, __FILE__, __func__); abort();}
enum sizes{
    STR_LENGTH = 60,
    STR_NUM = 8,
    FILE_SIZE = 600
};



int CharCompare(char firstChar, char secondChar){
    return tolower(firstChar) - tolower(secondChar);
}

int StringCompare(const char* firstString, const char* secondString){
    ASSERT(firstString != NULL && secondString != NULL);

    for (int i = 0, j = 0; i < STR_LENGTH; i++, j++){
        while(ispunct(firstString[i])){
            i++;
        }
        while(ispunct(secondString[j])){
            j++;
        }

        if (CharCompare(firstString[i], secondString[j]) > 0){
                return 1; // first bigger
        }
        else if (CharCompare(firstString[i], secondString[j]) < 0) {
                return -1; // second bigger
        }
    }
    return 0;
}

void SwapStrings(char* firstString, char* secondString){
    ASSERT(firstString != NULL && secondString != NULL);
    char temp;

    for (int i = 0; i < STR_LENGTH; i++){
        temp = firstString[i];
        firstString[i] = secondString[i];
        secondString[i] = temp;
    }

}

void BubbleSortStrings(char** sourceText){
    ASSERT(sourceText != NULL);

    for (int first = 0; first < STR_NUM; first++){
        for (int second = 0; second < STR_NUM - 1; second++){
            if (StringCompare(sourceText[second], sourceText[second + 1]) > 0){
                SwapStrings(sourceText[second], sourceText[second + 1]);
            }
        }
    }
}

void SplitText(char* buffer, char** storage){
    int lineCounter = 0;
    *storage = buffer; // mem start

    for (int i = 0; buffer[i] != EOF; i++){
        if (buffer[i] == '\n'){
            lineCounter++;
            printf("%lu ", (size_t)(buffer + i));
            *(storage + lineCounter) = (char*)((size_t)buffer + i);
        }
    }
    //printf("%d\n", lineCounter);
}

void PrintTextDebug(const char** sourceText){
    for (int i = 0; i < STR_NUM; i++){
        for (int j = 0; j < STR_LENGTH; j++){
            if (j <= 2){
                printf("%c(%d)", sourceText[i][j], (int)sourceText[i][j]);
            } else
            printf("%c", sourceText[i][j]);
        }
        printf("\n\n");
    }
}

void PrintText(const char** sourceText){
    for (int i = 0; i < STR_NUM; i++){
        printf("%s\n", sourceText[i]);
    }
}

int main(){

    const char* sourceFile = "onegin.txt";
    FILE* sourceFileLink = fopen(sourceFile, "r");

    char sourceOnegin[STR_NUM][STR_LENGTH] = {      {    "``My uncle -- high ideals inspire him;"   },
                                                    {    "but when past joking he fell sick,"       },
                                                    {    "he really forced one to admire him --"    },
                                                    {    "and never played a shrewder trick."       },
                                                    {    "Let others learn from his example!"       },
                                                    {    "But God, how deadly dull to sample"       },
                                                    {    "sickroom attendance night and day"        },
                                                    {    "and never stir a foot away!"              }};

    char* sourcePointer[STR_NUM] = {};

    for (int i = 0; i < STR_NUM; i++){
        sourcePointer[i] = sourceOnegin[i];
    }

    void* bufferPointer = calloc(FILE_SIZE, sizeof(char));
    char** textPointer = (char**)calloc(STR_NUM + 1, sizeof(char*)); // что здесь происходит???

    ASSERT(sourceFileLink != NULL && bufferPointer != NULL);
    fread(bufferPointer, sizeof(char), FILE_SIZE, sourceFileLink);

    SplitText((char*)bufferPointer, (char**)textPointer);

    printf("\n\n");
    for (int i = 0; i < STR_NUM; i++){
        printf("%lu \n", *(textPointer + i));
    }

    printf("%d\n", *(textPointer + 2) - *(textPointer + 0));

    for (int i = 0; i < *(textPointer + 2) - *(textPointer + 0); i++){
        printf("%c'%d'", *(char*)((size_t)bufferPointer + i), *(char*)((size_t)bufferPointer + i));
    }

    //BubbleSortStrings(sourcePointer);
    //PrintText((const char**)sourcePointer);

    //создать "массив чтения" || менять указатели на строки
    return 0;
}
