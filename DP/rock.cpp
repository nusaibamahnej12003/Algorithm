#include <bits/stdc++.h>
using namespace std;

const int M = 4, N = 5;
int arr[M][N];
int dp[M][N];

int rock(int m, int n)
{
  
    if (n < 0 || n >= N) return 1e9; 


    if (m == 0) return arr[0][n];

    
    if (dp[m][n] != -1) return dp[m][n];

    int up       = rock(m - 1, n);
    int up_left  = rock(m - 1, n - 1);
    int up_right = rock(m - 1, n + 1);

    return dp[m][n] = arr[m][n] + min({up, up_left, up_right});
}

int main()
{
    memset(dp, -1, sizeof(dp));

    // input
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> arr[i][j];

    // compute all results for last row
    for (int j = 0; j < N; j++)
        cout << rock(M - 1, j) << endl;

    return 0;
}
