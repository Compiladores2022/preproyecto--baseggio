#include "assertions.h"
#include <stdio.h>
#include <stdlib.h>


#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define RED     "\033[31m"      /* Red */
#define MAGENTA "\033[35m"      /* Magenta */

void assertTrue(int expression) {
	if(expression) {
		printf(GREEN "PASSED\n" RESET);
	} else {
		printf(RED "FAILED\n" RESET);
		printf(MAGENTA "expected: " RESET);
		printf(RED "False " RESET);
		printf(MAGENTA "but " RESET);
		printf(GREEN "True " RESET);
		printf(MAGENTA "was found\n" RESET);
		exit(EXIT_FAILURE);
	}
}

void assertFalse(int expression) {
	if(!expression) {
		printf(GREEN "PASSED\n" RESET);
	} else {
		printf(RED "FAILED\n" RESET);
		printf(MAGENTA "expected: " RESET);
		printf(RED "False " RESET);
		printf(MAGENTA "but " RESET);
		printf(GREEN "True " RESET);
		printf(MAGENTA "was found\n" RESET);
		exit(EXIT_FAILURE);
	}
}

void assertEquals(void* expected, void* value, int (*equals) (void*, void*), char* (*toString) (void*)) {
	if((*equals) (expected, value)) {
		printf(GREEN "PASSED\n" RESET);
	} else {
		printf(RED "FAILED\n" RESET);
		printf(MAGENTA "expected: " RESET);
		printf("%s ", (*toString) (expected));
		printf(MAGENTA "but " RESET);
		printf("%s ", (*toString) (value));
		printf(MAGENTA "was found\n" RESET);
		exit(EXIT_FAILURE);
	}
}
