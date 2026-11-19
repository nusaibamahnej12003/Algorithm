#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int discovery_time[MAXN], low_link[MAXN], timer;
bool visited[MAXN];
set<int> art_points; // ডুপ্লিকেট এড়াতে সেট ব্যবহার
vector<pair<int, int>> bridges;

void dfs(int u, int p = -1) {
    visited[u] = true;
    discovery_time[u] = low_link[u] = timer++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue; // প্যারেন্টে ফিরে যাবো না
        
        if (visited[v]) {
            // ব্যাক-এজ (Back-edge): অলরেডি ভিজিটেড মানেই এটি একটি লুপের অংশ
            low_link[u] = min(low_link[u], discovery_time[v]);
        } else {
            // নতুন নোড
            children++;
            dfs(v, u);
            low_link[u] = min(low_link[u], low_link[v]);

            // ১. ব্রিজ চেক করার শর্ত
            if (low_link[v] > discovery_time[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }

            // ২. আর্টিকুলেশন পয়েন্ট চেক করার শর্ত
            if (p != -1 && low_link[v] >= discovery_time[u]) {
                art_points.insert(u);
            }
        }
    }

    // স্পেশাল কেস: রুট নোড যদি আর্টিকুলেশন পয়েন্ট হয়
    if (p == -1 && children > 1) {
        art_points.insert(u);
    }
}

int main() {
    int n, m;
    cout << "Enter number of cities and roads: ";
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    timer = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
    }

    cout << "\n--- Result ---" << endl;
    cout << "Critical Cities (Articulation Points): ";
    for (int p : art_points) cout << p << " ";
    if (art_points.empty()) cout << "None";

    cout << "\nCritical Roads (Bridges):" << endl;
    if (bridges.empty()) cout << "None";
    for (auto& b : bridges) {
        cout << b.first << " -- " << b.second << endl;
    }

    return 0;
}