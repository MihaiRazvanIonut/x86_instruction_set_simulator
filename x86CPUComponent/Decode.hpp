#ifndef X86_DECODE_HPP
#define X86_DECODE_HPP

#include "Encodings.hpp"
#include <vector>
#include <string>
#include "CPUUtils.hpp"

class Decode {

public:

    std::vector<std::string> decode_instruction(std::vector<std::string> complete_encoded_instruction);

private:

    Encodings recognised_encodings;

};

#endif