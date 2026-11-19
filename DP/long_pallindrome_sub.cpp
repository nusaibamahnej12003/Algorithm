#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s = "bbbab";
    int n = s.length();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: single letters
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    // Fill table
    for (int len = 2; len <= n; len++) { 
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;

            if (s[i] == s[j]) {
                if (len == 2)
                    dp[i][j] = 2;
                else
                    dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "Length of Longest Palindromic Subsequence = " << dp[0][n - 1];
    return 0;
}
