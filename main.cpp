#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "sorting.hpp"
#include "myassert.hpp"

typedef struct string{
    char* pointer;
    size_t length;
} string;

typedef struct structuredText{
    string* strPointer;
    size_t numLines;
    void* bufferPointer;
    FILE* filePointer;
}structuredText;

int CharCompare(char firstChar, char secondChar){
    return tolower(firstChar) - tolower(secondChar);
}

int HasLetters(string str){
    for (int i = 0; i < str.length; i++){
        if (isalpha(str.pointer[i])){
            return 1;
        }
    }
    return 0;
}

int StringCompare(void* firstStringPointer, void* secondStringPointer){
    ASSERT(firstStringPointer != NULL && secondStringPointer != NULL);
    string firstString = *(string*)firstStringPointer;
    string secondString = *(string*)secondStringPointer;

    ASSERT((firstString.pointer != NULL) && (secondString.pointer != NULL));

    if (!HasLetters(firstString) && !HasLetters(firstString)){
        if (firstString.length > secondString.length){
            return 1;
        }
        return  0;
    } else if (!HasLetters(firstString)){
        return -1;
    } else if (!HasLetters(secondString)){
        return  1;
    }

    for (int i = 0, j = 0; i < firstString.length && i < secondString.length; i++, j++){
        while(ispunct(firstString.pointer[i]) || isspace(firstString.pointer[i])){
            i++;
        }
        while(ispunct(secondString.pointer[j]) || isspace(secondString.pointer[j])){
            j++;
        }

        if (CharCompare(firstString.pointer[i], secondString.pointer[j]) > 0){
                return 1; // first bigger
        }
        else if (CharCompare(firstString.pointer[i], secondString.pointer[j]) < 0) {
                return -1; // second bigger
        }
    }
    if (firstString.length > secondString.length){
        return 1;
    }
    return 0;
}

int StringCompareReversed(void* firstStringPointer, void* secondStringPointer){
    ASSERT(firstStringPointer != NULL && secondStringPointer != NULL);
    string firstString = *(string*)firstStringPointer;
    string secondString = *(string*)secondStringPointer;

    ASSERT((firstString.pointer != NULL) && (secondString.pointer != NULL));

    if (!HasLetters(firstString) && !HasLetters(firstString)){
        return  0;
    } else if (!HasLetters(firstString)){
        return -1;
    } else if (!HasLetters(secondString)){
        return  1;
    }

    for (int i = firstString.length, j = secondString.length; i > 0 && j > 0; i--, j--){
        while(ispunct(firstString.pointer[i]) || isspace(firstString.pointer[i])){
            i--;
        }
        while(ispunct(secondString.pointer[j]) || isspace(secondString.pointer[j])){
            j--;
        }

        if (CharCompare(firstString.pointer[i], secondString.pointer[j]) > 0){
                return 1; // first bigger
        }
        else if (CharCompare(firstString.pointer[i], secondString.pointer[j]) < 0) {
                return -1; // second bigger
        }
    }
    if (firstString.length > secondString.length){
        return 1;
    }
    return 0;
}

void SplitText(char* buffer, string* storage){
    ASSERT(buffer != nullptr && storage != nullptr)

    int lineCounter = 0;
    storage[0].pointer = buffer;

    for (int i = 0; buffer[i] != EOF; i++){
        if (buffer[i] == '\n'){
            lineCounter++;
            storage[lineCounter].pointer = (char*)((size_t)buffer + i);
            storage[lineCounter - 1].length = storage[lineCounter].pointer - storage[lineCounter - 1].pointer;
        }
    }
}

void PrintText(string* sourceStrText, size_t numLines, FILE* outputLink){
    ASSERT(sourceStrText != nullptr && outputLink != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 1;
        //fprintf(outputLink, "line:%d ", i + 1);
        while (isspace(((sourceStrText[i]).pointer)[j])){
                j++;
            }
        for (; j < (sourceStrText[i]).length; j++){
            if (((sourceStrText[i]).pointer)[j] != '\n'){
                fprintf(outputLink, "%c", ((sourceStrText[i]).pointer)[j]);
            }
        }
        fprintf(outputLink, "\n");
    }
}

void PrintTextDebug(string* sourceStrText, size_t numLines, FILE* outputLink){
    ASSERT(sourceStrText != nullptr && outputLink != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 1;
        //fprintf(outputLink, "line:%d ", i + 1);
        while (isspace(((sourceStrText[i]).pointer)[j])){
                j++;
            }
        for (; j < (sourceStrText[i]).length; j++){
            if (j <= 4){
                if (((sourceStrText[i]).pointer)[j] != '\n'){
                    fprintf(outputLink, "<%c(%d)>", ((sourceStrText[i]).pointer)[j], ((sourceStrText[i]).pointer)[j]);
                }
            } else {
                if (((sourceStrText[i]).pointer)[j] != '\n'){
                    fprintf(outputLink, "%c", ((sourceStrText[i]).pointer)[j]);
                }
            }
        }
        fprintf(outputLink, "\n");
    }
}

void PrintIntro(FILE* outputLink){
    ASSERT(outputLink != nullptr);
    fprintf(outputLink, "**-------------------------**");
    fprintf(outputLink, "\n\n\n\t\tSORTED LINES:\n\n\n");
    fprintf(outputLink, "**-------------------------**\n");
}

void PrintOutro(FILE* outputLink){
    ASSERT(outputLink != nullptr);
    fprintf(outputLink, "**-------------------------**");
    fprintf(outputLink, "\n\n\n\t\tINVERSE SORTED LINES:\n\n\n");
    fprintf(outputLink, "**-------------------------**\n");
}

void PrintOriginalText(string* sourceStrText, size_t numLines, FILE* outputLink){
    ASSERT(sourceStrText != nullptr && outputLink != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 0;
        for (; j < (sourceStrText[i]).length; j++){
            if (((sourceStrText[i]).pointer)[j] != '\n'){
                fprintf(outputLink, "%c", ((sourceStrText[i]).pointer)[j]);
            }
        }
        fprintf(outputLink, "\n");
    }
}

void CountLines(char* buffer, size_t* numberLines){
    size_t counter = 0;
    for (int i = 0; buffer[i] != EOF; i++){
        if (buffer[i] == '\n'){
            counter++;
        }
    }
    *numberLines = counter;
}

size_t GetFileSize(const char* source){
    struct stat st;
    stat(source, &st);
    size_t fileSize = st.st_size;

    return fileSize;
}

void GetFileContent(void* bufferPointer, size_t sizeOfElem, size_t fileSize, FILE* sourceFileLink){
    ASSERT(sourceFileLink != NULL && bufferPointer != NULL);
    fread(bufferPointer, sizeof(char), fileSize, sourceFileLink);
    ((char*)bufferPointer)[fileSize] = -1;
}

void SortAndOutput(string* strPointer, size_t numLines, FILE* stream){
    PrintOriginalText(strPointer, numLines, stream);

    PrintIntro(stream);

    QuickSort(strPointer, numLines, sizeof(string), StringCompare);
    PrintText(strPointer, numLines, stream);

    PrintOutro(stream);

    QuickSort(strPointer, numLines, sizeof(string), StringCompareReversed);
    PrintText(strPointer, numLines, stream);

    printf(COLOR_GREEN "sorted successfully\n" COLOR_RESET);
}

structuredText StructureText(const char* filenameIn){
    FILE* sourceFileLink = fopen(filenameIn, "r");
    size_t fileSize = GetFileSize(filenameIn);

    void* bufferPointer = calloc(fileSize, sizeof(char));
    GetFileContent(bufferPointer, sizeof(char), fileSize, sourceFileLink);

    size_t numLines = 0;
    CountLines((char*)bufferPointer, &numLines);

    string* strPointer = (string*)calloc(numLines + 1, sizeof(string));
    SplitText((char*)bufferPointer, (string*)strPointer);

    structuredText outputText = {};
    outputText.numLines = numLines;
    outputText.strPointer = strPointer;
    outputText.bufferPointer = bufferPointer;
    outputText.filePointer = sourceFileLink;

    return outputText;
}

void ProcessText(structuredText textIn, const char* filenameOut){
    FILE* stream = fopen(filenameOut, "w");
    string* strPointer = textIn.strPointer;
    size_t numLines = textIn.numLines;

    PrintOriginalText(strPointer, numLines, stream);

    PrintIntro(stream);

    QuickSort(strPointer, numLines, sizeof(string), StringCompare);
    PrintText(strPointer, numLines, stream);

    PrintOutro(stream);

    QuickSort(strPointer, numLines, sizeof(string), StringCompareReversed);
    PrintText(strPointer, numLines, stream);

    printf(COLOR_GREEN "sorted successfully\n" COLOR_RESET);

    if (stream != stdout){
        fclose(stream);
    }
}

void FreeAndClose(structuredText outputText){
    free(outputText.strPointer);
    free(outputText.bufferPointer);
    fclose(outputText.filePointer);
}


int main(int argc, const char* argv[]){
    const char* filenameIn  = (argc == 2)? argv[1] : "onegin.txt";
    const char* filenameOut = (argc == 3)? argv[2] : "out_onegin.txt";

    structuredText onegin = StructureText(filenameIn);
    ProcessText(onegin, filenameOut);

    structuredText hamlet = StructureText("hamlet.txt");
    ProcessText(hamlet, "out_hamlet.txt");

    FreeAndClose(onegin);
    FreeAndClose(hamlet);
    return 0;
}
