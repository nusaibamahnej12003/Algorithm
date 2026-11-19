#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph;

    // Floyd-Warshall Algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Print result
    cout << "Shortest distances between every pair:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 4;
    vector<vector<int>> graph = {
        {0,   3,   INF, 7},
        {8,   0,   2,   INF},
        {5,   INF, 0,   1},
        {2,   INF, INF, 0}
    };

    floydWarshall(graph, V);

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int INF = 1e9;

void solve() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    // ১. অ্যাডজাসেন্সি ম্যাট্রিক্স ইনপুট
    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter the cost matrix (use " << INF << " for no connection):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            if (i == j) dist[i][j] = 0;
        }
    }

    // ২. কোন শহরটি বন্ধ হবে তা ইনপুট (১-বেসড ইনপুট নিলে ০-বেসড এ কনভার্ট করো)
    int shutCity;
    cout << "Enter the city number to be shut down (1 to " << n << "): ";
    cin >> shutCity;
    shutCity--; // ০-বেসড ইনডেক্সিং

    // ৩. Floyd-Warshall অ্যালগরিদম (Shutdown Logic সহ)
    for (int k = 0; k < n; k++) {
        // যদি intermediate node k বন্ধ থাকে, তবে এটি দিয়ে কোনো রাস্তা হবে না
        if (k == shutCity) continue;

        for (int i = 0; i < n; i++) {
            // যদি সোর্স শহর i বন্ধ থাকে, তবে এখান থেকে কোথাও যাওয়া যাবে না
            if (i == shutCity) continue;

            for (int j = 0; j < n; j++) {
                // যদি গন্তব্য শহর j বন্ধ থাকে, তবে এখানে আসা যাবে না
                if (j == shutCity) continue;

                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // ৪. রেজাল্ট প্রিন্ট
    cout << "\nUpdated Shortest Path Matrix after City " << shutCity + 1 << " shutdown:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == shutCity || j == shutCity) {
                cout << "X\t"; // বন্ধ শহরটি X দিয়ে দেখানো হলো
            } else if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    solve();
    return 0;
}
*/