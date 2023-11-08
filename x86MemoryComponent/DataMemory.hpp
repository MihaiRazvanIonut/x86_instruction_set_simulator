#ifndef X86_DATAMEMORY_HPP
#define X86_DATAMEMORY_HPP


#include <cstdint>
#include <array>

#define MAX_MEM_SIZE 0xFFFF

class DataMemory {
public:
    DataMemory();
    void reset_data_memory();
    void store(const uint16_t& value, const uint16_t& address);
    const uint16_t& load(const uint16_t& address);
private:
    std::array<uint16_t, MAX_MEM_SIZE> data_memory{};
};

#endif