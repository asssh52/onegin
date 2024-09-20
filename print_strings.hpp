#pragma once

#include "structure_text.hpp"

void PrintTextOriginal  (string* sourceStrText, size_t numLines, FILE* outputLink);
void PrintTextDebug     (string* sourceStrText, size_t numLines, FILE* outputLink);
void PrintText          (string* sourceStrText, size_t numLines, FILE* outputLink);
void PrintIntro         (FILE* outputLink);
void PrintOutro         (FILE* outputLink);
