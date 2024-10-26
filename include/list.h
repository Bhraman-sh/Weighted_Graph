#ifndef LIST_H
#define LIST_H

// Data structure that simply puts the minimum value integer at the front
// Stores the path and the weight of each path
// Sorts based on the weight of the path

#include <malloc.h>

struct List
{
    int node1, node2;
    float pathweight;
    struct List *next;
};

void mergeNode(struct List **, int, int, float);
struct List getSmallest(struct List **list);            //.list must be checked if NULL
                                                        // before calling
int getLargest(struct List **);

void printList(struct List *);

#endif
