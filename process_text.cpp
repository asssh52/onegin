#include <ctype.h>
#include "sorting.hpp"
#include "myassert.hpp"
#include "process_text.hpp"
#include "print_strings.hpp"

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

void ProcessText(structuredText textIn, const char* filenameOut){
    FILE* stream = fopen(filenameOut, "w");
    string* strPointer = textIn.strPointer;
    size_t numLines = textIn.numLines;

    PrintTextOriginal(strPointer, numLines, stream);

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
