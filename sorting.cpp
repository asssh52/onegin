#include <stdio.h>
#include <stdlib.h>
#include "sorting.hpp"
#include "myassert.hpp"

void SwapItems(void* first, void* second, size_t sizeElem){
    ASSERT(first != nullptr && second != nullptr);
    
    for (int i = 0; i < sizeElem; i++){
        char temp = *((char*)first + i);
                    *((char*)first + i) = *((char*)second + i);
                                          *((char*)second + i) = temp;
    }
}

int Partiation(void* arr, size_t size, size_t sizeElem, cmpfnc CompareFunc){
    ASSERT(arr != nullptr);

    void* pivo = (char*)arr + (size - 1) * sizeElem;
    int firstPointer = -1;

    for (int secondPointer = 0; secondPointer < size; secondPointer++){
        if (CompareFunc(pivo, (char*)arr + secondPointer * sizeElem) == 1){
            firstPointer++;
            SwapItems((char*)arr + sizeElem * firstPointer, (char*)arr + sizeElem * secondPointer, sizeElem);
        }
    }

    SwapItems((char*)arr + sizeElem * (firstPointer + 1), pivo, sizeElem);
    return firstPointer + 1;
}

void QuickSort(void* arr, size_t size, size_t sizeElem, cmpfnc CompareFunc){
    if (size > 1){
        int pivoIndex = Partiation(arr, size, sizeElem, CompareFunc);
        QuickSort(arr, pivoIndex, sizeElem, CompareFunc);
        QuickSort((char*)arr + (1 + pivoIndex)* sizeElem, size - 1 - pivoIndex, sizeElem, CompareFunc);
    }
}
