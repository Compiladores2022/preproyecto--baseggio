#ifndef FLAG_H
#define FLAG_H
typedef enum {
    IDENTIFIER,
    ADDITION,
    MULTIPLICATION,
    OP_OR,
    OP_AND,
    ASSIGNMENT,
    SEMICOLON,
    VALUE_INT,
    VALUE_BOOL,
    RETURN
} Flag;

char* flagToString(Flag flag);
#endif
