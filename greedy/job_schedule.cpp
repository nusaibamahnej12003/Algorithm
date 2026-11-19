#include <iostream>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    Job arr[] = {{'A',2,100},{'B',1,19},{'C',2,27},{'D',1,25},{'E',3,15}};
    int n = 5;

    sort(arr, arr+n, cmp);

    int result[3] = {0};  // max deadline = 3
    bool slot[3] = {false};

    for (int i = 0; i < n; i++) {
        for (int j = arr[i].deadline - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = i;
                slot[j] = true;
                break;
            }
        }
    }

    cout << "Jobs done: ";
    for (int i = 0; i < 3; i++)
        if (slot[i])
            cout << arr[result[i]].id << " ";
}
