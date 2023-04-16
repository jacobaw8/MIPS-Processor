#pragma once

#include <iostream>
#include <stack>
#include <bitset>
#include <string>
#include <unordered_map>

using namespace std;

class Program
{

private:

    bool single_step_mode;

    bitset<8> *memory;
    int program_counter;
    int size;

    unordered_map<bitset<5>, string> register_names = {
        {00001, "$at"},
        {00010, "$v0"},
        {00011, "$v1"},
        {00100, "$a0"},
        {00101, "$a1"},
        {00110, "$a2"},
        {00111, "$a3"},
        {01000, "$t0"},
        {01001, "$t1"},
        {01010, "$t2"},
        {01011, "$t3"},
        {01100, "$t4"},
        {01101, "$t5"},
        {01110, "$t6"},
        {01111, "$t7"},
        {10000, "$s0"},
        {10001, "$s1"},
        {10010, "$s2"},
        {10011, "$s3"},
        {10100, "$s4"},
        {10101, "$s5"},
        {10110, "$s6"},
        {10111, "$s7"},
        {11000, "$t8"},
        {11001, "$t9"},
    };

    unordered_map<bitset<5>, bitset<5>> register_values = {
        {00001, 00000},
        {00010, 00000},
        {00011, 00000},
        {00100, 00000},
        {00101, 00000},
        {00110, 00000},
        {00111, 00000},
        {01000, 00000},
        {01001, 00000},
        {01010, 00000},
        {01011, 00000},
        {01100, 00000},
        {01101, 00000},
        {01110, 00000},
        {01111, 00000},
        {10000, 00000},
        {10001, 00000},
        {10010, 00000},
        {10011, 00000},
        {10100, 00000},
        {10101, 00000},
        {10110, 00000},
        {10111, 00000},
        {11000, 00000},
        {11001, 00000}
    };

    // the indices of alu_op_count are as follows (info on page 260 of textbook):
    //  [0] = add         (lw, sw, add)
    //  [1] = sub         (beq, sub)
    //  [2] = and         (and)
    //  [3] = or          (or)
    //  [4] = slt         (slt)
    int alu_op_count[5];

    int cycle_count;
    int mem_read_count;
    int mem_write_count;
    int instruction_count;

public:
    // constructor
    Program(int memory_size, bool step)
    {
        if(step){
            single_step_mode = 1;
        }else{
            single_step_mode = 0;
        }

        //initialize with 4 times the memory needed for instructions to make room for data...
        size = memory_size * 4;
        memory = new bitset<8>[size];

        program_counter = 0;

        // set all ALU operation counts to 0
        for (int i = 0; i < sizeof(alu_op_count); i++)
        {
            alu_op_count[i] = 0;
        }
    }
    // destructor
    ~Program() {}
    // load binary file into stack
    int load_memory(string);
    void print_stats(bitset<32>);
    void execute_program();
    void print_mem();

    int get_cycle_count() { return cycle_count; }
    int get_mem_read_count() { return mem_read_count; }
    int get_mem_write_count() { return mem_write_count; }
    int get_instruction_count() { return instruction_count; }
};
