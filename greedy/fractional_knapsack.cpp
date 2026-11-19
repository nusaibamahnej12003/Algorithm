#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

int main() {
    vector<Item> arr = {{60,10},{100,20},{120,30}};
    int W = 50;

    sort(arr.begin(), arr.end(), cmp);

    double totalValue = 0.0;

    for (auto item : arr) {
        if (W >= item.weight) {
            W -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            break;
        }
    }

    cout << "Maximum value = " << totalValue;
}
