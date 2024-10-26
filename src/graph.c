#include "graph.h"

void addNode(struct Graph *graph)
{
    // printf("addNode\n");
    struct Node *node = (*graph).node;
    if (node == NULL)
    {
        (*graph).node_count = 1;
        (*graph).path_count = 0;

        (*graph).node = (struct Node*) malloc (sizeof(struct Node));

        (*graph).node->node_number = 1;
        (*graph).node->next_node = NULL;
        (*graph).node->path = NULL; 

        return;
    }

    while(node->next_node != NULL)
    {
        node = node->next_node;
    }

    struct Node *s = (struct Node*) malloc(sizeof(struct Node));
    s->node_number = ++(*graph).node_count;
    s->next_node = NULL;
    s->path = NULL;

    node->next_node = s;
}

void addPath(struct Graph* graph, int node1, int node2, float weight)
{
    if ((*graph).node == NULL)
    {
        printf("Add a node first\n");
        return;
    }

    if (node1 > (*graph).node_count || node2 > (*graph).node_count)
    {
        printf("Node/s doesn't exitst\n");
        return;
    }

    struct Node *curr_node = (*graph).node;

    while(curr_node->node_number != node1)
    {
        curr_node = curr_node->next_node;
    }

    addPathList(&(curr_node->path), node2, weight);

    curr_node = (*graph).node;
    while(curr_node->node_number != node2)
    {
        curr_node = curr_node->next_node;
    }

    addPathList(&(curr_node->path), node1, weight);

    (*graph).path_count++;
}

void addPathList(struct Path **path_head, int node2, float weight)
{
    if ((*path_head) == NULL)
    {
        (*path_head) = (struct Path*) malloc (sizeof(struct Path));
        (*path_head)->node_number = node2;
        (*path_head)->weight = weight;
        (*path_head)->next_path = NULL;
        return;
    }

    struct Path *curr_path = *path_head;

    while(1)
    {
        if (curr_path->node_number == node2)
        {
            printf("Path already exists\n");
            return;
        }

        if (curr_path->next_path == NULL) break;

        curr_path = curr_path->next_path;
    }

    struct Path *new = (struct Path*) malloc (sizeof(struct Path));
    new->node_number = node2;
    new->weight = weight;
    new->next_path = NULL;

    curr_path->next_path = new;
}

int breadthFirstTraversal(struct Graph graph, int startingNode)
{
    if (startingNode > (graph).node_count)
    {
        printf("Starting node doesn't exist\n");
        return 0;
    }

    int cycle_flag = 0;

    struct Queue *queue = NULL;
    short int *queue_flags = (short int*) malloc ((graph).node_count * (sizeof(short int)));

    for (int i = 0; i < (graph).node_count; i++)
    {
        queue_flags[i] = 0;
    }

    enqueue(&queue, startingNode);
    queue_flags[startingNode -1] = 1;

    while(queue != NULL)
    {
        int current_node = dequeue(&queue);
        printf("%d ", current_node);
        struct Node *node = graph.node;

        while(node->node_number != current_node)
        {
            node = node->next_node;
        }

        struct Path *path = node->path;
        while(path != NULL)
        {
            int node_number = path->node_number;

            if(queue_flags[node_number - 1] == 0)
            {
                enqueue(&queue, node_number);
                queue_flags[node_number -1] = 1;
            }
            else 
            {
                cycle_flag++;
            }

            path = path->next_path;
        }
    }
    printf("\n");   
    free(queue_flags);

    return cycle_flag;
}

int depthFirstTraversal(struct Graph graph, int startingNode)
{
    if (startingNode > (graph).node_count)
    {
        printf("Starting node doesn't exist\n");
        return 0;
    }

    int cycle_flag = 0;                 // Check if there is cycles in the graph

    struct Stack *stack = NULL;
    short int *stack_flags = (short int*) malloc ((graph).node_count * (sizeof(short int)));

    for (int i = 0; i < (graph).node_count; i++)
    {
        stack_flags[i] = 0;
    }

    push(&stack, startingNode);
    stack_flags[startingNode -1] = 1;

    printf("Depth Frist Traversal: ");
    while(stack != NULL)
    {
        int current_node = pop(&stack);
        printf("%d ", current_node);
        struct Node *node = graph.node;

        while(node->node_number != current_node)
        {
            node = node->next_node;
        }

        struct Path *path = node->path;
        while(path != NULL)
        {
            int node_number = path->node_number;

            if(stack_flags[node_number - 1] == 0)
            {
                push(&stack, node_number);
                stack_flags[node_number -1] = 1;
            }
            else
            {
                cycle_flag++;
            }

            path = path->next_path;
        }
    }
    printf("\n");   
    free(stack_flags);

    return cycle_flag;
}

int checkCycle(struct Graph *graph)
{
    return (depthFirstTraversal(*graph, graph->node->node_number) - (*graph).path_count);
}

void primsAlgorithm(struct Graph input_graph, struct Graph *output_graph)
{
    if ((input_graph).node == NULL)
    {
        printf("Empty graph\n");
        return;
    }

    for (int i = 0; i < (input_graph).node_count; ++i)
    {
        addNode(output_graph);
    }
    
    struct Node *node = input_graph.node;
    int node_number = node->node_number;

    struct List *list = NULL;

    int i = 0;
    while(1)
    {
        struct Path *curr_path = node->path;
        while (curr_path != NULL)
        {
            mergeNode(&list, node_number, curr_path->node_number, curr_path->weight);
            curr_path = curr_path->next_path;
        }
        printf("In the list\n");

        printList(list);
        if (list == NULL)
        {
            return;
        }
        struct List temp_list = getSmallest(&list);

        addPath(output_graph, temp_list.node1, temp_list.node2, temp_list.pathweight);
        deletePath(&input_graph, temp_list.node1, temp_list.node2);

        while (checkCycle(output_graph) != 0)
        {
            deletePath(output_graph, temp_list.node1, temp_list.node2);
            if (list == NULL)
            {
                return;
            }
            temp_list = getSmallest(&list);
            addPath(output_graph, temp_list.node1, temp_list.node2, temp_list.pathweight);
            deletePath(&input_graph, temp_list.node1, temp_list.node2);
        }

        node = input_graph.node;
        while (node->node_number != temp_list.node2)
        {
            node = node->next_node;
        }
        node_number = node->node_number;
    }
}

void deleteNode(struct Graph *graph, int node)
{
    if (node > (*graph).node_count)
    {
        printf("Node doesn't exist(Deletion attempted)");
        return;
    }

    // POINTER TO POINTER TO NODE, the indirect pointer stores the addres of 
    // the pointer in the link. So when we dereference and change the pointer, 
    // we change the link
    struct Node **indirect = &(*graph).node;

    while ((*indirect)->node_number != node)
    {
        indirect = &(*indirect)->next_node;
    }

    struct Queue *pathQueue = NULL;
    struct Path *path = (*indirect)->path;
    struct Node *p = *indirect;

    // PUT ALL THE PATH OF THE NODE IN A QUEUE
    while (path != NULL)
    {
        enqueue(&pathQueue, path->node_number);
        path = path->next_path;
    }

    // USE THE QUEUE TO DELTE ALL THE PATH FROM THE NODE
    while (pathQueue != NULL)
    {
        deletePath(graph, node, dequeue(&pathQueue));
    }

    // DELETE THE NODE
    (*indirect) = (*indirect)->next_node;
    free(p);

    (*graph).node_count--;
}

void deletePath(struct Graph *graph, int node1, int node2)
{
    if ((node1 > (*graph).node_count) || (node2 > (*graph).node_count))
    {
        printf("Node/s doesn't exist\n");
        return;
    }

    // NODE POINTER to traverse through the node
    struct Node *curr_node = (*graph).node;

    // POINTER TO PATH POINTER to traverse through the path and change the 
    // path link
    struct Path **path;
    struct Path *p;     // Used to free memory

    // SEARCH FOR THE NODE
    while (curr_node->node_number != node1)
    {
        curr_node = curr_node->next_node;
    }

    path = &(curr_node)->path;
    if (*path == NULL)
    {
        printf("Path doesn't exits\n");
        return;
    }

    // SEARCH FOR PATH FROM NODE1 TO NODE2
    while((*path)->node_number != node2)
    {
        path = &(*path)->next_path;
        if (*path == NULL)
        {
            printf("Path doesn't exits\n");
            return;
        }
    }

    // DELETE THE PATH
    p = *path;
    (*path) = (*path)->next_path;
    free(p);

    // UNDIRECTED GRAPH, so do the same thing for path from node2 to node1
    curr_node = (*graph).node;
    while (curr_node->node_number != node2)
    {
        curr_node = curr_node->next_node;
    }
    path = &(curr_node)->path;

    if (*path == NULL)
    {
        printf("Path doesn't exits\n");
        return;
    }

    while((*path)->node_number != node1)
    {
        path = &(*path)->next_path;
        if (*path == NULL)
        {
            printf("Path doesn't exits\n");
            return;
        }
    }

    p = *path;
    (*path) = (*path)->next_path;
    free(p);

    (*graph).path_count--;
}

void printGraph(struct Graph graph)
{
    struct Node *node = graph.node;
    while(node != NULL)
    {
        printf("%d", node->node_number);
        printPaths(node->path);
        node = node->next_node;
    }
}

void printPaths(struct Path* path)
{
    while(path != NULL)
    {
        printf("->(%f) %d ", path->weight, path->node_number);
        path = path->next_path;
    }
    printf("\n");
}
