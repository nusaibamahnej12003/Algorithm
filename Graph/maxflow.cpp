#include <bits/stdc++.h>
using namespace std;

#define V 100  // max vertices

// BFS to find augmenting path
bool bfs(int rGraph[V][V], int s, int t, int parent[], int n) {
    bool visited[V] = {false};
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Ford-Fulkerson using BFS (Edmonds-Karp)
int maxFlow(int graph[V][V], int s, int t, int n) {
    int rGraph[V][V]; // residual graph

    // copy graph to residual graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rGraph[i][j] = graph[i][j];

    int parent[V];
    int max_flow = 0;

    // while there is a path from source to sink
    while (bfs(rGraph, s, t, parent, n)) {

        int path_flow = INT_MAX;

        // find minimum capacity in the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual graph
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int n = 6; // number of vertices

    int graph[V][V] = {0};

    // Example graph (capacity)
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[2][1] = 4;
    graph[1][3] = 12;
    graph[3][2] = 9;
    graph[2][4] = 14;
    graph[4][3] = 7;
    graph[3][5] = 20;
    graph[4][5] = 4;

    int source = 0;
    int sink = 5;

    cout << "Maximum Flow = " << maxFlow(graph, source, sink, n) << endl;

    return 0;
}

/*

১. Multiple Sources & Multiple Sinks (সুপার সোর্স ও সুপার সিঙ্ক)
এখানে অনেকগুলো সোর্স এবং সিঙ্ক থাকবে। আমরা একটি এক্সট্রা Super Source (ধরি নোড N) এবং একটি Super Sink (ধরি নোড N+1) তৈরি করবো।
code
C++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int V = 105; 
int capacity[V][V];
int parent[V];

bool bfs(int s, int t, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && capacity[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int maxFlow(int s, int t, int n) {
    int flow = 0;
    while (bfs(s, t, n)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        flow += path_flow;
    }
    return flow;
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    int super_source = n;     // নতুন সোর্স
    int super_sink = n + 1;   // নতুন সিঙ্ক

    cout << "Enter edges (u v capacity):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, c; cin >> u >> v >> c;
        capacity[u][v] = c;
    }

    int num_sources, num_sinks;
    cout << "Enter number of sources: "; cin >> num_sources;
    cout << "Enter the sources: ";
    for (int i = 0; i < num_sources; i++) {
        int s; cin >> s;
        capacity[super_source][s] = INF; // সুপার সোর্স থেকে কানেকশন
    }

    cout << "Enter number of sinks: "; cin >> num_sinks;
    cout << "Enter the sinks: ";
    for (int i = 0; i < num_sinks; i++) {
        int t; cin >> t;
        capacity[t][super_sink] = INF; // সুপার সিঙ্কে কানেকশন
    }

    // এখন সুপার সোর্স থেকে সুপার সিঙ্কে ফ্লো চালাবো
    // টোটাল নোড সংখ্যা এখন n + 2
    cout << "\nMaximum Flow: " << maxFlow(super_source, super_sink, n + 2) << endl;

    return 0;
}
২. Node Capacities (নোড স্প্লিটিং ট্রিক)
যদি প্রতিটি নোডের নিজস্ব ক্ষমতা থাকে, তবে নোড 
u
u
-কে আমরা দুটি নোডে ভাগ করব: 
u
i
n
u 
in
​
 
 এবং 
u
o
u
t
u 
out
​
 
।
আমরা নোড 
u
u
-কে 
u
u
 নিজেই রাখবো (হবে 
u
i
n
u 
in
​
 
) এবং 
u
+
N
u+N
-কে ধরবো 
u
o
u
t
u 
out
​
 
। তাদের মাঝের ক্যাপাসিটি হবে নোডটির ক্ষমতা।
code
C++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int V = 205; // দ্বিগুণ নোড লাগবে
int capacity[V][V];
int parent[V];

bool bfs(int s, int t, int n) {
    vector<bool> visited(n, false);
    queue<int> q; q.push(s);
    visited[s] = true; parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && capacity[u][v] > 0) {
                q.push(v);
                parent[v] = u; visited[v] = true;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int maxFlow(int s, int t, int n) {
    int flow = 0;
    while (bfs(s, t, n)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            path_flow = min(path_flow, capacity[parent[v]][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        flow += path_flow;
    }
    return flow;
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    // নোড ক্যাপাসিটি ইনপুট
    cout << "Enter processing capacity for each node (0 to " << n-1 << "):" << endl;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        // i_in থেকে i_out এ এডজ (i এবং i + n)
        capacity[i][i + n] = c;
    }

    cout << "Enter edges (u v capacity):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, c; cin >> u >> v >> c;
        // u_out থেকে v_in এ কানেকশন (u + n থেকে v)
        capacity[u + n][v] = c;
    }

    int source, sink;
    cout << "Enter source and sink: ";
    cin >> source >> sink;

    // সোর্স শুরু হবে source + n থেকে নয়, source থেকে। 
    // সিঙ্ক শেষ হবে sink এ নয়, sink + n এ। (কনসেপ্ট অনুযায়ী)
    cout << "\nMaximum Flow with Node Capacities: " << maxFlow(source, sink + n, 2 * n) << endl;

    return 0;
}
৩. Minimum Cut (কাটা পাইপগুলো বের করা)
ম্যাক্স ফ্লো চালানোর পর আমরা সোর্স থেকে একটা সাধারণ BFS চালাবো রেসিডুয়াল গ্রাফে। যে নোডগুলো রিচেবল (Reachable) আর যেগুলো রিচেবল না, তাদের মধ্যবর্তী মূল এডজগুলোই হলো মিনিমাম কাট।
code
C++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int V = 100;
int capacity[V][V];
int original_capacity[V][V]; // আসল ধারণক্ষমতা সেভ রাখার জন্য
int parent[V];

bool bfs(int s, int t, int n) {
    vector<bool> visited(n, false);
    queue<int> q; q.push(s);
    visited[s] = true; parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && capacity[u][v] > 0) {
                q.push(v); parent[v] = u; visited[v] = true;
                if (v == t) return true;
            }
        }
    }
    return false;
}

// সোর্স থেকে সব রিচেবল নোড খোঁজার জন্য স্পেশাল DFS
void dfs(int s, int n, vector<bool>& visited) {
    visited[s] = true;
    for (int i = 0; i < n; i++) {
        if (capacity[s][i] > 0 && !visited[i]) {
            dfs(i, n, visited);
        }
    }
}

void minCut(int s, int t, int n) {
    // ১. ফ্লো বের করা
    while (bfs(s, t, n)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v])
            path_flow = min(path_flow, capacity[parent[v]][v]);
            
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
    }

    // ২. সোর্স থেকে রিচেবল নোডগুলো মার্ক করা
    vector<bool> visited(n, false);
    dfs(s, n, visited);

    // ৩. রিচেবল নোড থেকে নন-রিচেবল নোডের মূল এডজগুলো প্রিন্ট করা
    cout << "\nEdges in the Minimum Cut are:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i] && !visited[j] && original_capacity[i][j] > 0) {
                cout << i << " - " << j << " (Capacity: " << original_capacity[i][j] << ")" << endl;
            }
        }
    }
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    cout << "Enter edges (u v capacity):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, c; cin >> u >> v >> c;
        capacity[u][v] = c;
        original_capacity[u][v] = c; // ব্যাকআপ রাখা
    }

    int source, sink;
    cout << "Enter source and sink: ";
    cin >> source >> sink;

    minCut(source, sink, n);

    return 0;
}

*/