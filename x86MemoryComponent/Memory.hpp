#ifndef X86_MEMORY_HPP
#define X86_MEMORY_HPP


#include "InstructionMemory.hpp"
#include "DataMemory.hpp"
class Memory {
public:

    InstructionMemory instruction_memory;
    DataMemory data_memory;
};

#endif