#include "graph.h"

int main()
{
    struct Graph graph;
    graph.node = NULL;

    addNode(&graph);
    addNode(&graph);
    addNode(&graph);
    addNode(&graph);
    addNode(&graph);
    addNode(&graph);
    addNode(&graph);

    addPath(&graph,1,2, 3);
    addPath(&graph,1,3, 10);
    addPath(&graph,2,3, 7);
    addPath(&graph,2,5, 6);
    addPath(&graph,2,7, 5);
    addPath(&graph,3,5, 6);
    addPath(&graph,3,6, 4);
    addPath(&graph,3,7, 1);
    addPath(&graph,5,6, 2);
    addPath(&graph,4,7, 4);

    printf("Original Graph\n");
    printGraph(graph);

    struct Graph minimum_span;
    minimum_span.node = NULL;

    primsAlgorithm(graph, &minimum_span);
    printf("\nThe minimum spanning tree of the graph\n");
    printGraph(minimum_span);
}
