#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

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

typedef struct string{
    char* pointer;
    size_t length;
} string;




int CharCompare(char firstChar, char secondChar){
    return tolower(firstChar) - tolower(secondChar);
}

int StringCompare(const char* firstString, const char* secondString){
    ASSERT(firstString != NULL && secondString != NULL);

    for (int i = 0, j = 0; i < STR_LENGTH; i++, j++){ // size избыточен?
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
            if (StringCompare((sourceStrText[second]).pointer, (sourceStrText[second + 1]).pointer) > 0){
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

void CopyContent(char** origin, char** output, size_t size){ //dont need
    ASSERT(origin != nullptr && output != nullptr)

    for (int i = 0; i < size; i++){
        output[i] = origin[i];
    }
}

void PrintText(string* sourceStrText, size_t numLines){
    ASSERT(sourceStrText != nullptr);

    for (int i = 0; i < numLines; i++){
        for (int j = 0; j < (sourceStrText[i]).length; j++){
            printf("%c", ((sourceStrText[i]).pointer)[j]);
        }
    }
}

void PrintTextDebug(const char** sourceText, size_t size){
    printf("%c", sourceText[0][0]);
    for (int i = 0; i < size; i++){
        for (int j = 1; sourceText[i][j] != '\n' && sourceText[i][j] != EOF; j++){
            if (0 <= j && j <= 50){
                printf("(<%c>'%d')", tolower(sourceText[i][j]), tolower(sourceText[i][j]));
            } else
            printf("%c", sourceText[i][j]);
        }
        printf("\n\n");
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

    PrintText(strSortedPointer, numLines);
    BubbleSortStrings(strSortedPointer, numLines);
    PrintText(strSortedPointer, numLines);


    /*//debug
    //printf("%d\n", StringCompare(textSortedPointer[12], textSortedPointer[13]));

    char * first =  "     ``My uncle -- high ideals inspire him;";
    char * second = "     \"When will the devil come for you?\"''";
    printf("%d", StringCompareDebug(textSortedPointer[0], textSortedPointer[13]));



    //debug*/
    return 0;
}
