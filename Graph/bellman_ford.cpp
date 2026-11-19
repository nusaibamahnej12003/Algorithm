#include<bits/stdc++.h>
using namespace std;
void dijkstra(int V,vector<vector<int>> adj[])
{
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
    vector<bool> visited(V,false);
    vector<int> d(V,100000);
    d[0]=0;
    pq.push({0,0});
    
for(int i=0;i<V-1;i++){

    for(int i=0;i<V;i++)
    {
         auto p=pq.top();
        int u=p.second;
        int cost = p.first;
        pq.pop();
        
       
        for(auto &a: adj[u])
        {
            int v=a[0];
            cost=a[1]; 
            
                if(d[u]+cost< d[v])
                {
                    d[v]=d[u]+cost;
                    pq.push({d[v],v});

                }         
        }
    }
}

for(int z=0;z<V;z++)
{
    cout<<"0 -> "<<z<<" = "<<d[z]<<endl;
}
    
}

int main()
{
    int V=6;
    vector<vector<int>> adj[V];
    adj[0].push_back({1,6});
    adj[0].push_back({2,4});
    adj[0].push_back({3,5});

    adj[1].push_back({4,-1});

    adj[2].push_back({1,-2});
    adj[2].push_back({4,3});


    adj[3].push_back({2,-2});
    adj[3].push_back({5,-1});

    adj[4].push_back({5,3});

    dijkstra(V,adj);
    return 0;

}

/*

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Using a large value for Infinity
const long long INF = 1e15;

struct Edge {
    int u, v, w;
};

void solve() {
    int n, m;
    cout << "Enter number of cities (N) and roads (M): ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter roads (Source Destination Cost/Reward):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);

    // Assume the trader starts at City 0
    int source = 0;
    int destination = n - 1;
    dist[source] = 0;

    // Step 1: Relax all edges N-1 times
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].w;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Step 2: Detect Negative Cycle (The Infinite Reward Loop)
    bool negativeCycle = false;
    for (int j = 0; j < m; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].w;

        // If we can still relax an edge, a negative cycle exists
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            negativeCycle = true;
            break;
        }
    }

    // Step 3: Handle the Output
    if (negativeCycle) {
        cout << "\nResult: Infinite Profit Possible" << endl;
    } 
    else if (dist[destination] == INF) {
        cout << "\nResult: Destination city is not reachable from City 0." << endl;
    } 
    else {
        cout << "\nMinimum Cost to reach City " << destination << ": " << dist[destination] << endl;

        // Path Reconstruction using the parent array
        vector<int> path;
        for (int v = destination; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }
}

int main() {
    // For faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}

*/