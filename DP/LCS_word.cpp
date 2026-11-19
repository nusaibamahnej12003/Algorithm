#include<bits/stdc++.h>

using namespace std;
vector<string> tokenize(const string& line)
{
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> readAllWords(const string& filename)
{
    vector<string> allWords;
    ifstream in(filename);
    if (!in) {
        cerr << "Cannot open " << filename << endl;
        return allWords;             
    }

    string line;
    while (getline(in, line)) {     
        vector<string> words = tokenize(line);
        allWords.insert(allWords.end(), words.begin(), words.end());
    }
    return allWords;
}

int lcs(const vector<string>& v1,const vector<string>& v2,vector<string>& lcs)
{
    int m = v1.size();
    int n = v2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (v1[i-1] == v2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

  
    vector<string> seq;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (v1[i-1] == v2[j-1]) {
            seq.push_back(v1[i-1]);
            --i; --j;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(seq.begin(), seq.end());
    lcs = seq;

    return dp[m][n];
}


int main()
{
    const string file1_name = "file1.txt";
    const string file2_name = "file2.txt";
    const string output_name = "output.txt";


    vector<string> words1 = readAllWords(file1_name);
    vector<string> words2 = readAllWords(file2_name);

    if (words1.empty() || words2.empty()) {
        cerr << "One of the files is empty or could not be read.\n";
        return 1;
    }


    vector<string> commonWords;
    int len = lcs(words1, words2, commonWords);


    ofstream out(output_name);
    if (!out) {
        cerr << "Cannot create " << output_name << endl;
        return 1;
    }

    out << len;
    if (!commonWords.empty()) {
        out << " (";
        for (size_t k = 0; k < commonWords.size(); ++k) {
            if (k) out << " ";
            out << commonWords[k];
        }
        out << ")";
    }
    out << endl;


    cout << "LCS length: " << len << "\nLCS words: ";
    for (size_t k = 0; k < commonWords.size(); ++k) {
        if (k) cout << " ";
        cout << commonWords[k];
    }
    cout << endl;

    return 0;
}