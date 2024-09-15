#ifndef SORTING_HPP
#define SORTING_HPP

typedef int (*cmpfnc)(void*, void*);
void QuickSort(void* arr, size_t size, size_t sizeElem, cmpfnc CompareFunc);

#endif
