#ifndef X86_ENCODINGS_HPP
#define X86_ENCODINGS_HPP


#include <unordered_map>
#include <string>


class Encodings{

public:
    Encodings();
    const std::string& decode_operation(const std::string& encoded_operation);
    const std::string& decode_parameter(const std::string& encoded_parameter);
private:
    std::unordered_map<std::string, std::string> operation_codes;
    std::unordered_map<std::string, std::string> parameter_codes;
};

#endif