#include "list.h"

void mergeNode(struct List **list, int node1, int node2, float pathweight)
{
    if (*list == NULL)
    {
        *list = (struct List *) malloc (sizeof(struct List));
        (*list)->node1 = node1;
        (*list)->node2 = node2;
        (*list)->pathweight = pathweight;

        (*list)->next = NULL;

        return;
    }

    if ((*list)->pathweight > pathweight)
    {
        struct List *new = (struct List *) malloc (sizeof(struct List));
        new->node1 = node1;
        new->node2 = node2;
        new->pathweight = pathweight;

        new->next = *list;
        *list = new;

        return;
    }

    while (((*list)->next != NULL) && !(((*list)->pathweight < pathweight) && ((*list)->next->pathweight >= pathweight)))
    {
        list = &(*list)->next;
    }

    struct List *new = (struct List *) malloc (sizeof(struct List));
    new->node1 = node1;
    new->node2 = node2;
    new->pathweight = pathweight;

    new->next = (*list)->next;
    (*list)->next = new;
}

struct List getSmallest(struct List **list)
{
    struct List return_list = **list;

    struct List *p = *list;
    *list = (*list)->next;

    free(p);
    return return_list;
}

void printList(struct List *list)
{
    while(list != NULL)
    {
        printf("%d %d %f\n", list->node1, list->node2, list->pathweight);
        list = list->next;
    }
    printf("\n");
}
