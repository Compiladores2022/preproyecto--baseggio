#include <stdio.h>
#include "stack.h"

Stack stack;

void show(Stack stack);
int main() {
    construct(&stack);
    int i = 0;
    float data = 0.0;
    while(i < 5) {
        push(&stack, &data);
	i++;
	data++;
    }


    while(!isEmpty(stack)) {
        show(stack);
	pop(&stack);
    }

    show(stack);
}

void show(Stack stack) {
    if(!isEmpty(stack)) {
        float p = *(float* ) peek(stack);
	printf("%f\n", p);
    }
}
