#ifndef FLAG_H
#define FLAG_H
typedef enum {
    flag_IDENTIFIER,
    flag_ADDITION,
    flag_SUBSTRACTION,
    flag_MULTIPLICATION,
    flag_DIVISION,
    flag_MOD,
    flag_OR,
    flag_AND,
    flag_LT,
    flag_GT,
    flag_EQT,
    flag_MINUS,
    flag_NEG,	
    flag_METHOD_DECLARATION,
    flag_METHOD_CALL,
    flag_PARAM,
    flag_IF,
    flag_IF_ELSE,
    flag_WHILE,
    flag_ASSIGNMENT,
    flag_SEMICOLON,
    flag_VALUE_INT,
    flag_VALUE_BOOL,
    flag_RETURN,
    flag_LABEL
} Flag;

char* flagToString(Flag flag);
int isAnArithmeticBinaryOperator(Flag flag);
int isABooleanBinaryOperator(Flag flag);
int isABinaryOperator(Flag flag);
int isValue(Flag flag);
#endif
