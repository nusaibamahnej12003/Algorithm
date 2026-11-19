#include <bits/stdc++.h>
using namespace std;

string s1, s2;
int dp[1005][1005]; 

int lcs(int i, int j) {
    if (i == s1.size() || j == s2.size()) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    if (s1[i] == s2[j])
        return dp[i][j] =1+lcs(i+1, j + 1);
    else
        return dp[i][j] = max(lcs(i+1,j), lcs(i,j+1));
}

string readfile(const string &filename) {
    ifstream file(filename);
    string line, data;
    while (getline(file, line)) {
        data += line + "\n";
    }
    return data;
}

int main() {
    memset(dp, -1, sizeof(dp));

    s1 = readfile("string1.txt");
    s2 = readfile("string2.txt");

    int ans = lcs(0, 0);

    ofstream out("output.txt");
    out << "Length of LCS: " << ans << endl;

    cout << "LCS length = " << ans  << endl;
    return 0;
}
/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void lcsString(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // DP টেবিল তৈরি
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // টেবিল ফিল করা
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "Length of LCS: " << dp[m][n] << endl;

    // ব্যাকট্র্যাকিং করে স্ট্রিংটি বের করা
    string lcs_str = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_str += s1[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs_str.begin(), lcs_str.end());
    cout << "Actual LCS: " << lcs_str << endl;
}

int main() {
    string s1, s2;
    cout << "Enter first string: "; cin >> s1;
    cout << "Enter second string: "; cin >> s2;
    lcsString(s1, s2);
    return 0;
}
*/



/*

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void lcsNumbers(vector<int>& v1, vector<int>& v2) {
    int m = v1.size();
    int n = v2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (v1[i - 1] == v2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "\nLength of LCS (Numbers): " << dp[m][n] << endl;

    // ব্যাকট্র্যাকিং করে সংখ্যার সিকোয়েন্স বের করা
    vector<int> lcs_seq;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (v1[i - 1] == v2[j - 1]) {
            lcs_seq.push_back(v1[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs_seq.begin(), lcs_seq.end());

    cout << "Actual Sequence: ";
    for (int x : lcs_seq) cout << x << " ";
    cout << endl;
}

int main() {
    int m, n;
    cout << "Enter size of 1st sequence: "; cin >> m;
    vector<int> v1(m);
    for (int i = 0; i < m; i++) cin >> v1[i];

    cout << "Enter size of 2nd sequence: "; cin >> n;
    vector<int> v2(n);
    for (int i = 0; i < n; i++) cin >> v2[i];

    lcsNumbers(v1, v2);
    return 0;
}

*/


/*
   kotogula delete korte hobe?

    #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getLCSLength(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // DP Table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

void solve() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int lcs_len = getLCSLength(s1, s2);
    
    int deletions_s1 = s1.length() - lcs_len;
    int deletions_s2 = s2.length() - lcs_len;
    int total_deletions = deletions_s1 + deletions_s2;

    cout << "\n--- Result ---" << endl;
    cout << "Length of Longest Common Subsequence: " << lcs_len << endl;
    cout << "Deletions needed from '" << s1 << "': " << deletions_s1 << endl;
    cout << "Deletions needed from '" << s2 << "': " << deletions_s2 << endl;
    cout << "Total minimum deletions required: " << total_deletions << endl;
}

int main() {
    solve();
    return 0;
}
*/