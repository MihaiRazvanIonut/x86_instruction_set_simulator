#ifndef X86_REGISTERS_HPP
#define X86_REGISTERS_HPP


#include <cstdint>
#include <unordered_map>
#include <string>
#define MAX_STACK_SIZE 256

struct Registers{
    std::unordered_map<std::string, uint16_t> internal_registers;
    std::unordered_map<std::string, uint16_t> config_registers;
    Registers(){
        internal_registers["R0"] = 0;
        internal_registers["R1"] = 0;
        internal_registers["R2"] = 0;
        internal_registers["R3"] = 0;
        internal_registers["R4"] = 0;
        internal_registers["R5"] = 0;
        internal_registers["R6"] = 0;
        internal_registers["R7"] = 0;
        internal_registers["FLAGS_ZERO"] = 0;
        internal_registers["FLAGS_EQUAL"] = 0;
        internal_registers["FLAGS_GREATER"] = 0;
        config_registers["STACK_BASE"] = 0xFFFC;
        config_registers["STACK_SIZE"] = MAX_STACK_SIZE;
        config_registers["SP"] = 0xFFFC;
    }
};

#endif