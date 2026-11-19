#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        int total = n * (n + 1) / 2;
        vector<double> b(total);
        int k = -1;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int l = j + 1;
                b[++k] = (double) accumulate(arr.begin() + i, arr.begin() + l, 0) / (j - i + 1);
            }
        }

        double mx = b[0];
        for (int i = 1; i <= k; i++) {
            if (b[i] > mx) mx = b[i];
        }

        cout << fixed << setprecision(0) << mx << endl;
    }
}
