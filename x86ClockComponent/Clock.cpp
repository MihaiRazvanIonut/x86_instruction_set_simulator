#include "Clock.hpp"

Clock::Clock() {

    clock = 1;

}

int Clock::show_clock() const{
    return clock;
}

void Clock::advance_clock() {
    clock++;
}

std::string Clock::show_clock_in_string_type() {
    unsigned int copy_clock = show_clock();
    std::string string_int;
    while(copy_clock){
        string_int.push_back('0' + (copy_clock % 10));
        copy_clock /= 10;
    }
    std::reverse(string_int.begin(), string_int.end());
    string_int = "Clock " + string_int;
    while (string_int.length() < 20){
        string_int.push_back(' ');
    }
    string_int.push_back('|');
    return string_int;
}

