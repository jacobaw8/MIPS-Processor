#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>

#include "Program.h"

using namespace std;

int get_file_size(ifstream &in_file)
{
    in_file.seekg(0, std::ios::end);
    size_t file_length = in_file.tellg();
    in_file.seekg(0, std::ios::beg);

    return file_length;
}

void Program::print_stats(bitset<32> curr_instruction)
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    string text = "Current Stats";
    int text_length = text.length();
    width = w.ws_col * 3 / 4;
    int num_dashes = width - text_length - 2;
    int left_dashes = num_dashes / 2;
    int right_dashes = num_dashes - left_dashes;

    stringstream ss;
    for (int i = 0; i < left_dashes; i++)
    {
        if (i == 0)
        {
            ss << "|";
        }
        else
        {
            ss << "-";
        }
    }
    ss << " "
       << "Current Stats"
       << " ";
    for (int i = 0; i < right_dashes; i++)
    {
        if (i == right_dashes - 1)
        {
            ss << "|";
        }
        else
        {
            ss << "-";
        }
    }

    text = "Registers";
    text_length = text.length();
    width = w.ws_col * 1 / 4;
    num_dashes = width - text_length - 2;
    left_dashes = num_dashes / 2;
    right_dashes = num_dashes - left_dashes;

    for (int i = 0; i < left_dashes; i++)
    {
        ss << "-";
    }
    ss << " "
       << "Registers"
       << " ";
    for (int i = 0; i < right_dashes; i++)
    {
        if (i == right_dashes - 1)
        {
            ss << "|" << endl;
        }
        else
        {
            ss << "-";
        }
    }

    int spaces = 25;

    ss << "|" << setw(spaces) << right << "PC : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << program_counter << right << "|" << setw(8) << right << "$at : " << left << register_values[00001] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "Current Instruction : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << curr_instruction << right << "|" << setw(8) << right << "$v0 : " << left << register_values[00010] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "# of cycles : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << cycle_count << right << "|" << setw(8) << right << "$v1 : " << left << register_values[00011] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "# of instructions : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << instruction_count << right << "|" << setw(8) << right << "$a0 : " << left << register_values[00100] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "# of memory reads : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << mem_read_count << right << "|" << setw(8) << right << "$a1 : " << left << register_values[00101] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "# of memory writes : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << mem_write_count << right << "|" << setw(8) << right << "$a2 : " << left << register_values[00110] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;

    text = "ALU Operations";
    text_length = text.length();
    width = w.ws_col * 3 / 4;
    num_dashes = width - text_length - 2;
    left_dashes = num_dashes / 2;
    right_dashes = num_dashes - left_dashes;

    for (int i = 0; i < left_dashes; i++)
    {
        if (i == 0)
        {
            ss << "|";
        }
        else
        {
            ss << "-";
        }
    }
    ss << " "
       << "ALU Operations"
       << " ";
    for (int i = 0; i < right_dashes; i++)
    {
        if (i == right_dashes - 1)
        {
            ss << "|" << setw(8) << right << "$a3 : " << left << register_values[00111] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
        }
        else
        {
            ss << "-";
        }
    }

    ss << "|" << setw(spaces) << right << "add : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << alu_op_count[0] << right << "|" << setw(8) << right << "$t0 : " << left << register_values[01000] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "sub : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << alu_op_count[1] << right << "|" << setw(8) << right << "$t1 : " << left << register_values[01001] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "and : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << alu_op_count[2] << right << "|" << setw(8) << right << "$t2 : " << left << register_values[01010] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "or : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << alu_op_count[3] << right << "|" << setw(8) << right << "$t3 : " << left << register_values[01011] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << "slt : " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << alu_op_count[4] << right << "|" << setw(8) << right << "$t4 : " << left << register_values[01100] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;

    for (int i = 0; i < num_dashes + text_length + 2; i++)
    {
        if (i == 0)
        {
            ss << "|";
        }
        else if (i == num_dashes + text_length + 2 - 1)
        {
            ss << "|" << setw(8) << right << "$t5 : " << left << register_values[01101] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
        }
        else
        {
            ss << "-";
        }
    }

    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$t6 : " << left << register_values[01110] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$t7 : " << left << register_values[01111] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s0 : " << left << register_values[10000] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s1 : " << left << register_values[10001] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s2 : " << left << register_values[10010] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s3 : " << left << register_values[10011] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s4 : " << left << register_values[10100] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s5 : " << left << register_values[10101] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s6 : " << left << register_values[10110] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$s7 : " << left << register_values[10111] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$t8 : " << left << register_values[11000] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;
    ss << "|" << setw(spaces) << right << " " << setw((w.ws_col * 3 / 4) - spaces - 2) << left << " " << right << "|" << setw(8) << right << "$t9 : " << left << register_values[11001] << setw((w.ws_col * 1 / 4) - 13) << right << "|" << endl;

    for (int i = 0; i < w.ws_col; i++)
    {
        if (i == 0)
        {
            ss << "|";
        }
        else if (i == num_dashes + text_length + 2 - 1)
        {
            ss << "|";
        }
        else if (i == w.ws_col - 2)
        {
            ss << "|";
            break;
        }
        else
        {
            ss << "-";
        }
    }

    cout << ss.str() << endl;

    if (single_step_mode)
    {
        cout << "\033[1A";
    }

    cout << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A"
         << "\033[1A";
}

int Program::load_memory(string file_name)
{

    ifstream in_file(file_name, ios::binary);

    if (in_file)
    {
        int temp_address = 0;
        while (!in_file.eof() && temp_address < size)
        {
            char buffer;
            in_file.read(&buffer, 1);

            bitset<8> instruction(buffer);

            memory[temp_address] = instruction;

            temp_address++;
        }
        in_file.close();
    }
    else
    {
        cerr << "Problem opening binary file" << endl;
    }

    return 1;
}

void Program::execute_program()
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    string title = "MIPS Processor: Normal Mode";
    if (single_step_mode)
    {
        title = "MIPS Processor: Single Step Mode (press enter to step)";
    }

    int title_length = title.length();
    width = w.ws_col;
    int num_spaces = (width - title_length) / 2;
    cout << endl
         << setw(num_spaces) << right << " "
         << "\033[1;36m" << title << "\033[0m" << endl;

    while (program_counter + 4 <= size)
    {
        if (single_step_mode)
        {
            getchar();
        }

        bitset<32> curr_instruction = memory[program_counter].to_ulong() << 24 | memory[program_counter + 1].to_ulong() << 16 | memory[program_counter + 2].to_ulong() << 8 | memory[program_counter + 3].to_ulong();

        print_stats(curr_instruction);

        bitset<6> opcode = (curr_instruction.to_ulong() >> 26) & 0x3F;

        if (opcode.to_string() == "000000")
        {
            // add, sub, or, and, slt
            bitset<5> rd = (curr_instruction.to_ulong() >> 21) & 0x1F;
            bitset<5> rs = (curr_instruction.to_ulong() >> 16) & 0x1F;
            bitset<5> rt = (curr_instruction.to_ulong() >> 11) & 0x1F;
            // bitset<5> shamt = (curr_instruction.to_ulong() >> 6) & 0x1F; shamt is never used by these instructions
            bitset<6> funct = curr_instruction.to_ulong() & 0x3F;

            // cout << 1 << endl;
            // cout << opcode << rd << rs << rt << shamt << funct << endl;

            // R-type instructions always take registers, so no need to check for constants.
            bitset<5> rs_val = register_values[rs];
            bitset<5> rt_val = register_values[rt];

            if (funct.to_string() == "100000")
            {
                // add
                // store rs + rt in rd
                register_values[rd] = rs_val.to_ulong() + rt_val.to_ulong();

                // update the ALU count for add
                alu_op_count[0] += 1;
                cycle_count++;
                instruction_count++;
            }
            else if (funct.to_string() == "100010")
            {
                // sub
                // store rs - rt in rd
                register_values[rd] = rs_val.to_ulong() - rt_val.to_ulong();

                // update the ALU count for add
                alu_op_count[1] += 1;
                cycle_count++;
                instruction_count++;
            }
            else if (funct.to_string() == "100100")
            {
                // and
                // store rs & rt in rd
                register_values[rd] = rs_val & rt_val;

                // update the ALU count for and
                alu_op_count[2] += 1;
                cycle_count++;
                instruction_count++;
            }
            else if (funct.to_string() == "100101")
            {
                // or
                // store rs | rt in rd
                register_values[rd] = rs_val | rt_val;

                // update the ALU count for or
                alu_op_count[3] += 1;
                cycle_count++;
                instruction_count++;
            }
            else if (funct.to_string() == "101010")
            {
                // slt
                if (rs_val.to_ulong() < rt_val.to_ulong())
                {
                    // if rs < rt, set rd to 1
                    register_values[rd] = bitset<5>("00001");
                }
                else
                {
                    // else set rd to 0
                    register_values[rd] = bitset<5>("00000");
                }

                // update the ALU count for slt
                alu_op_count[4] += 1;
                cycle_count++;
                instruction_count++;
            }
            else
            {
                cerr << "ERROR: Invalid R-Type funct: " << funct << endl;
            }
        }

        else if (opcode.to_string() == "100011")
        {
            // lw
            bitset<5> rs = (curr_instruction.to_ulong() >> 21) & 0x1F;
            bitset<5> rt = (curr_instruction.to_ulong() >> 16) & 0x1F;
            bitset<16> addr = (curr_instruction.to_ulong() & 0xFFFF);

            int memory_address = register_values[rs].to_ulong() + addr.to_ulong();

            bitset<8>(register_values[rt].to_ulong()) = memory[memory_address];

            // add to memory read
            mem_read_count++;
            alu_op_count[0]++;
            cycle_count++;
            instruction_count++;
        }

        else if (opcode.to_string() == "101011")
        {
            // sw
            bitset<5> rs = (curr_instruction.to_ulong() >> 21) & 0x1F;
            bitset<5> rt = (curr_instruction.to_ulong() >> 16) & 0x1F;
            bitset<16> addr = (curr_instruction.to_ulong() & 0xFFFF);

            int memory_address = register_values[rs].to_ulong() + addr.to_ulong();

            memory[memory_address] = bitset<8>(register_values[rt].to_ulong());

            // add to memory write
            mem_write_count++;
            alu_op_count[0]++;
            cycle_count++;
            instruction_count++;
        }

        else if (opcode.to_string() == "000100")
        {
            // beq
            bitset<5> rs = (curr_instruction.to_ulong() >> 21) & 0x1F;
            bitset<5> rt = (curr_instruction.to_ulong() >> 16) & 0x1F;
            bitset<16> addr = (curr_instruction.to_ulong() & 0xFFFF);

            alu_op_count[1]++;
            cycle_count++;
            instruction_count++;

            if (register_values[rs] == register_values[rt])
            {
                cout << endl;
                program_counter += (addr.to_ulong() * 4) + 4;
                continue;
            }
        }

        else if (opcode.to_string() == "000010")
        {
            // j
            bitset<26> loc = curr_instruction.to_ulong() & 0x03FFFFFF;

            cycle_count++;
            instruction_count++;
            cout << endl;

            program_counter = loc.to_ulong() * 4;

            continue;
        }
        else
        {
            cerr << "Invalid opcode" << endl;
        }
        cout << endl;
        program_counter += 4;
    }
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
}

void Program::print_mem()
{
    bitset<32> curr_word;
    for (int i = 0; i < size; i += 4)
    {
        curr_word = memory[i].to_ulong() << 24 | memory[i + 1].to_ulong() << 16 | memory[i + 2].to_ulong() << 8 | memory[i + 3].to_ulong();

        cout << "memory[" << i << "] to memory[" << i + 3 << "]: " << curr_word << endl;
    }
}

int main(int argc, char *argv[])
{
    bool single_step_mode = 0;

    if (argc != 2 && argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <INPUT FILE> <OPTIONAL FLAG>" << endl;
        return 0;
    }

    if (argc == 3)
    {
        string flag = argv[2];
        if (flag != "-s")
        {
            cerr << "Invalid flag" << endl;
            return 0;
        }else{
            single_step_mode = 1;
        }
    }

    string file_name = argv[1];

    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    ifstream in_file(file_name, ios::binary);

    // if the file opens...
    if (in_file)
    {
        int temp_size = get_file_size(in_file);
        in_file.close();

        // if the file is not empty...
        if (temp_size > 0)
        {
            Program newProg(temp_size, single_step_mode);

            if (newProg.load_memory("in.bin") != 1)
            {
                cerr << "Loading binary file failed.";
                return 0;
            }
            else
            {
                newProg.execute_program();
                // newProg.print_mem();
            }
        }
        else
        {
            cerr << "Binary file empty" << endl;
            return 0;
        }
    }
    else
    {
        // failed to open the file
        cerr << "Failed to open file" << endl;
        return 0;
    }

    return 1;
}
