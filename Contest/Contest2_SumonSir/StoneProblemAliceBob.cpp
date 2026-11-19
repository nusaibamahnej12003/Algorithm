#include <bits/stdc++.h>
using namespace std;

// Recursive function returns true if current player can win
bool canWin(int x, int y, int lastMove) {
    // Try all possible moves (more than lastMove) on either pile
    for (int take = lastMove + 1; take <= max(x, y); ++take) {
        // Try taking from X
        if (x >= take && !canWin(x - take, y, take))
            return true;
        // Try taking from Y
        if (y >= take && !canWin(x, y - take, take))
            return true;
    }
    return false; // No move leads to a win
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x, y, k;
        cin >> x >> y >> k;

        bool aliceWins = false;

        // Try all possible initial moves for Alice: 1 to k
        for (int first = 1; first <= k; ++first) {
            // Try taking from X
            if (x >= first && !canWin(x - first, y, first)) {
                aliceWins = true;
                break;
            }
            // Try taking from Y
            if (y >= first && !canWin(x, y - first, first)) {
                aliceWins = true;
                break;
            }
        }

        cout << (aliceWins ? "Alice" : "Bob") << endl;
    }
    return 0;
}
