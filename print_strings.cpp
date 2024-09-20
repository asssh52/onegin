#include <ctype.h>
#include "print_strings.hpp"
#include "myassert.hpp"

void PrintTextOriginal(string* sourceStrText, size_t numLines, FILE* outputLink){
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

void PrintText(string* sourceStrText, size_t numLines, FILE* outputLink){
    ASSERT(sourceStrText != nullptr && outputLink != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 1;
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
