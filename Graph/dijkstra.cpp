#include<bits/stdc++.h>
using namespace std;
void dijkstra(int V,vector<vector<int>> adj[])
{
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
    vector<bool> visited(V,false);
    vector<int> d(V,100000);
    d[0]=0;
    pq.push({0,0});
    

    while(!pq.empty())
    {
        auto p=pq.top();
        int u=p.second;
        int cost = p.first;
        pq.pop();
        
        visited[u]=true;
        

        for(auto &a: adj[u])
        {
            int v=a[0];
            cost=a[1]; 
            if(!visited[v]){
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
    adj[0].push_back({1,2});
    adj[0].push_back({2,1});
    adj[0].push_back({3,5});

    adj[1].push_back({0,2});
    adj[1].push_back({2,2});
    adj[1].push_back({3,3});

    adj[2].push_back({0,1});
    adj[2].push_back({1,2});
    adj[2].push_back({3,3});
    adj[2].push_back({4,1});

    adj[3].push_back({0,5});
    adj[3].push_back({1,3});
    adj[3].push_back({2,3});
    adj[3].push_back({4,1});
    adj[3].push_back({5,5});

    adj[4].push_back({2,1});
    adj[4].push_back({3,1});
    adj[4].push_back({5,2});


    adj[5].push_back({3,5});
    adj[5].push_back({4,2});


    dijkstra(V,adj);
    return 0;

}

/*
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

// এডজাসেন্সি লিস্ট: pair<গন্তব্য, ওয়েট>
typedef pair<int, int> pii;

void multiSourceDijkstra(int n, vector<vector<pii>>& adj, vector<int>& sources) {
    vector<int> dist(n + 1, INF);
    // min-priority queue: pair<দূরত্ব, নোড>
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // ট্রিক: সবগুলো সোর্সকে শুরুতে কিউতে পুশ করা এবং তাদের ডিস্ট্যান্স ০ করা
    for (int s : sources) {
        dist[s] = 0;
        pq.push({0, s});
    }

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // যদি বর্তমান দূরত্ব আগের জানা দূরত্বের চেয়ে বেশি হয়, তবে স্কিপ
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // আউটপুট: প্রতিটি নোডের জন্য নিকটতম সোর্স থেকে দূরত্ব
    cout << "\nNode\tShortest Distance from Nearest Source" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "\t" << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<pii>> adj(n + 1);
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // আনডাইরেক্টেড গ্রাফ হলে
    }

    int k;
    cout << "Enter number of source nodes: ";
    cin >> k;
    vector<int> sources(k);
    cout << "Enter the source nodes: ";
    for (int i = 0; i < k; i++) {
        cin >> sources[i];
    }

    multiSourceDijkstra(n, adj, sources);

    return 0;
}
*/

/*

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Using a large value for infinity
const long long INF = 1e18;

// Structure to represent an Edge
struct Edge {
    int to;
    int weight;
};

// Structure for the Priority Queue to store {time, node}
struct Node {
    int id;
    long long time;

    // Operator overloading to make the priority queue a Min-Heap
    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

void findShortestPath(int n, vector<vector<Edge>>& adj, vector<int>& waiting_time) {
    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Starting from City 0
    // Initial cost is the waiting time of the starting city
    dist[0] = waiting_time[0];
    pq.push({0, dist[0]});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.id;
        long long d = current.time;

        // Optimization: If we found a better path already, skip this
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // The twist: Add edge weight PLUS the waiting time of the destination city
            if (dist[u] + weight + waiting_time[v] < dist[v]) {
                dist[v] = dist[u] + weight + waiting_time[v];
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    // Output results
    if (dist[n - 1] == INF) {
        cout << "No path exists from City 0 to City " << n - 1 << endl;
    } else {
        cout << "Minimum Total Time: " << dist[n - 1] << endl;

        // Path Reconstruction
        vector<int> path;
        for (int v = n - 1; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }
}

int main() {
    int n, e;
    cout << "Enter number of cities and roads: ";
    cin >> n >> e;

    // Input waiting times for each city
    vector<int> waiting_time(n);
    cout << "Enter waiting time for each city (from city 0 to " << n - 1 << "): " << endl;
    for (int i = 0; i < n; i++) {
        cin >> waiting_time[i];
    }

    // Input road details
    vector<vector<Edge>> adj(n);
    cout << "Enter road details (CityA CityB Distance):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Assuming roads are bidirectional
    }

    findShortestPath(n, adj, waiting_time);

    return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct State {
    int u, k;
    long long cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

void solve() {
    int n, m, k_limit;
    cin >> n >> m >> k_limit;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // dist[node][used_coupons]
    vector<vector<long long>> dist(n + 1, vector<long long>(k_limit + 1, INF));
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][0] = 0;
    pq.push({1, 0, 0});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int u = curr.u;
        int k = curr.k;
        long long d = curr.cost;

        if (d > dist[u][k]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // অপশন ১: কুপন ব্যবহার না করে স্বাভাবিকভাবে যাওয়া
            if (dist[u][k] + w < dist[v][k]) {
                dist[v][k] = dist[u][k] + w;
                pq.push({v, k, dist[v][k]});
            }

            // অপশন ২: কুপন ব্যবহার করা (যদি কুপন বাকি থাকে)
            if (k < k_limit) {
                if (dist[u][k] + (w / 2) < dist[v][k + 1]) {
                    dist[v][k + 1] = dist[u][k] + (w / 2);
                    pq.push({v, k + 1, dist[v][k + 1]});
                }
            }
        }
    }

    long long ans = INF;
    for (int i = 0; i <= k_limit; i++) ans = min(ans, dist[n][i]);
    cout << "Minimum Cost: " << ans << endl;
}

int main() {
    solve();
    return 0;
}
*/



/*
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<Edge>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue; // সেলফ লুপ ইগনোর করা হলো

        // আসল রাস্তা: খরচ ০
        adj[u].push_back({v, 0});
        // উল্টো রাস্তা: খরচ ১
        adj[v].push_back({u, 1});
    }

    // 0-1 BFS শুরু
    vector<int> dist(n + 1, INF);
    deque<int> dq;

    dist[1] = 0;
    dq.push_back(1);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                
                // যদি ওয়েট ০ হয় তবে সামনে পুশ (High Priority)
                // যদি ওয়েট ১ হয় তবে পেছনে পুশ (Low Priority)
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    if (dist[n] == INF) {
        cout << "-1" << endl; // গন্তব্যে পৌঁছানো অসম্ভব হলে
    } else {
        cout << "Minimum edges to reverse: " << dist[n] << endl;
    }
}

int main() {
    // ফাস্ট ইনপুট-আউটপুট
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}

*/