#include "InstructionMemory.hpp"
#include "MemoryUtils.hpp"


InstructionMemory::InstructionMemory() {
    /**
     * read from memory input file the instructions given by user
     */
    instructions = MemoryUtils::read_from_memory_input_file("memory_input.txt");
}

std::vector<std::string> InstructionMemory::read_instruction_memory() {
    return instructions;
}