
#include "InstructionCache.hpp"

void InstructionCache::clear_instruction_cache() {
    while (!incomplete_instruction_cache_queue.empty())
        incomplete_instruction_cache_queue.pop();
}

void InstructionCache::fetch_window_instruction_caching(const std::vector<std::string>& fetch_window) {

    for (const auto& instruction : fetch_window){
        incomplete_instruction_cache_queue.push(instruction);
    }

}

bool InstructionCache::check_if_need_fetch_window() {
    if (incomplete_instruction_cache_queue.empty() or !does_instruction_cache_have_complete_instruction())
        return true;

    return false;
}

bool InstructionCache::does_instruction_cache_have_complete_instruction() {
    std::string formatted_main_instruction = CPUUtils::format_instruction_to_binary(incomplete_instruction_cache_queue.front());
    int how_many_words_needed_for_instruction_cache = 1;
    if (formatted_main_instruction[6] == '1') how_many_words_needed_for_instruction_cache++;
    if (formatted_main_instruction[11] == '1') how_many_words_needed_for_instruction_cache++;
    if (incomplete_instruction_cache_queue.size() >= how_many_words_needed_for_instruction_cache)
        return true;
    else
        return false;
}

std::vector<std::string> InstructionCache::fetch_instruction() {
    std::vector<std::string> complete_instruction;
    std::string formatted_main_instruction = CPUUtils::format_instruction_to_binary(incomplete_instruction_cache_queue.front());
    complete_instruction.push_back(incomplete_instruction_cache_queue.front());
    incomplete_instruction_cache_queue.pop();
    if (formatted_main_instruction[6] == '1') complete_instruction.push_back(incomplete_instruction_cache_queue.front()), incomplete_instruction_cache_queue.pop();
    if (formatted_main_instruction[11] == '1') complete_instruction.push_back(incomplete_instruction_cache_queue.front()), incomplete_instruction_cache_queue.pop();
    return  complete_instruction;
}
