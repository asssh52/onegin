#include <stdio.h>
#include "process_text.hpp"
#include "structure_text.hpp"
#include "myassert.hpp"



int main(int argc, const char* argv[]){
    const char* filenameIn  = (argc == 2)? argv[1] : "in_onegin.txt";
    const char* filenameOut = (argc == 3)? argv[2] : "out_onegin.txt";

    structuredText onegin = StructureText(filenameIn);
    ProcessText(onegin, filenameOut);

    structuredText hamlet = StructureText("in_hamlet.txt");
    ProcessText(hamlet, "out_hamlet.txt");

    FreeAndClose(onegin);
    FreeAndClose(hamlet);
    return 0;
}
