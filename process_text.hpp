#pragma once

#include "structure_text.hpp"

int HasLetters              (string str);
int CharCompare             (char firstChar, char secondChar);
int StringCompare           (void* firstStringPointer, void* secondStringPointer);
int StringCompareReversed   (void* firstStringPointer, void* secondStringPointer);
void ProcessText            (structuredText textIn, const char* filenameOut);
