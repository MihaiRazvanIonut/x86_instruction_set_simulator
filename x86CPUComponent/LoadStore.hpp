#ifndef X86_LOADSTORE_HPP
#define X86_LOADSTORE_HPP


#include "../x86MemoryComponent/Memory.hpp"
#include "CPUUtils.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include "../x86MemoryComponent/Memory.hpp"

class LoadStore {

public:

    std::vector<std::string> request_fetch_window(const uint16_t& IP_value, int IP_offset, const std::vector<std::string>& instruction_memory);

    void store_request(Memory& memory, const uint16_t& store_value, const uint16_t& store_address);
    const uint16_t& load_request(Memory& memory, const uint16_t& load_value);
};

#endif
