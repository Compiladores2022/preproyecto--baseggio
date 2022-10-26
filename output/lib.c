#include <stdio.h>

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
