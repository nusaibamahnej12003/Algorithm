#include<bits/stdc++.h>
using namespace std;

int ST(int V,vector<vector<int>> adj[])
{
    priority_queue<pair<int,pair<int,int>> , vector<pair<int,pair<int,int>>> , greater<pair<int,pair<int,int>>>> pq ;

    vector<bool> visited(V,false);
    int result = 0;
    pq.push({0,{0,-1}});//weight,child,parent
    int parent_vertex=0;

    while(!pq.empty())
    {
        auto  p = pq.top();
        pq.pop();
        int wt=p.first;
        int child_vertex = p.second.first;
        parent_vertex=p.second.second;

        if(visited[child_vertex])continue;
        result += wt;
        visited[child_vertex]=true;
        cout<<parent_vertex<<"-->"<<child_vertex<<" = "<<wt<<endl;

         for(auto &v:adj[child_vertex])
         {
            int weight=v[1];
            int adj_of_child=v[0];
            if(!visited[v[0]])
            {
                pq.push({weight,{adj_of_child , child_vertex}});
            }
         }
    }
return result;

}

int main()
{
    
    int V;
    cout<<"Total vetices = ";
    cin>>V;
    vector<vector<int>> adj[V];
    for(int i=0;i<V;i++)
    {
        int x,y;
        cout<<"If there is no adjacent vertex type -1"<<endl;
        while(1)
        {
            cout<<"Enter adjacency vertex of "<<i<<": ";
            cin>>x;
            if(x==-1)break;
            cout<<"Enter corresponding weight : ";
            cin>>y;
            cout<<endl;
            adj[i].push_back({x,y});
        }
    }
cout<<ST(V,adj)<<endl;
return 0;

}
/*
* normal priority queue = Priority_queue<int>
                        = Priority_queue<pair<int,int>>(2 ta value)
                        = Priority_queue<pair<int,pair<int,int>>>(3 ta value)
 if wanna store in array/container
                        =Priority_queue<pair<int,pair<int,int>> ,vector<pair<int,pair<int,int>>>(3 ta value)

*/

/*

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

// শহরের স্থানাঙ্ক রাখার জন্য স্ট্রাকচার
struct Point {
    int id;
    double x, y;
};

// দুটি শহরের মধ্যবর্তী দূরত্ব (ইউক্লিডীয় দূরত্ব) বের করার ফাংশন
double calculateDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void solve() {
    int n, existing_bridges;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<Point> cities(n);
    cout << "Enter coordinates (x y) for each city:" << endl;
    for (int i = 0; i < n; i++) {
        cities[i].id = i;
        cin >> cities[i].x >> cities[i].y;
    }

    // এডজাসেন্সি লিস্ট (শহর, খরচ)
    // যেহেতু সব শহর সবার সাথে কানেক্ট হতে পারে, তাই এটি একটি কমপ্লিট গ্রাফ
    vector<vector<pair<int, double>>> adj(n);

    // ১. সব শহরের মধ্যে দূরত্বের এডজাসেন্সি লিস্ট তৈরি
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = calculateDistance(cities[i], cities[j]);
            adj[i].push_back({j, d});
            adj[j].push_back({i, d});
        }
    }

    // ২. বিদ্যমান ব্রিজের জন্য খরচ ০ করে দেওয়া
    cout << "Enter number of existing bridges: ";
    cin >> existing_bridges;
    cout << "Enter the pairs of cities already connected (e.g., 1 2):" << endl;
    for (int i = 0; i < existing_bridges; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // ০-বেসড ইনডেক্সিং করার জন্য
        adj[u].push_back({v, 0.0});
        adj[v].push_back({u, 0.0});
    }

    // ৩. প্রিমস অ্যালগরিদম শুরু
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    vector<double> min_cost(n, 1e18); // ইনফিনিটি
    vector<bool> inMST(n, false);
    vector<int> parent(n, -1);

    double total_mst_weight = 0;
    
    // শুরু করছি শহর ০ থেকে
    pq.push({0.0, 0});
    min_cost[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        double w = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        total_mst_weight += w;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            double weight = edge.second;

            if (!inMST[v] && weight < min_cost[v]) {
                min_cost[v] = weight;
                pq.push({min_cost[v], v});
                parent[v] = u;
            }
        }
    }

    // আউটপুট
    cout << fixed << setprecision(2);
    cout << "\nMinimum additional cost needed: " << total_mst_weight << endl;
    
    cout << "New connections to be built:" << endl;
    for (int i = 1; i < n; i++) {
        // যদি খরচ ০ এর বেশি হয়, তবেই সেটা নতুন ব্রিজ
        // এখানে সরাসরি কানেক্টেড ব্রিজের প্যারেন্টগুলোও দেখাবে
        if (parent[i] != -1) {
             // আমরা শুধু সেগুলোই দেখাবো যারা আগে থেকে কানেক্টেড ছিল না
             // এটা অপশনাল, প্রশ্নের চাহিদা অনুযায়ী দিবে
             cout << "City " << parent[i] + 1 << " - City " << i + 1 << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}

*/