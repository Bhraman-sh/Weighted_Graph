#ifndef QUEUE_H
#define QUEUE_H
// Implement integer queue using linked list

#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

struct Queue
{
    int node;
    struct Queue *next;
};

void enqueue(struct Queue**, int);
int dequeue(struct Queue**);

#endif
