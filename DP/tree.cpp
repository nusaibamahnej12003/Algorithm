#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int val[100005];
long long dp[100005][2];

void dfs(int u, int parent){
    dp[u][1] = val[u];

    for(int v : g[u]){
        if(v == parent) continue;

        dfs(v, u);

        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main(){
    int n;
    cin >> n;

    for(int i=1;i<=n;i++) cin >> val[i];

    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    cout << max(dp[1][0], dp[1][1]);
}
