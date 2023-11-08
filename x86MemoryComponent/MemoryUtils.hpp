#ifndef X86_MEMORYUTILS_HPP
#define X86_MEMORYUTILS_HPP


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace MemoryUtils{


    std::vector<std::string> read_from_memory_input_file(const std::string& memory_input_file_name){
        std::ifstream instructions_file;
        std::string line;
        std::vector<std::string> instructions;
        instructions_file.open(memory_input_file_name, std::fstream::in);
        if (instructions_file.is_open()) {
            while (std::getline(instructions_file, line)){
                instructions.push_back(line);
            }
            instructions_file.close();
        }
        else {
            std::cout << "# Memory Utils # Error!: Unable to open memory input file";
        }
        return instructions;
    }


}

#endif