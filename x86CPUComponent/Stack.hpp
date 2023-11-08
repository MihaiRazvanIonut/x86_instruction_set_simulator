#ifndef X86_STACK_HPP
#define X86_STACK_HPP
#include <vector>
#include <cstdint>
#include "Registers.hpp"
class Stack {

public:

    Stack();
    void push(const uint16_t& value);
    uint16_t pop();
private:

    std::vector<uint16_t> stack_memory;
};


#endif //X86_STACK_HPP
