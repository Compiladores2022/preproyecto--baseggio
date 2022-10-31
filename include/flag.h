#ifndef FLAG_H
#define FLAG_H
typedef enum {
     flag_IDENTIFIER
    ,flag_ADDITION
    ,flag_SUBSTRACTION
    ,flag_MULTIPLICATION
    ,flag_DIVISION
    ,flag_MOD
    ,flag_OR
    ,flag_AND
    ,flag_LT
    ,flag_GT
    ,flag_EQT
    ,flag_MINUS
    ,flag_NEG	
    ,flag_METHOD_DECLARATION
    ,flag_METHOD_CALL
    ,flag_PARAM
    ,flag_IF
    ,flag_IF_ELSE
    ,flag_WHILE
    ,flag_ASSIGNMENT
    ,flag_SEMICOLON
    ,flag_VALUE_INT
    ,flag_VALUE_BOOL
    ,flag_RETURN
    ,flag_LABEL
    ,flag_GLOBAL_VAR_DECL
} Flag;

/* The 'flagToString' function returns a string representing the flag. */
char* flagToString(Flag flag);

/* The 'isAnArithmeticBinaryOperator' function returns TRUE iff the flag corresponds to an arithmetic binary operator. */
int isAnArithmeticBinaryOperator(Flag flag);

/* The 'isABooleanBinaryOperator' function returns TRUE iff the flag corresponds to a boolean binary operator. */
int isABooleanBinaryOperator(Flag flag);

/* The 'isABinaryOperator' function returns TRUE iff the flag corresponds to a binary operator. */
int isABinaryOperator(Flag flag);

/* The 'isAConstant' function returns TRUE iff the flag corresponds to a constant. */
int isAConstant(Flag flag);
#endif
