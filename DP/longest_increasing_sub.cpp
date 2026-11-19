#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = arr.size();

    vector<int> dp(n, 1);  // each element alone = length 1

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int lis = *max_element(dp.begin(), dp.end());
    cout << "Length of LIS = " << lis << endl;

    return 0;
}
