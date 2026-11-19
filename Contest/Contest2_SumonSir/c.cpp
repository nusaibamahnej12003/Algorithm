#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int min(int m, const string& a) {
    unordered_map<char, int> count;
    for (char c : a) {
        count[c]++;
    }

    string real = "ABCDEFG";
    int ans = 0;

    for (char r: real) {
        int have = count[r];
        int need = max(0, m - have);
        ans += need;
    }

    return ans;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        string a;
        cin >> n >> m >> a;

        cout << min(m, a) << endl;
    }

    return 0;
}
