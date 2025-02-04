#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findMinDistanceVertex(int dist[], int sptSet[], int V) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printShortestDistances(int dist[], int V) {
    printf("Shortest distances from the source node:\n");
    for (int i = 0; i < V; i++) {
        printf("To node %d: %d\n", i, dist[i]);
    }
}
void performDijkstra(int **graph, int V, int src) {
    int *dist = (int *)malloc(V * sizeof(int));
    int *sptSet = (int *)malloc(V * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = findMinDistanceVertex(dist, sptSet, V);

        // Mark the picked vertex as visited
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the solution (shortest distances)
    printShortestDistances(dist, V);

    free(dist);
    free(sptSet);
}

int main() {
    int V, src;

    // Get user input for the number of points (V)
    printf("Enter the number of points: ");
    scanf("%d", &V);

    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                printf("Enter the weight for edge (%d, %d): ", i, j);
                scanf("%d", &graph[i][j]);
            }
        }
    }

    // Get user input for the source node
    printf("Enter the source node: ");
    scanf("%d", &src);

    // Perform Dijkstra's algorithm with the given input
    performDijkstra(graph, V, src);

    // Free dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
