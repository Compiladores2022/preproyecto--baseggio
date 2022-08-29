#include <stdio.h>
#include "queue.h"

Queue queue;

int main() {
    construct(&queue);
    enqueue(&queue, 0);
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    while(!isEmpty(queue)) {
	show(queue);
        dequeue(&queue);
    }

    show(queue);
}
