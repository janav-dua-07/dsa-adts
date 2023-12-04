#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int vertices;
    struct Node** adjacencyList;
};

// Structure to represent a queue for BFS
struct Queue {
    int front, rear;
    unsigned capacity;
    int* array;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    // Allocate memory for an array of adjacency lists
    graph->adjacencyList = (struct Node**)malloc(vertices * sizeof(struct Node*));

    // Initialize each adjacency list as empty by setting all pointers to NULL
    for (int i = 0; i < vertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; ++i) {
        printf("Adjacency list of vertex %d:\n", i);
        struct Node* current = graph->adjacencyList[i];
        while (current) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to create a new queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to enqueue a value to the queue
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == queue->capacity - 1) {
        fprintf(stderr, "Queue overflow\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->array[++queue->rear] = value;
}

// Function to dequeue a value from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }

    int value = queue->array[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        ++queue->front;
    }

    return value;
}

// Function to perform Breadth-First Search (BFS)
void bfs(struct Graph* graph, int startVertex) {
    // Create a boolean array to keep track of visited vertices
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = false;
    }

    // Create a queue for BFS
    struct Queue* queue = createQueue(graph->vertices);

    // Mark the starting vertex as visited and enqueue it
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("BFS starting from vertex %d: ", startVertex);

    // Perform BFS
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the current vertex
        struct Node* temp = graph->adjacencyList[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }

    printf("\n");

    // Free allocated memory
    free(visited);
    free(queue->array);
    free(queue);
}

// Recursive function for Depth-First Search (DFS)
void dfsUtil(struct Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    // Visit all adjacent vertices of the current vertex
    struct Node* temp = graph->adjacencyList[vertex];
    while (temp) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform Depth-First Search (DFS)
void dfs(struct Graph* graph, int startVertex) {
    // Create a boolean array to keep track of visited vertices
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = false;
    }

    printf("DFS starting from vertex %d: ", startVertex);

    // Perform DFS
    dfsUtil(graph, startVertex, visited);

    printf("\n");

    // Free allocated memory
    free(visited);
}

// Function to free the memory allocated for the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; ++i) {
        struct Node* current = graph->adjacencyList[i];
        while (current) {
            struct Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjacencyList);
    free(graph);
}

// Function to check if an edge exists between two vertices
bool hasEdge(struct Graph* graph, int src, int dest) {
    struct Node* current = graph->adjacencyList[src];
    while (current) {
        if (current->data == dest) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to remove an edge between two vertices
void removeEdge(struct Graph* graph, int src, int dest) {
    struct Node* current = graph->adjacencyList[src];
    struct Node* prev = NULL;

    // Find and remove the edge in the adjacency list of src
    while (current) {
        if (current->data == dest) {
            if (prev) {
                prev->next = current->next;
            } else {
                graph->adjacencyList[src] = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    // Remove the reverse edge for an undirected graph
    current = graph->adjacencyList[dest];
    prev = NULL;

    while (current) {
        if (current->data == src) {
            if (prev) {
                prev->next = current->next;
            } else {
                graph->adjacencyList[dest] = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

// Function to get the in-degree of a vertex
int inDegree(struct Graph* graph, int vertex) {
    int inDegreeCount = 0;

    for (int i = 0; i < graph->vertices; ++i) {
        struct Node* current = graph->adjacencyList[i];
        while (current) {
            if (current->data == vertex) {
                inDegreeCount++;
                break;
            }
            current = current->next;
        }
    }

    return inDegreeCount;
}

// Function to get the out-degree of a vertex
int outDegree(struct Graph* graph, int vertex) {
    int outDegreeCount = 0;

    struct Node* current = graph->adjacencyList[vertex];
    while (current) {
        outDegreeCount++;
        current = current->next;
    }

    return outDegreeCount;
}

// Helper function for topological sort
void topologicalSortUtil(struct Graph* graph, int vertex, bool* visited, int* stack, int* index) {
    visited[vertex] = true;

    struct Node* current = graph->adjacencyList[vertex];
    while (current) {
        int adjVertex = current->data;
        if (!visited[adjVertex]) {
            topologicalSortUtil(graph, adjVertex, visited, stack, index);
        }
        current = current->next;
    }

    stack[(*index)--] = vertex;
}

// Function to perform topological sort
void topologicalSort(struct Graph* graph) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = false;
    }

    int* stack = (int*)malloc(graph->vertices * sizeof(int));
    int index = graph->vertices - 1;

    for (int i = 0; i < graph->vertices; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &index);
        }
    }

    printf("Topological Sort: ");
    for (int i = 0; i < graph->vertices; ++i) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(visited);
    free(stack);
}

// Helper function for cycle detection in DFS
bool isCyclicUtil(struct Graph* graph, int vertex, bool* visited, bool* inStack) {
    visited[vertex] = true;
    inStack[vertex] = true;

    struct Node* current = graph->adjacencyList[vertex];
    while (current) {
        int adjVertex = current->data;
        if (!visited[adjVertex]) {
            if (isCyclicUtil(graph, adjVertex, visited, inStack)) {
                return true;
            }
        } else if (inStack[adjVertex]) {
            // If the adjacent vertex is already in the stack, then there is a cycle
            return true;
        }

        current = current->next;
    }

    // Remove the vertex from the recursion stack after exploration
    inStack[vertex] = false;

    return false;
}

// Function to detect cycles in a directed graph
bool hasCycle(struct Graph* graph) {
    // Create arrays to keep track of visited vertices and the recursion stack
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    bool* inStack = (bool*)malloc(graph->vertices * sizeof(bool));

    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = false;
        inStack[i] = false;
    }

    // Perform DFS for each unvisited vertex
    for (int i = 0; i < graph->vertices; ++i) {
        if (!visited[i]) {
            if (isCyclicUtil(graph, i, visited, inStack)) {
                // Free allocated memory before returning
                free(visited);
                free(inStack);
                return true;
            }
        }
    }

    // Free allocated memory before returning
    free(visited);
    free(inStack);

    // No cycle found
    return false;
}

// Function to find the vertex with the minimum distance value
int minDistance(int* distance, bool* sptSet, int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; ++v) {
        if (!sptSet[v] && distance[v] < min) {
            min = distance[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the solution of Dijkstra's algorithm
void printDijkstra(int* distance, int vertices, int startVertex) {
    printf("Dijkstra's Shortest Paths starting from vertex %d:\n", startVertex);

    for (int i = 0; i < vertices; ++i) {
        printf("Vertex %d: Distance = %d\n", i, distance[i]);
    }
}

// Function to perform Dijkstra's algorithm
void dijkstra(struct Graph* graph, int startVertex) {
    int vertices = graph->vertices;
    int* distance = (int*)malloc(vertices * sizeof(int));
    bool* sptSet = (bool*)malloc(vertices * sizeof(bool));

    // Initialize distances and set of visited vertices
    for (int i = 0; i < vertices; ++i) {
        distance[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance from the source vertex to itself is always 0
    distance[startVertex] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; ++count) {
        int u = minDistance(distance, sptSet, vertices);

        // Mark the selected vertex as visited
        sptSet[u] = true;

        // Update distance value of the adjacent vertices
        struct Node* current = graph->adjacencyList[u];
        while (current) {
            int v = current->data;
            if (!sptSet[v] && distance[u] != INT_MAX &&
                distance[u] + 1 < distance[v]) {  // Assuming edge weights are 1
                distance[v] = distance[u] + 1;
            }
            current = current->next;
        }
    }

    // Print the solution
    printDijkstra(distance, vertices, startVertex);

    // Free allocated memory
    free(distance);
    free(sptSet);
}

// Helper function to clone a graph using DFS
void cloneGraphUtil(struct Graph* original, struct Graph* cloned, int vertex, bool* visited, int* vertexMap) {
    visited[vertex] = true;

    // Create a mapping from original vertex to cloned vertex
    vertexMap[vertex] = cloned->vertices;

    // Add vertices to the cloned graph
    for (int i = 0; i < original->vertices; ++i) {
        if (!visited[i]) {
            struct Node* current = original->adjacencyList[i];
            while (current) {
                addEdge(cloned, vertexMap[i], vertexMap[current->data]);
                current = current->next;
            }
        }
    }

    // Recursively clone the neighbors of the current vertex
    struct Node* current = original->adjacencyList[vertex];
    while (current) {
        if (!visited[current->data]) {
            cloneGraphUtil(original, cloned, current->data, visited, vertexMap);
        }
        current = current->next;
    }
}

// Function to clone a graph
struct Graph* cloneGraph(struct Graph* original) {
    if (!original) {
        return NULL;
    }

    // Create a new graph with the same number of vertices
    struct Graph* cloned = createGraph(original->vertices);

    // Array to keep track of visited vertices during DFS
    bool* visited = (bool*)malloc(original->vertices * sizeof(bool));
    int* vertexMap = (int*)malloc(original->vertices * sizeof(int));

    // Initialize visited array
    for (int i = 0; i < original->vertices; ++i) {
        visited[i] = false;
    }

    // Clone the graph using DFS
    cloneGraphUtil(original, cloned, 0, visited, vertexMap);

    // Free allocated memory
    free(visited);
    free(vertexMap);

    return cloned;
}