#include "type.h"

char* typeToString(Type type) {
    switch (type) {
        case TYPE_INT:
            return "Int";
        case TYPE_BOOL:
            return "Bool";
	case TYPE_VOID:
	    return "void";
        default:
            return "NRF";
    }
}
