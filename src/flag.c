#include "flag.h"

char* flagToString(Flag flag) {
	switch (flag) {
	    case IDENTIFIER:
		    return "ID";
	    case ADDITION:
		    return "+";
	    case MULTIPLICATION:
		    return "*";
	    case OP_OR:
		    return "||";
	    case OP_AND:
		    return "&&";
	    case ASSIGNMENT:
		    return "=";
	    case SEMICOLON:
		    return ";";
	    case VALUE_INT:
		    return "vInt";
	    case VALUE_BOOL:
		    return "vBool";
	    case RETURN:
		    return "return";
	    default:
		    return "NRF";
	}
}

int isAnArithmeticBinaryOperator(Flag flag) {
    return flag == ADDITION || flag == MULTIPLICATION;
}

int isABooleanBinaryOperator(Flag flag) {
    return flag == OP_OR || flag == OP_AND;
}
