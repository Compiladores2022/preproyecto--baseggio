#include "code.h"

int iCodeIsABinaryOperator(Code code) {
    return code == code_ADDITION
        || code == code_SUBSTRACTION
        || code == code_MULTIPLICATION
        || code == code_DIVISION
        || code == code_MOD
        || code == code_OR
        || code == code_AND
        || code == code_LT
        || code == code_GT
        || code == code_EQT
        ;
}

char* iCodeToString(Code code) {
    switch (code) {
        case code_ADDITION:
            return "+";
        case code_SUBSTRACTION:
            return "-";
        case code_MULTIPLICATION:
            return "*";
        case code_DIVISION:
            return "/";
        case code_MOD:
            return "%";
        case code_OR:
            return "||";
        case code_AND:
            return "&&";
        case code_LT:
            return "<";
        case code_GT:
            return ">";
        case code_EQT:
            return "==";
        case code_FALSE_CONDITIONAL:
            return "if false";
        case code_JMP:
            return "jmp";
        case code_LABEL:
            return "label";
        case code_LABEL_START_OF_FUNCTION:
            return "start of function";
        case code_RETURN:
            return "return";
        case code_ASSIGNMENT:
            return "=";
        case code_MINUS:
            return "minus";
        case code_NEG:
            return "!";
        case code_CALL:
            return "call";
        case code_LOAD:
            return "load";
        default:
            return "NRF";
    }
}