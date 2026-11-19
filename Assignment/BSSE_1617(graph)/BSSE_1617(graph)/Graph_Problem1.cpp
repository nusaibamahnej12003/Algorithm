#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int main() {
    int caseNum = 1;
    while (true) {
        int C, S, Q;
        cin >> C >> S >> Q;
        if (C == 0 && S == 0 && Q == 0) break;

        vector<vector<int>> dist(C + 1, vector<int>(C + 1, INF));


        for (int i = 1; i <= C; i++) dist[i][i] = 0;

        for (int i = 0; i < S; i++) {
            int u, v, d;
            cin >> u >> v >> d;
            if (d < dist[u][v]) {
                dist[u][v] = dist[v][u] = d;
            }
        }
        for (int k = 1; k <= C; k++) {
            for (int i = 1; i <= C; i++) {
                for (int j = 1; j <= C; j++) {
                    dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
                }
            }
        }
        if (caseNum > 1) cout << "\n";
        cout << "Case #" << caseNum++ << "\n";

        for (int i = 0; i < Q; i++) {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] == INF)
                cout << "no path\n";
            else
                cout << dist[u][v] << "\n";
        }
    }

    return 0;
}
