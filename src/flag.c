#include "flag.h"

char* flagToString(Flag flag) {
	switch (flag) {
	    case flag_IDENTIFIER:
		    return "ID";
	    case flag_ADDITION:
		    return "+";
	    case flag_SUBSTRACTION:
		    return "-";
	    case flag_MULTIPLICATION:
		    return "*";
	    case flag_DIVISION:
		    return "/";
	    case flag_MOD:
		    return "%";
            case flag_LT:
		    return "<";
	    case flag_GT:
		    return ">";
	    case flag_EQT:
		    return "==";
	    case flag_OR:
		    return "||";
	    case flag_AND:
		    return "&&";
	    case flag_MINUS:
		    return "-";
	    case flag_NEG:
		    return "!";
	    case flag_ASSIGNMENT:
		    return "=";
	    case flag_SEMICOLON:
		    return ";";
	    case flag_VALUE_INT:
		    return "vInt";
	    case flag_VALUE_BOOL:
		    return "vBool";
	    case flag_RETURN:
		    return "return";
            case flag_IF:
                    return "if";
            case flag_IF_ELSE:
                    return "if-then-else";
            case flag_WHILE:
                    return "while";
            case flag_METHOD:
		    return "method";
	    case flag_PARAM:
		    return "param";
	    default:
		    return "NRF";
	}
}

int isAnArithmeticBinaryOperator(Flag flag) {
    return flag == flag_ADDITION || flag == flag_MULTIPLICATION;
}

int isABooleanBinaryOperator(Flag flag) {
    return flag == flag_OR || flag == flag_AND;
}

int isABinaryOperator(Flag flag) {
    return isAnArithmeticBinaryOperator(flag) || isABooleanBinaryOperator(flag);
}

int isValue(Flag flag) {
    return flag == flag_VALUE_INT || flag == flag_VALUE_BOOL;
}
