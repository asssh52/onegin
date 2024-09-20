#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "myassert.hpp"
#include "structure_text.hpp"

structuredText StructureText  (const char* filenameIn);
size_t         GetFileSize    (const char* source);
void           GetFileContent (void* bufferPointer, size_t sizeOfElem, size_t fileSize, FILE* sourceFileLink);
void           CountLines     (char* buffer, size_t* numberLines);
void           SplitText      (char* buffer, string* storage);
void           FreeAndClose   (structuredText outputText);

structuredText StructureText(const char* filenameIn){
    ASSERT(filenameIn != nullptr);

    FILE* sourceFileLink = fopen(filenameIn, "r");
    size_t fileSize = GetFileSize(filenameIn);

    void* bufferPointer = calloc(fileSize + 1, sizeof(char)); //magic fileSize + 1
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

void GetFileContent(void* bufferPointer, size_t sizeOfElem, size_t fileSize, FILE* sourceFileLink){
    ASSERT(sourceFileLink != NULL && bufferPointer != NULL);

    fread(bufferPointer, sizeOfElem, fileSize, sourceFileLink);
    ((char*)bufferPointer)[fileSize] = -1;
}

size_t GetFileSize(const char* source){
    ASSERT(source != nullptr);

    struct stat st;
    stat(source, &st);
    size_t fileSize = st.st_size;

    return fileSize;
}

void CountLines(char* buffer, size_t* numberLines){
    ASSERT(buffer != nullptr && numberLines != nullptr);

    size_t counter = 0;
    for (int i = 0; buffer[i] != EOF; i++){
        if (buffer[i] == '\n'){
            counter++;
        }
    }
    *numberLines = counter;
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

void FreeAndClose(structuredText outputText){
    free(outputText.strPointer);
    free(outputText.bufferPointer);
    fclose(outputText.filePointer);
}
