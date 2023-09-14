#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

void generate_symbol_table(ifstream &file);

class parser {
    public:
        parser(string_view line);
        // if not an instruction can be skipped
        bool isinstr{ false };
        // true if a instruction, false if c
        bool isa{ false };
        // store the number for an a-instruction
        int value{0};
        // store the sections of a c-instruction: destination, calculation, and jump condition
        string dest;
        string calc;
        string jump;
        int parse_cinstr(string_view line);

};

class Code {
private:
    unordered_map<string, string> calc_map{
        {"0", "101010"},
        {"1", "111111"},
        {"-1", "111010"},
        {"D", "001100"},
        {"A", "110000"},
        {"!D", "001101"},
        {"!A", "110001"},
        {"-D", "001111"},
        {"-A", "110011"},
        {"D+1", "011111"},
        {"A+1", "110111"},
        {"D-1", "001110"},
        {"A-1", "110010"},
        {"D+A", "000010"},
        {"D-A", "010011"},
        {"A-D", "000111"},
        {"D&A", "000000"},
        {"D|A", "010101"}
    };
    unordered_map<string, string> jump_map{
        {"null", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };


public:
    string generate_calc_code(string& calc);
    string generate_code(parser& instr);
    string generate_dest_code(string& dest);
    string generate_jump_code(string& jump);
    string inttobinstr(int n);
};







