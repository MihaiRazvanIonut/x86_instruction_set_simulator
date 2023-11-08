#ifndef X86_CLOCK_HPP
#define X86_CLOCK_HPP

#include <string>
#include <algorithm>

class Clock {

public:
    Clock();
    void advance_clock();
    int show_clock() const;
    std::string show_clock_in_string_type();
private:

    int clock;

};
#endif
