#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(int V, vector<vector<int>>& adj) {
    vector<int> color(V, -1); // -1 = not colored

    for (int start = 0; start < V; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == color[node]) {
                        return false; // not bipartite
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int V = 4;
    vector<vector<int>> adj = {
        {1, 3},   // 0
        {0, 2},   // 1
        {1, 3},   // 2
        {0, 2}    // 3
    };

    if (isBipartite(V, adj))
        cout << "Graph is Bipartite\n";
    else
        cout << "Graph is NOT Bipartite\n";

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void findMinimumColors(int n, vector<vector<int>>& adj) {
    // প্রতিটি নোডের রঙ জমা রাখার জন্য অ্যারে (শুরুতে -১ মানে কোনো রঙ নেই)
    vector<int> result(n, -1);

    // প্রথম নোডকে ০ নম্বর রঙ দিয়ে শুরু করি
    result[0] = 0;

    // বাকি নোডগুলোর জন্য রঙ নির্ধারণ
    // available[i] = false মানে রঙ i বর্তমানে কোনো প্রতিবেশী ব্যবহার করছে
    vector<bool> available(n, true);

    for (int u = 1; u < n; u++) {
        // ১. প্রতিবেশীদের রঙ চেক করা
        for (int v : adj[u]) {
            if (result[v] != -1) {
                available[result[v]] = false;
            }
        }

        // ২. সবচেয়ে ছোট যে রঙটি এখন এভেইলএবল সেটি খুঁজে বের করা
        int cr;
        for (cr = 0; cr < n; cr++) {
            if (available[cr]) break;
        }

        result[u] = cr; // নোড u-কে রঙ cr দেওয়া হলো

        // ৩. পরবর্তী নোডের জন্য এভেইলএবল লিস্ট রিসেট করা
        for (int v : adj[u]) {
            if (result[v] != -1) {
                available[result[v]] = true;
            }
        }
    }

    // ৪. টোটাল কয়টি ইউনিক রঙ ব্যবহৃত হয়েছে তা বের করা
    int max_color = 0;
    for (int i = 0; i < n; i++) {
        if (result[i] > max_color) max_color = result[i];
    }

    int min_colors = max_color + 1; // যেহেতু ০ থেকে শুরু হয়েছে

    cout << "\nMinimum colors required (Approx): " << min_colors << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " ---> Color " << result[i] << endl;
    }

    // Bipartite চেক
    if (min_colors == 2) {
        cout << "Since exactly 2 colors are used, this graph is Bipartite." << endl;
    } else if (min_colors == 1) {
        cout << "Only 1 color used (No edges in the graph)." << endl;
    } else {
        cout << "The graph is NOT Bipartite because it needs " << min_colors << " colors." << endl;
    }
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<int>> adj(n);
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findMinimumColors(n, adj);

    return 0;
}
*/