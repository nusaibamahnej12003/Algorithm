#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

double d[12][12];    
double dp[505][12][12];
string s;

void pre() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            int r1 = i / 3, c1 = i % 3;
            int r2 = j / 3, c2 = j % 3;
            double x = sqrt(pow(r1 - r2, 2) + pow(c1 - c2, 2));
            d[i][j] = round(x * 2.0) / 2.0;
        }
    }
}

int id(char c) {
    if (c == '0') return 10;
    if (c == '*') return 9;
    if (c == '#') return 11;
    return c - '1';
}


double go(int i, int a, int b) {
    if (i == s.length()) return 0;
    if (dp[i][a][b] != -1) return dp[i][a][b];

    int t = id(s[i]);

    double x = d[a][t] + go(i + 1, t, b);
    double y = d[b][t] + go(i + 1, a, t);

    return dp[i][a][b] = min(x, y);
}

int main() {
    pre();
    s = "123456";

    for (int i = 0; i < 505; i++)
        for (int j = 0; j < 12; j++)
            for (int k = 0; k < 12; k++)
                dp[i][j][k] = -1;

    double ans = go(0, 9, 11);

    cout << "Minimum effort: " << fixed << setprecision(1) << ans << endl;
    return 0;
}
