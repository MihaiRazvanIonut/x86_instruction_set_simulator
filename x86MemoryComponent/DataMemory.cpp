#include "DataMemory.hpp"

void DataMemory::reset_data_memory() {
    for(int i = 0; i < MAX_MEM_SIZE; ++i){
        data_memory[i] = 0;
    }
}

void DataMemory::store(const uint16_t &value, const uint16_t &address) {
    data_memory[address] = value;
}

const uint16_t &DataMemory::load(const uint16_t &address) {
    return data_memory[address];
}

DataMemory::DataMemory() {
    for(int i = 0; i < MAX_MEM_SIZE; ++i){
        data_memory[i] = 0;
    }
}
