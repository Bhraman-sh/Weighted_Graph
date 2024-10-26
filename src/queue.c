#include "queue.h"

void enqueue(struct Queue** front, int node)
{
    if(*front == NULL)
    {
        (*front) = (struct Queue*) malloc (sizeof(struct Queue));
        (*front)->node = node;
        (*front)->next = NULL;
        return;
    }

    struct Queue *new = (struct Queue*) malloc (sizeof(struct Queue));
    new->node = node;
    new->next = *front;
    *front = new;
}

int dequeue(struct Queue** front)
{
    if(*front == NULL)
    {
        printf("Queue is empty");
        return 0;
    }

    struct Queue **indirect = front;

    while((*indirect)->next != NULL)
    {
        indirect = &(*indirect)->next;
    }

    struct Queue *p = *indirect;
    int a = p->node;
    *indirect = NULL;

    free(p);
    return a;
} 
