#include "Execute.hpp"


std::pair<uint16_t, uint16_t> Execute::execute_instruction(bool& sim_on, uint16_t& IP, Registers& read_write_access_registers, std::vector<std::string> instruction, std::array<uint16_t, 2> loaded_data, bool& store_flag, Stack stack_memory) {

    /**
     *
     *      Pair -> first store address, second store value
     *      In loaded data -> [0] is second loaded parameter
     *                        [1] is first loaded parameter
     *
     */

    std::pair<uint16_t, uint16_t> store_data;
    store_data.first = 0;
    store_data.second = 0;
    store_flag = false;
    if (instruction[0] == "ADD"){
        uint16_t first_add_parameter;
        uint16_t second_add_parameter;
        if (load_flags[0]){
            first_add_parameter = loaded_data[0];
            if (load_flags[1]){
                // 1 1
                second_add_parameter = loaded_data[1];
            } else {
                // 1 0
                if (instruction[2][0] == 'R'){
                    second_add_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_add_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }
        }else {
            if (instruction[1][0] == 'R'){
                first_add_parameter = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                first_add_parameter = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
            if (load_flags[1]){
                // 0 1
                second_add_parameter = loaded_data[0];
            } else {
                // 0 0
                if (instruction[2][0] == 'R'){
                    second_add_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_add_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }

        }

        store_data.second = first_add_parameter + second_add_parameter;

        if (store_data.second == 0) read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 1;
        else{
            read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 0;
        }
        if (instruction[1][0] == '['){
            store_flag = true;
            if (instruction[1][1] == 'R'){
                std::string store_register;
                store_register.push_back(instruction[1][1]);
                store_register.push_back(instruction[1][2]);
                store_data.first = read_write_access_registers.internal_registers.at(store_register);
            } else {
                std::string  store_address;
                for (int i = 1; i < instruction[1].length() - 1; ++i){
                    store_address.push_back(instruction[1][i]);
                }
                store_data.first = CPUUtils::convert_hex_string_to_value(store_address);
            }
        } else {
            read_write_access_registers.internal_registers.at(instruction[1]) = store_data.second;
        }

    }

    if (instruction[0] == "SUB"){
        uint16_t first_sub_parameter;
        uint16_t second_sub_parameter;
        if (load_flags[0]){
            first_sub_parameter = loaded_data[0];
            if (load_flags[1]){
                // 1 1
                second_sub_parameter = loaded_data[1];
            } else {
                // 1 0
                if (instruction[2][0] == 'R'){
                    second_sub_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_sub_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }
        }else {
            if (instruction[1][0] == 'R'){
                first_sub_parameter = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                first_sub_parameter = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
            if (load_flags[1]){
                // 0 1
                second_sub_parameter = loaded_data[0];
            } else {
                // 0 0
                if (instruction[2][0] == 'R'){
                    second_sub_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_sub_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }

        }

        store_data.second = first_sub_parameter - second_sub_parameter;

        if (store_data.second == 0) read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 1;
        else{
            read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 0;
        }

        if (instruction[1][0] == '['){
            store_flag = true;
            if (instruction[1][1] == 'R'){
                std::string store_register;
                store_register.push_back(instruction[1][1]);
                store_register.push_back(instruction[1][2]);
                store_data.first = read_write_access_registers.internal_registers.at(store_register);
            } else {
                std::string  store_address;
                for (int i = 1; i < instruction[1].length() - 1; ++i){
                    store_address.push_back(instruction[1][i]);
                }
                store_data.first = CPUUtils::convert_hex_string_to_value(store_address);
            }
        } else {
            read_write_access_registers.internal_registers.at(instruction[1]) = store_data.second;
        }

    }

    if (instruction[0] == "MOV"){
        uint16_t mov_value;
        if (load_flags[1]){
            mov_value = loaded_data[0];
        } else {
            if (instruction[2][0] == 'R'){
               mov_value = read_write_access_registers.internal_registers.at(instruction[2]);
            } else {
               mov_value = CPUUtils::convert_hex_string_to_value(instruction[2]);
            }
        }
        store_data.second = mov_value;
        if (instruction[1][0] == '['){
            store_flag = true;
            std::string pure_hex_string;
            for (int i = 1; i < instruction[1].length() - 1; ++i){
                pure_hex_string.push_back(instruction[1][i]);
            }
            store_data.first = CPUUtils::convert_hex_string_to_value(pure_hex_string);
        } else {
            read_write_access_registers.internal_registers.at(instruction[1]) = store_data.second;
        }
    }

    if (instruction[0] == "MUL"){
        uint32_t first_mul_parameter;
        uint32_t second_mul_parameter;
        if (load_flags[0]){
            first_mul_parameter = loaded_data[0];
            if (load_flags[1]){
                // 1 1
                second_mul_parameter = loaded_data[1];
            } else {
                // 1 0
                if (instruction[2][0] == 'R'){
                    second_mul_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_mul_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }
        }else {
            if (instruction[1][0] == 'R'){
                first_mul_parameter = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                first_mul_parameter = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
            if (load_flags[1]){
                // 0 1
                second_mul_parameter = loaded_data[0];
            } else {
                // 0 0
                if (instruction[2][0] == 'R'){
                    second_mul_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_mul_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }

        }
        uint32_t mul_result = first_mul_parameter * second_mul_parameter;
        if (mul_result == 0) read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 1;
        else{
            read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 0;
        }
        uint16_t R0_store_value = 0, R1_store_value = 0;
        std::string bin_mul_result;
        while (mul_result){
            if (mul_result % 2 == 0){
                bin_mul_result.push_back('0');
            } else {
                bin_mul_result.push_back('1');
            }
            mul_result /= 2;
        }
        std::reverse(bin_mul_result.begin(), bin_mul_result.end());
        while (bin_mul_result.length() < 32){
            bin_mul_result = "0" + bin_mul_result;
        }
        std::string first_half_bin_mul_result;
        std::string second_half_bin_mul_result;
        for (int i = 0; i < 16; ++i){
            first_half_bin_mul_result.push_back(bin_mul_result[i]);
            second_half_bin_mul_result.push_back(bin_mul_result[i + 16]);
        }
        for (int i = 0; i < 16; ++i){
            if (first_half_bin_mul_result.c_str()[16 - i - 1] == '1')
                R0_store_value += (1 << i);
            if (second_half_bin_mul_result.c_str()[16 - i - 1] == '1')
                R1_store_value += (1 << i);
        }
        read_write_access_registers.internal_registers.at("R0") = R0_store_value;
        read_write_access_registers.internal_registers.at("R1") = R1_store_value;
    }

    if (instruction[0] == "DIV"){
        uint16_t first_div_parameter;
        uint16_t second_div_parameter;
        if (load_flags[0]){
            first_div_parameter = loaded_data[0];
            if (load_flags[1]){
                // 1 1
                second_div_parameter = loaded_data[1];
            } else {
                // 1 0
                if (instruction[2][0] == 'R'){
                    second_div_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_div_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }
        }else {
            if (instruction[1][0] == 'R'){
                first_div_parameter = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                first_div_parameter = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
            if (load_flags[1]){
                // 0 1
                second_div_parameter = loaded_data[0];
            } else {
                // 0 0
                if (instruction[2][0] == 'R'){
                    second_div_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_div_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }

        }
        if (first_div_parameter == 0) read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 1;
        read_write_access_registers.internal_registers.at("R0") = first_div_parameter / second_div_parameter;
        read_write_access_registers.internal_registers.at("R1") = first_div_parameter % second_div_parameter;
    }

    if (instruction[0] == "CMP"){
        uint16_t first_cmp_parameter;
        uint16_t second_cmp_parameter;
        if (load_flags[0]){
            first_cmp_parameter = loaded_data[0];
            if (load_flags[1]){
                // 1 1
                second_cmp_parameter = loaded_data[1];
            } else {
                // 1 0
                if (instruction[2][0] == 'R'){
                    second_cmp_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_cmp_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }
        }else {
            if (instruction[1][0] == 'R'){
                first_cmp_parameter = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                first_cmp_parameter = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
            if (load_flags[1]){
                // 0 1
                second_cmp_parameter = loaded_data[0];
            } else {
                // 0 0
                if (instruction[2][0] == 'R'){
                    second_cmp_parameter = read_write_access_registers.internal_registers.at(instruction[2]);
                } else {
                    second_cmp_parameter = CPUUtils::convert_hex_string_to_value(instruction[2]);
                }
            }

        }

        read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 0;
        read_write_access_registers.internal_registers.at("FLAGS_EQUAL") = 0;
        read_write_access_registers.internal_registers.at("FLAGS_GREATER") = 0;

        if (first_cmp_parameter == second_cmp_parameter){
            read_write_access_registers.internal_registers.at("FLAGS_EQUAL") = 1;
            if (first_cmp_parameter == 0)
                read_write_access_registers.internal_registers.at("FLAGS_ZERO") = 1;
        } else if (first_cmp_parameter > second_cmp_parameter)
                read_write_access_registers.internal_registers.at("FLAGS_GREATER") = 1;

    }

    if (instruction[0] == "JMP"){
        IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
    }

    if (instruction[0] == "JE"){
        if (read_write_access_registers.internal_registers.at("FLAGS_EQUAL")){
            IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
        }
    }

    if (instruction[0] == "JL"){
        if (!read_write_access_registers.internal_registers.at("FLAGS_EQUAL") and !read_write_access_registers.internal_registers.at("FLAGS_GREATER")){
            IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
        }
    }

    if (instruction[0] == "JG"){
        if (read_write_access_registers.internal_registers.at("FLAGS_GREATER")){
            IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
        }
    }

    if (instruction[0] == "JZ"){
        if (read_write_access_registers.internal_registers.at("FLAGS_ZERO")){
            IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
        }
    }

    if (instruction[0] == "CALL"){
        stack_memory.push(IP);
        stack_memory.push(read_write_access_registers.internal_registers.at("FLAGS_ZERO"));
        stack_memory.push(read_write_access_registers.internal_registers.at("FLAGS_EQUAL"));
        stack_memory.push(read_write_access_registers.internal_registers.at("FLAGS_GREATER"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R0"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R1"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R2"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R3"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R4"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R5"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R6"));
        stack_memory.push(read_write_access_registers.internal_registers.at("R7"));
        IP = CPUUtils::convert_hex_string_to_value(instruction[1]);
    }

    if (instruction[0] == "RET"){
        for (int i = 0; i < 11; ++i)
            stack_memory.pop();
        IP = stack_memory.pop();
    }

    if (instruction[0] == "END_SIM"){
        sim_on = false;
    }

    if (instruction[0] == "PUSH"){
        uint16_t push_value;
        if (load_flags[0]){
            push_value = loaded_data[0];
        } else {
            if (instruction[1][0] == 'R'){
                push_value = read_write_access_registers.internal_registers.at(instruction[1]);
            } else {
                push_value = CPUUtils::convert_hex_string_to_value(instruction[1]);
            }
        }
        stack_memory.push(push_value);
    }

    if (instruction[0] == "POP"){
        stack_memory.pop();
    }
    return store_data;
}

void Execute::analyse_instruction_to_be_executed(Registers read_access_registers, std::vector<std::string> instruction, bool& jump_flag, std::vector<uint16_t>& load_addresses) {
    jump_flag = false;
    load_addresses.clear();
    load_flags[0] = false;
    load_flags[1] = false;
    if (instruction[0] == "JMP"){
        jump_flag = true;
    }
    if (instruction[0] == "JE" and read_access_registers.internal_registers.at("FLAGS_EQUAL") == 1){
       jump_flag = true;
    }
    if (instruction[0] == "JL" and read_access_registers.internal_registers.at("FLAGS_EQUAL") == 0 and read_access_registers.internal_registers.at("FLAGS_GREATER") == 0){
        jump_flag = true;
    }
    if (instruction[0] == "JG"  and read_access_registers.internal_registers.at("FLAGS_GREATER") == 1) {
        jump_flag = true;
    }
    if (instruction[0] == "JZ"  and read_access_registers.internal_registers.at("FLAGS_ZERO") == 1){
        jump_flag = true;
    }
    if (instruction[0] == "CALL"){
        jump_flag = true;
    }
    if (instruction[0] == "RET"){
        jump_flag = true;
    }
    if (instruction[0] == "PUSH" or instruction[0] == "MOV" or instruction[0] == "ADD" or instruction[0] == "SUB" or instruction[0] == "MUL" or instruction[0] == "DIV" or instruction[0] == "CMP"){
        if (instruction[0] != "MOV" and instruction[1][0] == '[') {
            load_flags[0] = true;
            if (instruction[1][1] == 'R'){
                std::string register_key;
                register_key.push_back(instruction[1][1]);
                register_key.push_back(instruction[1][2]);
                load_addresses.push_back(read_access_registers.internal_registers.at(register_key));
            }else{
                std::string pure_hex_string;
                for (int i = 1; i < instruction[1].length() - 1; ++i)
                    pure_hex_string.push_back(instruction[1][i]);
                load_addresses.push_back(CPUUtils::convert_hex_string_to_value(pure_hex_string));
            }
        }
        if (instruction[0] != "PUSH" and instruction[2][0] == '[') {
            load_flags[1] = true;
            if (instruction[2][1] == 'R'){
                std::string register_key;
                register_key.push_back(instruction[2][1]);
                register_key.push_back(instruction[2][2]);
                load_addresses.push_back(read_access_registers.internal_registers.at(register_key));
            }else{
                std::string pure_hex_string;
                for (int i = 1; i < instruction[2].length() - 1; ++i)
                    pure_hex_string.push_back(instruction[2][i]);
                load_addresses.push_back(CPUUtils::convert_hex_string_to_value(pure_hex_string));
            }
        }
    }

}
