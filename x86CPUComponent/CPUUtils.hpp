#ifndef X86_CPUUTILS_HPP
#define X86_CPUUTILS_HPP

#include <string>

namespace CPUUtils{

    inline std::string convert_hex_to_bin(const char& hex_value){
        std::string bin_string;
        switch (hex_value) {

            case '0': bin_string = "0000"; break;

            case '1': bin_string = "0001"; break;

            case '2': bin_string = "0010"; break;

            case '3': bin_string = "0011"; break;

            case '4': bin_string = "0100"; break;

            case '5': bin_string = "0101"; break;

            case '6': bin_string = "0110"; break;

            case '7': bin_string = "0111"; break;

            case '8': bin_string = "1000"; break;

            case '9': bin_string = "1001"; break;

            case 'a': bin_string = "1010"; break;

            case 'b': bin_string = "1011"; break;

            case 'c': bin_string = "1100"; break;

            case 'd': bin_string = "1101"; break;

            case 'e': bin_string = "1110"; break;

            case 'f': bin_string = "1111"; break;

            default: break;

        }
        return bin_string;
    }

    inline std::string format_instruction_to_binary(std::string hex_string_value){
        std::string formatted_instruction;
        for (int i = 0; i < hex_string_value.size(); ++i)
            formatted_instruction.append(convert_hex_to_bin(hex_string_value[i]));
        return formatted_instruction;
    }

    inline uint16_t convert_hex_string_to_value(std::string hex_string){
        uint16_t temp_hex_value = 0;
        std::string bin_instruction = format_instruction_to_binary(hex_string);
        for (int i = 0; i < 16; ++i){
            if (bin_instruction.c_str()[16 - i - 1] == '1')
                temp_hex_value += (1 << i);

        }
        return temp_hex_value;
    }

    inline void split_bin_instruction(std::string instruction, std::string& op, std::string& p1, std::string& p2){
        int counter = 0;
        for(; counter < 6; counter++){
            op.push_back(instruction[counter]);
        }
        for (counter = 0; counter < 5; counter++){
            p1.push_back(instruction[6 + counter]);
            p2.push_back(instruction[11 + counter]);
        }
    }


}

#endif