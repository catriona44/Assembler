/* 
Given a parsed instruction, generate its machine code string
*/
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std; 

string Code::generate_code(parser &instr) {
    if (instr.isinstr == false) {
        // If it's a label, comment or whitespace, no machine code generated
        return "";
    }
    // For an A-instruction generate the machine code
    if (instr.isa == true) {
        // Convert the integer into a binary address and prepend the 0 to indicate an a-instruction
        return "0" + inttobinstr(instr.value) + "\n";
    } else {
        // For a C-instruction generate the machine code
        string code = "111";

        // Generate the calculation section of machine code
        code += generate_calc_code(instr.calc);

        // Generate the destination section of machine code
        code += generate_dest_code(instr.dest);

        // Generate the jump section of machine code
        code += generate_jump_code(instr.jump);

        // Generate full machine code for C-instruction
        return code + "\n";
    }
}

// Convert an integer between 0 and 2^15 - 1 inclusive to a 15 digit binary string
string Code::inttobinstr(int n) {
    string bin_str = "";
    for (int i{0}; i < 15; i++) {
        if (n % 2 == 1) {
            bin_str = "1" + bin_str;
            n = (n - 1) / 2;
        } else {
            bin_str = "0" + bin_str;
            n = n / 2;
        }
    }
    return bin_str;
}

string Code::generate_dest_code(string& dest) {
    bool A = false;
    bool M = false;
    bool D = false;
    size_t n = dest.length();
    for (int i = 0; i < n; i++) {
        switch (dest[i]) {
        case 'A':
            A = true;
            break;
        case 'M':
            M = true;
            break;
        case 'D':
            D = true;
            break;
        default:
            break;
        }
    }
    stringstream s;
    s << A << D << M;
    return s.str();
}

string Code::generate_calc_code(string& calc) {
    // Check whether the string contains M, if so, swap for A but set a-bit = 1, otherwise set a-bit = 0
    size_t loc = calc.find("M");
    if (loc == string::npos) {
        return "0" + calc_map.at(calc);
    }
    else {
        calc[loc] = 'A';
        return "1" + calc_map.at(calc);
    }
}

string Code::generate_jump_code(string& jump) {
    return jump_map.at(jump);
}
