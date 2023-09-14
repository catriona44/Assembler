/* 
Given a line from an assembly code file, determine whether it is C-instruction, A-instruction or neither and split into consistuent parts
*/
#include "helpers.h"
#include <charconv>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Split
parser::parser(string_view line) {
    switch (line[0]) {
        // If first character is /, check if second character is also in which case this is a comment
        case '/':
            if (line[1] != '/') {
                cout << "Error, invalid instruction\n";
            }
            isinstr = false;
            break;
            
        // If first character is @ this is an a-instruction
        case '@':
            isinstr = true;
            isa = true;
            line.remove_prefix(1);
            from_chars(line.data(), line.data() + line.size(), value);
            break;
        // Otherwise it *should* be a C instruction
        default:   
            isinstr = true;
            isa = false;
            parse_cinstr(line);
            break;
        return;

        // TODO: error handling here - have assumed input file is error free
    } 
}

int parser::parse_cinstr(string_view line) {
    // Look for "=", the section before it is the dest, else dest is null
    int i{0};
    size_t len = line.size();
    for (; i < len; i++) {
        if (line[i] == '=' || line[i] == ';') {
            break;
        }     
    }
    if (line[i] == '=') {
        dest = line.substr(0, i);
        i++;
    } else {
        i = 0;
        dest = "null";
    }
    int j{i};
    // Section after "=" or at the start if dest = null is the calculation string, up to ';' or '/'
    for (; i < len; i++) {
        if (line[i] == ';' || line[i] == '/') {
            i;
            break;
        }
    }
    calc = line.substr(j, i);

    // Section after ";" is the jump condition
    jump = "null";
    if (i < len) {
        if (line[i] == ';') {
            jump = line.substr(i + 1, i + 4);
        }
    }
    return 0;
}
