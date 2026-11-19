#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
int dista[20][20];
int dp[1<<15][15];

int tsp(int mask, int u){
    if(mask == (1<<n)-1)
        return dista[u][0];  // return home

    if(dp[mask][u] != -1) return dp[mask][u];

    int ans = INF;

    for(int v = 0; v < n; v++){
        if((mask & (1<<v)) == 0){
            ans = min(ans,
                      dista[u][v] +
                      tsp(mask | (1<<v), v));
        }
    }

    return dp[mask][u] = ans;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> dista[i][j];

    memset(dp, -1, sizeof(dp));
    cout << tsp(1, 0);  // start from city 0
}
/*

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int n;
int cost[21][21];
int dp[1 << 20]; // ২^২০ সাইজের টেবিল

// mask: কোন কোন টাস্ক অ্যাসাইন করা হয়ে গেছে তার বাইনারি রিপ্রেজেন্টেশন
// mask = 5 (বাইনারি 101) মানে টাস্ক ০ এবং টাস্ক ২ অ্যাসাইন করা হয়েছে
int solve(int agent, int mask) {
    // বেস কেস: সব এজেন্টকে টাস্ক দেওয়া হয়ে গেলে খরচ ০
    if (agent == n) {
        return 0;
    }

    // মেমোইজেশন: যদি এই স্টেট আগে ক্যালকুলেট করা থাকে
    if (dp[mask] != -1) {
        return dp[mask];
    }

    int min_cost = INF;

    // বর্তমান এজেন্টের জন্য সব টাস্ক চেক করা
    for (int task = 0; task < n; task++) {
        // যদি ওই টাস্কটি আগে কাউকে দেওয়া না হয়ে থাকে (Bitmask check)
        if (!(mask & (1 << task))) {
            // টাস্কটি দিয়ে পরবর্তী এজেন্টের জন্য কল করা
            int res = cost[agent][task] + solve(agent + 1, mask | (1 << task));
            min_cost = min(min_cost, res);
        }
    }

    return dp[mask] = min_cost;
}

int main() {
    cout << "Enter the number of agents/tasks (N): ";
    cin >> n;

    cout << "Enter the cost matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // DP টেবিল -১ দিয়ে ইনিশিয়ালাইজ করা
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = -1;
    }

    cout << "\nMinimum total cost to assign all tasks: " << solve(0, 0) << endl;

    return 0;
}
*/