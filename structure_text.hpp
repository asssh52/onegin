#pragma once

#include <stdio.h>

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

structuredText StructureText(const char* filenameIn);
void FreeAndClose(structuredText outputText);
