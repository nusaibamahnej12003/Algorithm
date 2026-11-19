#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int maxSoFar = arr[0];
    int currentSum = arr[0];

    int start = 0, end = 0, tempStart = 0;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > currentSum + arr[i]) {
            currentSum = arr[i];
            tempStart = i;
        } else {
            currentSum += arr[i];
        }

        if (currentSum > maxSoFar) {
            maxSoFar = currentSum;
            start = tempStart;
            end = i;
        }
    }

    cout << "Maximum Sum = " << maxSoFar << endl;
    cout << "Interval: ";
    for (int i = start; i <= end; i++)
        cout << arr[i] << " ";

    return 0;
}
