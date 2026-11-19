#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

void solve() {
    int n, e;
    cout << "Enter number of courses: ";
    cin >> n;
    cout << "Enter number of dependency rules: ";
    cin >> e;

    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0);
    map<int, string> courseName;

    cout << "Enter course names (ID and Name, e.g., 0 SPL):" << endl;
    for (int i = 0; i < n; i++) {
        int id;
        string name;
        cin >> id >> name;
        courseName[id] = name;
    }

    cout << "Enter dependencies (Pre-req_ID -> Target_ID):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    queue<int> q;
    // শুরুতে যে কোর্সগুলোর কোনো প্রি-রিকুইজিট নেই
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int semester = 1;
    int processed_courses = 0;

    cout << "\n--- Semester-wise Course Plan ---" << endl;

    while (!q.empty()) {
        int courses_this_semester = q.size();
        cout << "Semester " << semester++ << ": ";

        // এই সেমিস্টারের সবগুলো কোর্স একসাথে প্রসেস করা
        for (int i = 0; i < courses_this_semester; i++) {
            int u = q.front();
            q.pop();
            cout << courseName[u] << " ";
            processed_courses++;

            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    // সাইকেল চেক
    if (processed_courses != n) {
        cout << "\nError: Circular dependency detected! Cannot complete all courses." << endl;
    }
}

int main() {
    solve();
    return 0;
}