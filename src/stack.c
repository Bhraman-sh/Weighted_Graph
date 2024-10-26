#include "stack.h"

void push(struct Stack **stack, int node)
{
    struct Stack *new = (struct Stack*) malloc (sizeof(struct Stack));

    new->node_number = node; 
    new->next = (*stack);
    *stack = new;
}

int pop(struct Stack **stack)
{
    if ((*stack) == NULL)
    {
        printf("Stack is empty\n");
        return 0;
    }

    struct Stack *p = *stack;
    *stack = (*stack)->next;

    int retval = p->node_number;
    free(p);
    return retval;
}
