#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> weight = {1, 3, 4, 5};
    vector<int> value  = {1, 4, 5, 7};
    int W = 7; // capacity
    int n = weight.size();

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],  // don't take
                    value[i - 1] + dp[i - 1][w - weight[i - 1]] // take
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum Value = " << dp[n][W] << endl;
    return 0;
}
