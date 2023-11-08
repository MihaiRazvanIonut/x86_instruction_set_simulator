#ifndef X86_EXECUTE_HPP
#define X86_EXECUTE_HPP

#include <vector>
#include <array>
#include <string>
#include "Registers.hpp"
#include <tuple>
#include "CPUUtils.hpp"
#include "Stack.hpp"
#include <algorithm>

class Execute {
public:
    void analyse_instruction_to_be_executed(Registers read_access_registers, std::vector<std::string> instruction, bool& jump_flag, std::vector<uint16_t>& load_addresses);
    std::pair<uint16_t, uint16_t> execute_instruction(bool& end_sim, uint16_t& IP, Registers& read_write_access_registers, std::vector<std::string> instruction, std::array<uint16_t, 2> loaded_data, bool& store_flag, Stack stack_memory);

private:
    std::array<bool, 2> load_flags = {false, false};

};


#endif
