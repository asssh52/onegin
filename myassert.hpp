#pragma once

#include <stdlib.h>

#define COLOR_RESET         "\x1b[0m"
#define COLOR_RED          "\x1b[31m"
#define COLOR_GREEN        "\x1b[0;32m"

#define ASSERT(x) if (!(x)) { printf(COLOR_RED "\nThe programm has been aborted.\n"\
                                               "Line %d of file %s, function %s.\n\n" COLOR_RESET,\
                                            __LINE__, __FILE__, __func__); abort();}

