#include <stdio.h>
#include "stack.h"

Stack stack;

int main() {
    construct(&stack);
    int i = 0;
    while(i < 5) {
        push(&stack, i);
	i++;
    }

    while(!isEmpty(stack)) {
        show(stack);
	pop(&stack);
    }

    show(stack);
}
