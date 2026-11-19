#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int c[N][N];     
vector<int> g[N];
int p[N];           

int bfs(int s, int t) {
    memset(p, -1, sizeof(p));
    p[s] = -2;

    queue<pair<int,int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for (int v : g[u]) {
            if (p[v] == -1 && c[u][v] > 0) {
                p[v] = u;
                int nf = min(f, c[u][v]);
                if (v == t) return nf;
                q.push({v, nf});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0, nf;

    while (nf = bfs(s, t)) {
        flow += nf;
        int cur = t;

        while (cur != s) {
            int prev = p[cur];
            c[prev][cur] -= nf;
            c[cur][prev] += nf;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    int n;

    while (cin >> n) {
        int s, t, e;
        cin >> s >> t >> e;

        memset(c, 0, sizeof(c));
        for (int i = 0; i < N; i++) g[i].clear();

        for (int i = 0; i < e; i++) {
            int u, v, w;
            cin >> u >> v >> w;

            c[u][v] += w;
            c[v][u] += w;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << "The bandwidth is " << maxflow(s, t) << endl;
    }
}
