#include "Encodings.hpp"

Encodings::Encodings() {
    operation_codes["000001"] = "ADD";
    operation_codes["000010"] = "SUB";
    operation_codes["000011"] = "MOV";
    operation_codes["000100"] = "MUL";
    operation_codes["000101"] = "DIV";
    operation_codes["000110"] = "CMP";
    operation_codes["000111"] = "JMP";
    operation_codes["001001"] = "JE";
    operation_codes["001010"] = "JL";
    operation_codes["001011"] = "JG";
    operation_codes["001100"] = "JZ";
    operation_codes["001101"] = "CALL";
    operation_codes["001110"] = "RET";
    operation_codes["001111"] = "END_SIM";
    operation_codes["010000"] = "PUSH";
    operation_codes["010001"] = "POP";

    parameter_codes["00000"] = "NULL";
    parameter_codes["00001"] = "R0";
    parameter_codes["00010"] = "R1";
    parameter_codes["00011"] = "R2";
    parameter_codes["00100"] = "R3";
    parameter_codes["00101"] = "R4";
    parameter_codes["00110"] = "R5";
    parameter_codes["00111"] = "R6";
    parameter_codes["01000"] = "R7";
    parameter_codes["10000"] = "IMM";
    parameter_codes["10001"] = "ADDR";
    parameter_codes["10010"] = "ADDR_R";
}

const std::string &Encodings::decode_operation(const std::string &encoded_operation) {
    return operation_codes[encoded_operation];
}

const std::string &Encodings::decode_parameter(const std::string &encoded_parameter) {
    return parameter_codes[encoded_parameter];
}
