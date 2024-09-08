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
    STR_NUM = 14,
    FILE_SIZE = 600
};



int CharCompare(char firstChar, char secondChar){
    return tolower(firstChar) - tolower(secondChar);
}

int StringCompare(const char* firstString, const char* secondString){
    ASSERT(firstString != NULL && secondString != NULL);

    for (int i = 0, j = 0; i < STR_LENGTH; i++, j++){
        while(ispunct(firstString[i]) || isspace(firstString[i])){
            i++;
        }
        while(ispunct(secondString[j]) || isspace(secondString[j])){
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

int StringCompareDebug(const char* firstString, const char* secondString){
    ASSERT(firstString != NULL && secondString != NULL);

    for (int i = 0, j = 0; i < STR_LENGTH; i++, j++){
        while(ispunct(firstString[i]) || isspace(firstString[i])){
            i++;
        }
        while(ispunct(secondString[j]) || isspace(secondString[j])){
            j++;
        }

        if (CharCompare(firstString[i], secondString[j]) > 0){
            printf("i:%d ch:%c(%d) \nj:%d ch:%c(%d)", i, firstString[i], firstString[i], j, secondString[j], secondString[j]);
            return 1; // first bigger
        }
        else if (CharCompare(firstString[i], secondString[j]) < 0) {
                printf("i:%d ch:%c(%d) \nj:%d ch:%c(%d)", i, firstString[i], firstString[i], j, secondString[j], secondString[j]);
                return -1; // second bigger
        }
    }
    return 0;
}

void SwapStrings(char* firstString, char* secondString){ // dont need
    ASSERT(firstString != NULL && secondString != NULL);
    char temp;

    for (int i = 0; i < STR_LENGTH; i++){
        temp = firstString[i];
        firstString[i] = secondString[i];
        secondString[i] = temp;
    }

}

void SwapStringPointers(char** firstString, char** secondString){
    ASSERT(firstString != NULL && secondString != NULL);
    char* temp = nullptr;

    temp = *firstString;
    *firstString = *secondString;
    *secondString = temp;
}

void BubbleSortStrings(char** sourceText, size_t size){
    ASSERT(sourceText != NULL);

    for (int first = 0; first < size; first++){
        for (int second = 0; second < size - 1; second++){
            if (StringCompare(sourceText[second], sourceText[second + 1]) > 0){
                SwapStringPointers(&sourceText[second], &sourceText[second + 1]);
            }
        }
    }
}

void SplitText(char* buffer, char** storage){
    ASSERT(buffer != nullptr && storage != nullptr)

    int lineCounter = 0;
    *storage = buffer;

    for (int i = 0; buffer[i] != EOF; i++){
        if (buffer[i] == '\n'){
            lineCounter++;
            *(storage + lineCounter) = (char*)((size_t)buffer + i);
        }
    }
}

void CopyContent(char** origin, char** output, size_t size){ //dont need
    ASSERT(origin != nullptr && output != nullptr)

    for (int i = 0; i < size; i++){
        output[i] = origin[i];
    }
}

void PrintText(const char** sourceText){
    printf("%c", sourceText[0][0]);
    for (int i = 0; i < STR_NUM; i++){
        for (int j = 1; sourceText[i][j] != '\n' && sourceText[i][j] != EOF; j++){
            printf("%c", sourceText[i][j]);
        }
        printf("\n");
    }
}

void PrintTextDebug(const char** sourceText){
    printf("%c", sourceText[0][0]);
    for (int i = 0; i < STR_NUM; i++){
        for (int j = 1; sourceText[i][j] != '\n' && sourceText[i][j] != EOF; j++){
            if (4 <= j && j <= 7){
                printf("(<%c>'%d')", tolower(sourceText[i][j]), tolower(sourceText[i][j]));
            } else
            printf("%c", sourceText[i][j]);
        }
        printf("\n");
    }
}

int main(){

    const char* sourceFile = "onegin.txt";
    FILE* sourceFileLink = fopen(sourceFile, "r");

    void* bufferPointer = calloc(FILE_SIZE, sizeof(char));
    char** originalTextPointer = (char**)calloc(STR_NUM + 1, sizeof(char*)); // что здесь происходит???

    ASSERT(sourceFileLink != NULL && bufferPointer != NULL);
    fread(bufferPointer, sizeof(char), FILE_SIZE, sourceFileLink);

    SplitText((char*)bufferPointer, (char**)originalTextPointer);

    char** textSortedPointer = (char**)calloc(STR_NUM + 1, sizeof(char*));
    CopyContent(originalTextPointer, textSortedPointer, STR_NUM + 1);

    PrintText((const char**)textSortedPointer);
    BubbleSortStrings(textSortedPointer, STR_NUM);
    PrintText((const char**)textSortedPointer);

    /*//debug
    //printf("%d\n", StringCompare(textSortedPointer[12], textSortedPointer[13]));

    char * first =  "     ``My uncle -- high ideals inspire him;";
    char * second = "     \"When will the devil come for you?\"''";
    printf("%d", StringCompareDebug(textSortedPointer[0], textSortedPointer[13]));



    //debug*/
    return 0;
}
