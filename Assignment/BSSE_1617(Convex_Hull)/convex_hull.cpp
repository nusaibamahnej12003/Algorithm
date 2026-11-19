#include <bits/stdc++.h>
using namespace std;

struct Pt {
    int x, y;
};

Pt p0; 

int ot(Pt p, Pt q, Pt r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

int dis(Pt p1, Pt p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

bool compare(Pt p1, Pt p2) {
    int o = ot(p0, p1, p2);

    if (o == 0)
        return dis(p0, p1) < dis(p0, p2);

    return (o == 2);
}

vector<Pt> GrahamScan(vector<Pt>& p) {
    int n = p.size();
    if (n < 3) return p;

    int minIndex = 0;
    int minY = p[0].y;
    for (int i = 1; i < n; i++) {
        if ((p[i].y < minY) || (p[i].y == minY && p[i].x < p[minIndex].x)) {
            minY = p[i].y;
            minIndex = i;
        }
    }

    swap(p[0], p[minIndex]);
    p0 = p[0];

    sort(p.begin() + 1, p.end(), compare);

    vector<Pt> S;
    S.push_back(p[0]);
    S.push_back(p[1]);

    for (int i = 2; i < n; i++) {
        while (S.size() > 1 &&
               ot(S[S.size()-2],
                           S[S.size()-1],
                           p[i]) != 2) {
            S.pop_back();
        }
        S.push_back(p[i]);
    }

    return S;
}

int main() {

    vector<Pt> p = {
        {1, 2}, {2, 5}, {3, 3},
        {5, 3}, {4, 1}, {2, 1},
        {0, 3}, {3, 0}
    };

    vector<Pt> hull = GrahamScan(p);

    cout << "The points are:\n";
    for (auto pt : hull) {
        cout << "(" << pt.x << ", " << pt.y << ")\n";
    }

    return 0;
}