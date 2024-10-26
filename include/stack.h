#ifndef STACK_H
#define STACK_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack 
{
    int node_number;
    struct Stack* next;
};

void push(struct Stack **, int);
int pop(struct Stack **);

#endif
