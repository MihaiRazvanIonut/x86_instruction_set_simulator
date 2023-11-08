#include "Simulation.hpp"


void Simulation::run_simulation() {
    int clock_cycles = 0;

    std::vector<std::string> instructions_done;
    int instruction_needs[MAX_INSTRUCTION_SIZE][6];
/**
 *
 *  instruction_needs[i] [0] instruction i needs FW \n
 *  instruction_needs[i] [1] instruction i needs IC \n
 *  instruction_needs[i] [2] instruction i needs DE \n
 *  instruction_needs[i] [3] instruction i needs Load (value can be 0, 1, 2 depending on how many loads the instruction needs) \n
 *  instruction_needs[i] [4] instruction i needs EX \n
 *  instruction_needs[i] [5] instruction i needs Store \n
 *
 */
    for (int i = 0; i < MAX_INSTRUCTION_SIZE; ++i)
        for (int j = 0; j < 6; ++j)
            instruction_needs[i][j] = 0;
    int instruction_needs_counter = 0;
    while (sim_on){
        bool jump_flag = false;
        bool store_flag = false;
        std::vector<uint16_t> load_addresses;
        need_fetch_window = sim_instruction_cache.check_if_need_fetch_window();
        if (need_fetch_window){
            instruction_needs[instruction_needs_counter][0] = 1;
            clock_cycles += 15;
            auto fetch_window = sim_load_store.request_fetch_window(IP, IP_offset, sim_memory.instruction_memory.read_instruction_memory());
            sim_instruction_cache.fetch_window_instruction_caching(fetch_window);
            IP_offset+=4;
        }

        instruction_needs[instruction_needs_counter][1] = 1;
        clock_cycles += 3;
        auto encoded_instruction = sim_instruction_cache.fetch_instruction();


        instruction_needs[instruction_needs_counter][2] = 1;
        clock_cycles += 2;
        auto decoded_instruction = sim_decode.decode_instruction(encoded_instruction);

        sim_execute.analyse_instruction_to_be_executed(sim_registers, decoded_instruction,  jump_flag, load_addresses);
        if (jump_flag == 1) {
            sim_instruction_cache.clear_instruction_cache();
            IP_offset = 1;
        }
        std::array<uint16_t, 2> loaded_data = {0, 0};
        if (!load_addresses.empty()){
            instruction_needs[instruction_needs_counter][3] = 1;
            clock_cycles += 15;
            loaded_data[0] = sim_load_store.load_request(sim_memory, load_addresses[0]);
            if (load_addresses.size() == 2){
                instruction_needs[instruction_needs_counter][3] = 2;
                clock_cycles += 15;
                loaded_data[1] = sim_load_store.load_request(sim_memory, load_addresses[1]);
            }
        }
        instruction_needs[instruction_needs_counter][4] = 1;
        clock_cycles += 5;
        std::pair<uint16_t, uint16_t> store_data = sim_execute.execute_instruction(sim_on, IP, sim_registers, decoded_instruction,
                                                                                   loaded_data, store_flag, sim_stack);
        if (store_flag){
            instruction_needs[instruction_needs_counter][5] = 1;
            clock_cycles += 15;
            sim_load_store.store_request(sim_memory, store_data.second, store_data.first);
        }
        instruction_needs_counter++;
        std::string easy_to_read_instruction_format;
        for (const auto& item : decoded_instruction){
            easy_to_read_instruction_format.append(item);
            easy_to_read_instruction_format.push_back(' ');
        }
        instructions_done.push_back(easy_to_read_instruction_format);
    }
    std::ofstream output_file("parallel_output.txt");
    output_file << "Sequential execution of instructions took: " << clock_cycles << " clock cycles to complete\n\n";
    bool pipelined_execution_simulation_on = true;


    std::vector<std::string> clock_line_to_print;
    clock_line_to_print.emplace_back("Clock Cycles      |");
    std::vector<std::string> ls_line_to_print;
    ls_line_to_print.emplace_back   ("Load Store        |");
    std::vector<std::string> ic_line_to_print;
    ic_line_to_print.emplace_back   ("Instruction Cache |");
    std::vector<std::string> de_line_to_print;
    de_line_to_print.emplace_back   ("Decode            |");
    std::vector<std::string> ex_line_to_print;
    ex_line_to_print.emplace_back   ("Execute           |");

    /**
     *  until_when_are_components_occupied[0]   LS \n
     *  until_when_are_components_occupied[1]   IC \n
     *  until_when_are_components_occupied[2]   DE \n
     *  until_when_are_components_occupied[3]   EX \n
     */

    int until_when_are_components_occupied[4] = {0, 0, 0, 0};
    int what_instruction_occupies_components[4] = {0, 0, 0, 0};
    bool is_ic_finished = false;
    bool is_ls_finished = false;
    bool is_de_finished = false;
    bool is_ex_finished = false;
    bool what_type_of_ls_is_occupied[3] = {false, false, false};
    while (pipelined_execution_simulation_on){
        is_ls_finished = false;
        is_ic_finished = false;
        is_de_finished = false;
        is_ex_finished = false;
        pipelined_execution_simulation_on = false;
        clock_line_to_print.push_back(sim_clock.show_clock_in_string_type());
        if (until_when_are_components_occupied[0] == 0){
            int fw_pos = MAX_INSTRUCTION_SIZE, l_pos = MAX_INSTRUCTION_SIZE, s_pos = MAX_INSTRUCTION_SIZE;
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 1){
                    fw_pos = i;
                    break;
                }
            }
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 0 and instruction_needs[i][1] == 0 and instruction_needs[i][2] == 0 and instruction_needs[i][3] == 1){
                    int j;
                    for (j = 0; j < i; ++j){
                        if (instruction_needs[i][0] == 1 or instruction_needs[i][1] == 1 or instruction_needs[i][2] == 1) break;
                    }
                    if (j == i){
                        l_pos = i;
                    } else {
                        break;
                    }
                }
            }
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 0 and instruction_needs[i][1] == 0 and instruction_needs[i][2] == 0 and instruction_needs[i][3] == 0 and instruction_needs[i][4] == 0 and instruction_needs[i][5] == 1){
                    int j;
                    for (j = 0; j < i; ++j){
                        if (instruction_needs[i][0] == 1 or instruction_needs[i][1] == 1 or instruction_needs[i][2] == 1 or instruction_needs[i][3] != 0 or instruction_needs[i][4] == 1) break;
                    }
                    if (j == i){
                        s_pos = i;
                    } else {
                        break;
                    }
                }
            }
            if (fw_pos < l_pos and fw_pos < s_pos){
                until_when_are_components_occupied[0] = sim_clock.show_clock() + 14;
                what_instruction_occupies_components[0] = fw_pos;
                what_type_of_ls_is_occupied[0] = true;
                what_type_of_ls_is_occupied[1] = false;
                what_type_of_ls_is_occupied[2] = false;
                pipelined_execution_simulation_on = true;
            }
            if (l_pos < fw_pos and l_pos < s_pos){
                until_when_are_components_occupied[0] = sim_clock.show_clock() + (instruction_needs[l_pos][3] * 15) -1;
                what_instruction_occupies_components[0] = l_pos;
                what_type_of_ls_is_occupied[0] = false;
                what_type_of_ls_is_occupied[1] = true;
                what_type_of_ls_is_occupied[2] = false;
                pipelined_execution_simulation_on = true;
            }
            if (s_pos < fw_pos and s_pos < l_pos){
                until_when_are_components_occupied[0] = sim_clock.show_clock() + 14;
                what_instruction_occupies_components[0] = s_pos;
                what_type_of_ls_is_occupied[0] = false;
                what_type_of_ls_is_occupied[1] = false;
                what_type_of_ls_is_occupied[2] = true;
                pipelined_execution_simulation_on = true;
            }
        } else {
            pipelined_execution_simulation_on = true;
            if (sim_clock.show_clock() == until_when_are_components_occupied[0]){
                is_ls_finished = true;
            }
        }

        if (until_when_are_components_occupied[1] == 0) {
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 0 and instruction_needs[i][1] == 1){
                    int j;
                    for (j = 0; j < i; ++j){
                        if (instruction_needs[j][0] == 1) break;
                    }
                    if (j == i){
                        until_when_are_components_occupied[1] = sim_clock.show_clock() + 2;
                        what_instruction_occupies_components[1] = i;
                        pipelined_execution_simulation_on = true;
                    } else {
                        break;
                    }
                }
            }
        } else {
            pipelined_execution_simulation_on = true;
            if (sim_clock.show_clock() == until_when_are_components_occupied[1]){
                is_ic_finished = true;
            }
        }

        if (until_when_are_components_occupied[2] == 0) {
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 0 and instruction_needs[i][1] == 0 and instruction_needs[i][2] == 1){
                    int j;
                    for (j = 0; j < i; ++j){
                        if (instruction_needs[j][0] == 1 or instruction_needs[j][1] == 1) break;
                    }
                    if (j == i){
                        until_when_are_components_occupied[2] = sim_clock.show_clock() + 1;
                        what_instruction_occupies_components[2] = i;
                        pipelined_execution_simulation_on = true;
                    } else {
                        break;
                    }
                }
            }
        } else {
            pipelined_execution_simulation_on = true;
            if (sim_clock.show_clock() == until_when_are_components_occupied[2]){
                is_de_finished = true;
            }
        }

        if (until_when_are_components_occupied[3] == 0) {
            for (int i = 0; i < instruction_needs_counter; ++i){
                if (instruction_needs[i][0] == 0 and instruction_needs[i][1] == 0 and instruction_needs[i][2] == 0 and instruction_needs[i][3] == 0 and instruction_needs[i][4] == 1){
                    int j;
                    for (j = 0; j < i; ++j){
                        if (instruction_needs[j][0] == 1 or instruction_needs[j][1] == 1 or instruction_needs[i][2] == 1 or instruction_needs[i][3] != 0) break;
                    }
                    if (j == i){
                        until_when_are_components_occupied[3] = sim_clock.show_clock() + 4;
                        what_instruction_occupies_components[3] = i;
                        pipelined_execution_simulation_on = true;
                    } else {
                        break;
                    }
                }
            }
        } else {
            pipelined_execution_simulation_on = true;
            if (sim_clock.show_clock() == until_when_are_components_occupied[3]){
                is_ex_finished = true;
            }
        }
        if (until_when_are_components_occupied[0] == 0){
            ls_line_to_print.emplace_back("                    |");
        } else {
            auto len_of_instruction_string = instructions_done[what_instruction_occupies_components[0]].length();
            std::string instruction_print_string = instructions_done[what_instruction_occupies_components[0]];
            while (len_of_instruction_string < 20){
                instruction_print_string.push_back(' ');
                len_of_instruction_string++;
            }
            instruction_print_string.push_back('|');
            ls_line_to_print.push_back(instruction_print_string);
        }
        if (until_when_are_components_occupied[1] == 0){
            ic_line_to_print.emplace_back("                    |");
        } else {
            auto len_of_instruction_string = instructions_done[what_instruction_occupies_components[1]].length();
            std::string instruction_print_string = instructions_done[what_instruction_occupies_components[1]];
            while (len_of_instruction_string < 20){
                instruction_print_string.push_back(' ');
                len_of_instruction_string++;
            }
            instruction_print_string.push_back('|');
            ic_line_to_print.push_back(instruction_print_string);
        }
        if (until_when_are_components_occupied[2] == 0){
            de_line_to_print.emplace_back("                    |");
        } else {
            auto len_of_instruction_string = instructions_done[what_instruction_occupies_components[2]].length();
            std::string instruction_print_string = instructions_done[what_instruction_occupies_components[2]];
            while (len_of_instruction_string < 20){
                instruction_print_string.push_back(' ');
                len_of_instruction_string++;
            }
            instruction_print_string.push_back('|');
            de_line_to_print.push_back(instruction_print_string);
        }
        if (until_when_are_components_occupied[3] == 0){
            ex_line_to_print.emplace_back("                    |");
        } else {
            auto len_of_instruction_string = instructions_done[what_instruction_occupies_components[3]].length();
            std::string instruction_print_string = instructions_done[what_instruction_occupies_components[3]];
            while (len_of_instruction_string < 20){
                instruction_print_string.push_back(' ');
                len_of_instruction_string++;
            }
            instruction_print_string.push_back('|');
            ex_line_to_print.push_back(instruction_print_string);
        }
        if (is_ls_finished){
            until_when_are_components_occupied[0] = 0;
            if (what_type_of_ls_is_occupied[0])
                instruction_needs[what_instruction_occupies_components[0]][0] = 0;
            if (what_type_of_ls_is_occupied[1])
                instruction_needs[what_instruction_occupies_components[0]][3] = 0;
            if (what_type_of_ls_is_occupied[2])
                instruction_needs[what_instruction_occupies_components[0]][5] = 0;
            for (int i = 0; i < 3; ++i)
                what_type_of_ls_is_occupied[i] = false;
            what_instruction_occupies_components[0] = 0;
        }
        if (is_ic_finished){
            until_when_are_components_occupied[1] = 0;
            instruction_needs[what_instruction_occupies_components[1]][1] = 0;
            what_instruction_occupies_components[1] = 0;
        }
        if (is_de_finished){
            until_when_are_components_occupied[2] = 0;
            instruction_needs[what_instruction_occupies_components[2]][2] = 0;
            what_instruction_occupies_components[2] = 0;
        }
        if (is_ex_finished){
            until_when_are_components_occupied[3] = 0;
            instruction_needs[what_instruction_occupies_components[3]][4] = 0;
            what_instruction_occupies_components[3] = 0;
        }

        sim_clock.advance_clock();
    }

    output_file << "Parallel execution took: " << sim_clock.show_clock() - 2 << " clock cycles to complete\n\n";
    clock_line_to_print.pop_back();
    ls_line_to_print.pop_back();
    ic_line_to_print.pop_back();
    de_line_to_print.pop_back();
    ex_line_to_print.pop_back();
    for (const auto& item : clock_line_to_print)
        output_file << item << ' ';
    output_file << '\n';
    for (const auto& item : ls_line_to_print)
        output_file << item << ' ';
    output_file << '\n';
    for (const auto& item : ic_line_to_print)
        output_file << item << ' ';
    output_file << '\n';
    for (const auto& item : de_line_to_print)
        output_file << item << ' ';
    output_file << '\n';
    for (const auto& item : ex_line_to_print)
        output_file << item << ' ';
    output_file << '\n';
    output_file.close();
}

Simulation::Simulation() {
    sim_on = true;
    IP_offset = 1;
    need_fetch_window = true;
    IP = 0xFFF0;
}

