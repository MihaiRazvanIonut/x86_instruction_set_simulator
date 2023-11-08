#ifndef X86_SIMULATION_HPP
#define X86_SIMULATION_HPP


#include "../x86ClockComponent/Clock.hpp"
#include "../x86MemoryComponent/Memory.hpp"
#include "Stack.hpp"
#include "Registers.hpp"
#include "LoadStore.hpp"
#include "InstructionCache.hpp"
#include "Decode.hpp"
#include "Execute.hpp"
#include <iostream>
#include <fstream>


#define MAX_INSTRUCTION_SIZE 1024


class Simulation {

public:
    Simulation();
    void run_simulation();
private:

    uint16_t IP;
    int IP_offset;
    bool need_fetch_window;
    Registers sim_registers;
    Clock sim_clock;
    Memory sim_memory;
    Stack sim_stack;
    LoadStore sim_load_store;
    InstructionCache sim_instruction_cache;
    Decode sim_decode;
    Execute sim_execute;
    bool sim_on;

};

#endif