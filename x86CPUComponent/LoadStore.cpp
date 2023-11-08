#include "LoadStore.hpp"

std::vector<std::string>
LoadStore::request_fetch_window(const uint16_t &IP_value, int IP_offset, const std::vector<std::string>& instruction_memory){
        std::vector<std::string> fetch_window;
        for (int i = 0; i < instruction_memory.size() - 1; ++i){
            if (instruction_memory[i][0] == '#'){
                std::string pure_hex_string = instruction_memory[i];
                pure_hex_string.erase(remove(pure_hex_string.begin(), pure_hex_string.end(), '#'), pure_hex_string.end());
                while (pure_hex_string.length() < 4)
                    pure_hex_string = "0" + pure_hex_string;
                uint16_t temp_label = CPUUtils::convert_hex_string_to_value(pure_hex_string);
                if (IP_value == temp_label){
                    for (int j = 0; j < 4 and i + IP_offset < instruction_memory.size(); ++j){
                        fetch_window.push_back(instruction_memory[i + IP_offset]);
                        IP_offset++;
                    }
                    break;
                }
            }

        }

        return fetch_window;
}

void LoadStore::store_request(Memory& memory, const uint16_t& store_value, const uint16_t& store_address) {
        memory.data_memory.store(store_value, store_address);
}

const uint16_t &LoadStore::load_request(Memory& memory, const uint16_t& load_address) {
    return memory.data_memory.load(load_address);
}
