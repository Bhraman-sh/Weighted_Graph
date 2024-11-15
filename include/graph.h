#ifndef GRAPH_H
#define GRAPH_H
#include <malloc.h>

#include "queue.h"
#include "stack.h"
#include "list.h"
// This program implements graph using linked list
// First we have a linked list of Node
// Each Nodes consists a pointer to 'Path', the path is also a linked list
struct Path
{
    int node_number;
    float weight;
    struct Path *next_path;
};

struct Node 
{
    int node_number;
    struct Node *next_node;
    struct Path *path;
};

struct Graph 
{
    int node_count, path_count;
    struct Node *node;
};

// HELPER STRUCTURE TO STORE THE OUTPUT OF DIJKSTRA ALGORITHM
struct dijkstra
{
    short int done;               // CURRENT NODE
    float weight;           // TOTAL WEIGHT OF THE PATH TO THE NODE
    int prev;               // PREVIOUS NODE IN THE PATH
};

// NEW NODE
void addNode(struct Graph*);

// PATH RELATED
void addPath(struct Graph*, int, int, float);
void addPathList(struct Path **, int to, float);           // Helper function: adds entire paths as a linked list

// GRAPH TRAVERSAL
int breadthFirstTraversal(struct Graph, int);
int depthFirstTraversal(struct Graph, int);

// CHECK IF THERE IS ANY CYCLE IN THE GRAPH;
int checkCycle(struct Graph *);         // returns the number of cycles

// MINNIMUM WEIGHT SPANNING TREE ALGORITHMS
void primsAlgorithm(struct Graph, struct Graph*);                      // Simply print the tree
void kruskalAlgorithm(struct Graph*);

// MINNIMUM PATH ALGORITHMS 
void dijkstraAlgorithm(struct Graph*, int, struct dijkstra *output);
void initOutput(struct dijkstra*, int);
int findMinimumWeightNode(struct dijkstra*, int);

// DELETION
void deleteNode(struct Graph*, int);
void deletePath(struct Graph*, int, int);

// PRINTING GRAPH
void printGraph(struct Graph);
void printPaths(struct Path*);                      // Prints paths

//
int getnode_count();
int getpath_count();

#endif
