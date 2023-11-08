//
// Created by razvan on 9/29/23.
//

#include "Stack.hpp"

Stack::Stack() {
    stack_memory.reserve(MAX_STACK_SIZE);
}

void Stack::push(const uint16_t &value) {
    stack_memory.push_back(value);
}

uint16_t Stack::pop() {
    uint16_t value = stack_memory.back();
    stack_memory.pop_back();
    return value;
}
