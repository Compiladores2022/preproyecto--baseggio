#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue queue;

void show(Queue queue);

int main() {
    construct(&queue);
    float data1 = 1.0;
    float data2 = 0.5;
    float data3 = 0.25;
    enqueue(&queue, &data1);
    enqueue(&queue, &data2);
    enqueue(&queue, &data3);
    while(!isEmpty(queue)) {
	show(queue);
        dequeue(&queue);
    }
    show(queue);
}

void show(Queue queue) {
	if(!isEmpty(queue)) {
	    float data = *(float* ) head(queue);
	    printf(" %f", data);
	}
}
