#include "utils.h"
#include <stdlib.h>

char* allocateChar(int size) {
	return (char*) malloc(size * sizeof(char));
}
