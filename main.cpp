#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

#define COLOR_RESET         "\x1b[0m"
#define COLOR_RED          "\x1b[31m"
#define ASSERT(x) if (!(x)) { printf(COLOR_RED "\nThe programm has been aborted.\n"\
                                               "Line %d of file %s, function %s.\n\n" COLOR_RESET,\
                                            __LINE__, __FILE__, __func__); abort();}

typedef struct string{
    char* pointer;
    size_t length;
} string;

int MaxNum(long a, long b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

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

int StringCompare(string firstString, string secondString){
    ASSERT(firstString.pointer != NULL && secondString.pointer != NULL);

    if (!HasLetters(firstString) && !HasLetters(firstString)){
        return 0;
    } else if (!HasLetters(firstString)){
        return -1;
    } else if (!HasLetters(secondString)){
        return 1;
    }

    for (int i = 0, j = 0; i < firstString.length && i < secondString.length; i++, j++){ // size избыточен?
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
    return 0;
}

void SwapStringPointers(string* firstString, string* secondString){
    ASSERT(firstString != NULL && secondString != NULL);
    string temp = {0,0};

    temp = *firstString;
    *firstString = *secondString;
    *secondString = temp;
}

void BubbleSortStrings(string* sourceStrText, size_t size){
    ASSERT(sourceStrText != NULL);

    for (int first = 0; first < size; first++){
        for (int second = 0; second < size - 1; second++){
            if (StringCompare(sourceStrText[second], sourceStrText[second + 1]) > 0){
                SwapStringPointers(&sourceStrText[second], &sourceStrText[second + 1]);
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

void CopyContent(char** origin, char** output, size_t size){
    ASSERT(origin != nullptr && output != nullptr)

    for (int i = 0; i < size; i++){
        output[i] = origin[i];
    }
}

void PrintText(string* sourceStrText, size_t numLines){
    ASSERT(sourceStrText != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 1;
        printf("line:%d ", i + 1);
        while (isspace(((sourceStrText[i]).pointer)[j])){
                j++;
            }
        for (; j < (sourceStrText[i]).length; j++){
            if (((sourceStrText[i]).pointer)[j] != '\n'){
                printf("%c", ((sourceStrText[i]).pointer)[j]);
            }
        }
        printf("\n");
    }
}

void PrintOriginalText(string* sourceStrText, size_t numLines){
    ASSERT(sourceStrText != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 0;
        for (; j < (sourceStrText[i]).length; j++){
            if (((sourceStrText[i]).pointer)[j] != '\n'){
                printf("%c", ((sourceStrText[i]).pointer)[j]);
            }
        }
        printf("\n");
    }
}

void PrintTextDebug(string* sourceStrText, size_t numLines){
    ASSERT(sourceStrText != nullptr);

    for (int i = 0; i < numLines; i++){
        size_t j = 1;
        printf("line:%d ", i + 1);
        while (isspace(((sourceStrText[i]).pointer)[j])){
                j++;
            }
        for (; j < (sourceStrText[i]).length; j++){
            if (((sourceStrText[i]).pointer)[j] != '\n'){
                if ( 3 < j && j < 11){
                    printf("('%c'<%d>)", ((sourceStrText[i]).pointer)[j], ((sourceStrText[i]).pointer)[j]);
                } else {
                    printf("%c", ((sourceStrText[i]).pointer)[j]);
                }
            }
        }
        printf("\n");
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

void ConvertPointersToStruct(char** arr, string* strArr, size_t size){
    for (int i = 0; i < size; i++){
        strArr[i].pointer = arr[i];
        strArr[i].length = arr[i + 1] - arr[i];
        printf("%lu ", strArr[i].length);
    }
}

int main(){

    const char* sourceFile = "onegin.txt";
    FILE* sourceFileLink = fopen(sourceFile, "r");
    size_t numLines = 0;

    struct stat st;
    stat(sourceFile, &st);
    size_t fileSize = st.st_size;

    printf("%lu\n", fileSize); // как узнать количество строк в файле?

    void* bufferPointer = calloc(fileSize, sizeof(char)); //выделение памяти для буфера

    ASSERT(sourceFileLink != NULL && bufferPointer != NULL);
    fread(bufferPointer, sizeof(char), fileSize, sourceFileLink); // чтение в буфер
    ((char*)bufferPointer)[fileSize] = -1; //фиксит countLines

    CountLines((char*)bufferPointer, &numLines); // счёт '\n'
    printf("%lu\n", numLines);

    char** originalTextPointer = (char**)calloc(numLines + 1, sizeof(char*)); // (char**)!=(сhar*)???



    SplitText((char*)bufferPointer, (char**)originalTextPointer); // разделение буфера по '\n'

    string* strSortedPointer = (string*)calloc(numLines + 1, sizeof(string));
    char** textSortedPointer = (char**)calloc(numLines + 1, sizeof(char*)); // отсортированные указатели
    CopyContent(originalTextPointer, textSortedPointer, numLines + 1);

    ConvertPointersToStruct(originalTextPointer, strSortedPointer, numLines);

    PrintOriginalText(strSortedPointer, numLines);
    BubbleSortStrings(strSortedPointer, numLines);
    PrintText(strSortedPointer, numLines);

    return 0;
}
