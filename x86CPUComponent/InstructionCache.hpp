#ifndef X86_INSTRUCTIONCACHE_HPP
#define X86_INSTRUCTIONCACHE_HPP


#include <queue>
#include <string>
#include <vector>
#include "CPUUtils.hpp"
class InstructionCache {

public:

    void clear_instruction_cache();
    void fetch_window_instruction_caching(const std::vector<std::string>& fetch_window);
    bool check_if_need_fetch_window();
    std::vector<std::string> fetch_instruction();

private:
    std::queue<std::string> incomplete_instruction_cache_queue;
    bool does_instruction_cache_have_complete_instruction();
};

#endif