#include <stdio.h>
#include <assert.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */

void newline() {
	putchar('\n');
}

void print(int x) {
    printf("%d\n", x);
}

void print_bool(int x) {
	if(x) {
		printf("True");
	} else {
		printf("False");
	}
}

int get_int() {
	int input;
	scanf("%d", &input);
	return input;
}

void assertTrue(int expression) {
	assert(expression);
	printf(GREEN "PASSED\n" RESET);
}
