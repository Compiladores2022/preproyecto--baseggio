#ifndef FLAG_H
#define FLAG_H
typedef enum {
    flag_IDENTIFIER,
    flag_ADDITION,
    flag_MULTIPLICATION,
    flag_OR,
    flag_AND,
    flag_ASSIGNMENT,
    flag_SEMICOLON,
    flag_VALUE_INT,
    flag_VALUE_BOOL,
    flag_RETURN
} Flag;

char* flagToString(Flag flag);
int isAnArithmeticBinaryOperator(Flag flag);
int isABooleanBinaryOperator(Flag flag);
int isABinaryOperator(Flag flag);
int isValue(Flag flag);
#endif
