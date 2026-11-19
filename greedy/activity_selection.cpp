#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish;
};

bool compare(Activity a, Activity b) {
    return a.finish < b.finish;
}

int main() {
    vector<Activity> arr = {{1,2},{3,4},{0,6},{5,7},{8,9},{5,9}};

    sort(arr.begin(), arr.end(), compare);

    cout << "Selected Activities:\n";

    int lastFinish = arr[0].finish;
    cout << arr[0].start << " " << arr[0].finish << endl;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].start >= lastFinish) {
            cout << arr[i].start << " " << arr[i].finish << endl;
            lastFinish = arr[i].finish;
        }
    }
}
