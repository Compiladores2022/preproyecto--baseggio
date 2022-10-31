#ifndef CODE_H
#define CODE_H

typedef enum {
     code_ADDITION
    ,code_SUBSTRACTION
    ,code_MULTIPLICATION
    ,code_DIVISION
    ,code_MOD
    ,code_OR
    ,code_AND
    ,code_LT
    ,code_GT
    ,code_EQT
    ,code_FALSE_CONDITIONAL
    ,code_JMP
    ,code_LABEL
    ,code_LABEL_START_OF_FUNCTION
    ,code_LABEL_END_OF_FUNCTION
    ,code_RETURN
    ,code_ASSIGNMENT
    ,code_MINUS
    ,code_NEG
    ,code_CALL
    ,code_LOAD
    ,code_GLOBAL_VAR_DECL
} Code;

/* The 'iCodeIsABinaryOperator' function returns TRUE iff the instruction code corresponds to a binary operator. */
int	iCodeIsABinaryOperator(Code code);

/* The 'iCodeToString' returns a string representing the instruction code. */
char*	iCodeToString(Code code);

#endif
