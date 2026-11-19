#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF 9999

// Graph definition
typedef struct {
    int V;
    int Adj[MAX][MAX];
} Graph;

// Global arrays
int color[MAX], d[MAX], f[MAX], parent[MAX];
int time = 0;

// BFS(G, s)
void BFS(Graph G, int s) {
    for (int u = 0; u < G.V; u++) {
        if (u != s) {
            color[u] = WHITE;
            d[u] = INF;
            parent[u] = -1;
        }
    }

    color[s] = GRAY;
    d[s] = 0;
    parent[s] = -1;

    int Q[MAX], front = 0, rear = 0;
    Q[rear++] = s;

    while (front < rear) {
        int u = Q[front++];

        for (int v = 0; v < G.V; v++) {
            if (G.Adj[u][v] && color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                parent[v] = u;
                Q[rear++] = v;
            }
        }

        color[u] = BLACK;
    }
}

// DFS-VISIT(G, u)
void DFS_VISIT(Graph G, int u) {
    time = time + 1;
    d[u] = time;
    color[u] = GRAY;

    for (int v = 0; v < G.V; v++) {
        if (G.Adj[u][v] && color[v] == WHITE) {
            parent[v] = u;
            DFS_VISIT(G, v);
        }
    }

    color[u] = BLACK;
    time = time + 1;
    f[u] = time;
}

// DFS(G)
void DFS(Graph G) {
    for (int u = 0; u < G.V; u++) {
        color[u] = WHITE;
        parent[u] = -1;
    }

    time = 0;

    for (int u = 0; u < G.V; u++) {
        if (color[u] == WHITE) {
            DFS_VISIT(G, u);
        }
    }
}

// MAIN
int main() {
    Graph G;
    int edges, u, v, source;

    printf("Enter number of vertices: ");
    scanf("%d", &G.V);

    // Initialize adjacency matrix
    for (int i = 0; i < G.V; i++)
        for (int j = 0; j < G.V; j++)
            G.Adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (from -> to):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        G.Adj[u][v] = 1;
        // For undirected graph, add: G.Adj[v][u] = 1;
    }

    printf("Enter source vertex for BFS: ");
    scanf("%d", &source);

    printf("\n--- BFS(G, %d) ---\n", source);
    BFS(G, source);
    for (int i = 0; i < G.V; i++) {
        printf("Node %d: Distance = %d, Parent = %d\n", i, d[i], parent[i]);
    }

    printf("\n--- DFS(G) ---\n");
    DFS(G);
    for (int i = 0; i < G.V; i++) {
        printf("Node %d: Discovery = %d, Finish = %d, Parent = %d\n", i, d[i], f[i], parent[i]);
    }

    return 0;
}