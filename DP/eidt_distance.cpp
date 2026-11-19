#include <iostream>
#include <vector>
using namespace std;

int editDistance(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Base cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;  // delete all characters

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;  // insert all characters

    // Fill table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (s1[i - 1] == s2[j - 1]) {
                // Characters match → no operation
                dp[i][j] = dp[i - 1][j - 1];
            } else {
               dp[i][j] = 1 + min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;

    cout << "Enter second string: ";
    cin >> str2;

    int result = editDistance(str1, str2);

    cout << "Minimum Edit Distance = " << result << endl;

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void weightedEditDistance(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // Operation Costs
    const int INS_COST = 2;
    const int DEL_COST = 3;
    const int REP_COST = 4;

    // DP Table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i * DEL_COST; 
    for (int j = 0; j <= n; j++) dp[0][j] = j * INS_COST;

    // Filling the DP Table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No cost if characters match
            } else {
                int del = dp[i - 1][j] + DEL_COST;
                int ins = dp[i][j - 1] + INS_COST;
                int rep = dp[i - 1][j - 1] + REP_COST;

                dp[i][j] = min({del, ins, rep});
            }
        }
    }

    cout << "------------------------------------" << endl;
    cout << "Minimum Transformation Cost: " << dp[m][n] << endl;
    cout << "------------------------------------" << endl;

    // Backtracking to find steps
    cout << "Steps to transform '" << s1 << "' to '" << s2 << "':" << endl;
    int i = m, j = n;
    vector<string> steps;

    while (i > 0 || j > 0) {
        // If characters match, just move diagonally
        if (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]) {
            i--; j--;
        } 
        // Check if it was a Replacement
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + REP_COST) {
            steps.push_back("Replace '" + string(1, s1[i - 1]) + "' with '" + string(1, s2[j - 1]) + "' (Cost: 4)");
            i--; j--;
        } 
        // Check if it was a Deletion
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + DEL_COST) {
            steps.push_back("Delete '" + string(1, s1[i - 1]) + "' (Cost: 3)");
            i--;
        } 
        // Check if it was an Insertion
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + INS_COST) {
            steps.push_back("Insert '" + string(1, s2[j - 1]) + "' (Cost: 2)");
            j--;
        }
    }

    // Steps were collected backwards, so reverse them
    reverse(steps.begin(), steps.end());
    for (const string& step : steps) {
        cout << "- " << step << endl;
    }
}

int main() {
    string A, B;
    cout << "Enter source string (A): ";
    cin >> A;
    cout << "Enter target string (B): ";
    cin >> B;

    weightedEditDistance(A, B);

    return 0;
}
*/