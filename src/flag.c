#include "flag.h"

char* flagToString(Flag flag) {
	switch (flag) {
	    case flag_IDENTIFIER:
		    return "ID";
	    case flag_ADDITION:
		    return "+";
	    case flag_MULTIPLICATION:
		    return "*";
	    case flag_OR:
		    return "||";
	    case flag_AND:
		    return "&&";
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
