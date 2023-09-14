/*
Translates Hack assembly programs into executable Hack binary code
The source program is supplied in a text file named Xxx.asm
The generated code is written into a text file named Xxx.hack
*/
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    // TODO: Initialise symbol table and add pre defined symbols

    // TODO: Check for correct command line argument

    // Open input file for reading
    ifstream assembly_file(argv[1]);

    // TODO: First pass: count instruction numbers while adding labels to symbol table
        
    // TODO: Second pass: add variable symbols from a-instructions to symbol table

    
    string line; 
    // Open output file for writing
    int i = 0;

    // Setup name for the out file as the same as infile but .asm swapped for out.txt
    while (argv[1][i] != '\0') {
        i++;
    }
    char* outfilename;
    if (i > 4) {
        outfilename = (char*)malloc(sizeof(char) * (i + 5));
        for (int j = 0; j < i - 4; j++) {
            outfilename[j] = argv[1][j];
        }
        char* ptr = (outfilename + i - 4);
        strcpy_s(ptr, 9, "out.hack");
    }
    else {
        outfilename = (char*)malloc(7 * sizeof(char));
        strcpy_s(outfilename, 6, "a.hack");
    }
    ofstream output(outfilename);
    free(outfilename);
    Code code;
    string code_str;
    while (getline(assembly_file >> ws, line)) {
        // Parse the command
        parser instr(line);
        // Generate the machine code for an instruction 
        code_str = code.generate_code(instr);
        // Write the code to the output file
        output << code_str;
    }  
    output.close();
}
