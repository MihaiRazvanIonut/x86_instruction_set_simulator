
#include "Decode.hpp"

std::vector<std::string> Decode::decode_instruction(std::vector<std::string> complete_encoded_instruction) {
    bool is_param1_reg = false;
    std::vector<std::string> decoded_instruction;
    std::string bin_instruction = CPUUtils::format_instruction_to_binary(complete_encoded_instruction[0]);
    std::string operation_code;
    std::string parameter_1_code;
    std::string parameter_2_code;
    CPUUtils::split_bin_instruction(bin_instruction, operation_code, parameter_1_code, parameter_2_code);
    decoded_instruction.push_back(recognised_encodings.decode_operation(operation_code));
    if (recognised_encodings.decode_parameter(parameter_1_code) != "NULL") {
        if (parameter_1_code[0] == '1') {
            if (recognised_encodings.decode_parameter(parameter_1_code) == "IMM") {
                decoded_instruction.push_back(complete_encoded_instruction[1]);
            } else if (recognised_encodings.decode_parameter(parameter_1_code) == "ADDR") {
                decoded_instruction.push_back("[" + complete_encoded_instruction[1] + "]");
            } else {
                std::string bin_string = CPUUtils::format_instruction_to_binary(complete_encoded_instruction[1]);
                std::string trimmed_bin_string;
                for (int i = 11; i < 16; ++i)
                    trimmed_bin_string.push_back(bin_string[i]);
                decoded_instruction.push_back(
                        "[" + recognised_encodings.decode_parameter(trimmed_bin_string) + "]");
            }
        } else {
            decoded_instruction.push_back(recognised_encodings.decode_parameter(parameter_1_code));
            is_param1_reg = true;
        }
    }
    int index;
    if (is_param1_reg) index = 1;
    else index = 2;
    if (recognised_encodings.decode_parameter(parameter_1_code) != "NULL" and recognised_encodings.decode_parameter(parameter_2_code) != "NULL") {
        if (parameter_2_code[0] == '1') {
            if (recognised_encodings.decode_parameter(parameter_2_code) == "IMM") {
                decoded_instruction.push_back(complete_encoded_instruction[index]);
            } else if (recognised_encodings.decode_parameter(parameter_2_code) == "ADDR") {
                decoded_instruction.push_back("[" + complete_encoded_instruction[index] + "]");
            } else {
                std::string bin_string = CPUUtils::format_instruction_to_binary(complete_encoded_instruction[index]);
                std::string trimmed_bin_string;
                for (int i = 11; i < 16; ++i)
                    trimmed_bin_string.push_back(bin_string[i]);
                decoded_instruction.push_back(
                        "[" + recognised_encodings.decode_parameter(trimmed_bin_string) + "]");
            }
        } else {
            decoded_instruction.push_back(recognised_encodings.decode_parameter(parameter_2_code));
        }
    }
    return decoded_instruction;
}
