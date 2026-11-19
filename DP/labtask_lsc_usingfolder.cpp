#include <bits/stdc++.h>
using namespace std;


int lcsLength(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

string readFile(const string &filename) {
    ifstream file(filename);
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return text;
}

int main() {
    string myfile = "myfile.txt";
    string folderList = "stringfolder"; 
    string s1 = readFile(myfile);

    ifstream list(folderList);
    string filename;
    int maxLCS = -1;
    string bestFile;

    while (getline(list, filename)) {
        string s2 = readFile(filename);
        int len = lcsLength(s1, s2);
        cout << "Compared with: " << filename << " → LCS length = " << len << endl;

        if (len > maxLCS) {
            maxLCS = len;
            bestFile = filename;
        }
    }

    ofstream out("output.txt");
    out << "Best match file: " << bestFile << "\n";
    out << "Maximum LCS length: " << maxLCS << "\n";
    out.close();

    cout << "\nBest file: " << bestFile << " | LCS length = " << maxLCS << endl;
    return 0;
}
