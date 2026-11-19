#include <iostream>
#include <climits>
using namespace std;

#define V 5   

int main() {

    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int key[V];
    int parent[V];  
    bool inQ[V];       

   
    for (int u = 0; u < V; u++) {
        key[u] = INT_MAX;
        parent[u] = -1;
        inQ[u] = true;
    }

    int r = 0;        
    key[r] = 0;      
    parent[r] = -1; 


    for (int count = 0; count < V - 1; count++) {

        int min = INT_MAX, u;
        for (int i = 0; i < V; i++) {
            if (inQ[i] && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        inQ[u] = false; 


        for (int v = 0; v < V; v++) {

            if (graph[u][v] && inQ[v] &&
                graph[u][v] < key[v]) {

                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i
             << "\t" << graph[i][parent[i]] << endl;
    }

    return 0;
}
