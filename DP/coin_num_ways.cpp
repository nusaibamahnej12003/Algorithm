#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;

    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }

    cout << "Number of ways = " << dp[amount];
    return 0;
}
