#ifndef X86_INSTRUCTIONMEMORY_HPP
#define X86_INSTRUCTIONMEMORY_HPP


#include <vector>
#include <cstdint>
#include <string>
#include <array>

class InstructionMemory {
public:
    InstructionMemory();
    std::vector<std::string> read_instruction_memory();
private:
    std::vector<std::string> instructions;
};

#endif