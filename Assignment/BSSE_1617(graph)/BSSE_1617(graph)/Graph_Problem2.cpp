#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
const int INF = 1e7;

int main() {
    int u, v, caseNum = 1;

  
    while (cin >> u >> v && (u != 0 || v != 0)) {
        int d[101][101];
        bool e[101] = {false};
        for (int i = 1; i <= 100; i++) {
            for (int j = 1; j <= 100; j++) {
                if (i == j) d[i][j] = 0;
                else d[i][j] = INF;
            }
        }

        d[u][v] = 1;
        e[u] = e[v] = true;
        while (cin >> u >> v && (u != 0 || v != 0)) {
            d[u][v] = 1;
            e[u] = e[v] = true;
        }
        for (int k = 1; k <= 100; k++) {
            if (!e[k]) continue; 
            for (int i = 1; i <= 100; i++) {
                if (!e[i]) continue;
                for (int j = 1; j <= 100; j++) {
                    if (!e[j]) continue;
                    
                    if (d[i][k] + d[k][j] < d[i][j])
                     {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }
        double sum = 0;
        int pair = 0;
        for (int i = 1; i <= 100; i++) {
            for (int j = 1; j <= 100; j++) {
                if (e[i] && e[j] && i != j) 
                {
                    sum += d[i][j];
                    pair++;
                }
            }
        }

        
        double average = sum / pair;
        cout << "Case " << caseNum++ << ": average length between pages = " 
             << fixed << setprecision(3) << average << " clicks" << endl;
    }
}
