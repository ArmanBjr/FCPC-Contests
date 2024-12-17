//FCPC S.1 2024 C
#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int sign(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int ccw(const pii& a, const pii& b, const pii& c) {
    return sign((ll)a.fi * (b.se - c.se) +
                (ll)b.fi * (c.se - a.se) +
                (ll)c.fi * (a.se - b.se));
}


bool intersect(const pii& a, const pii& b, const pii& c, const pii& d) {
    if (a == b || a == c || a == d || b == c || b == d || c == d) return false;
    return ccw(a, b, c) != ccw(a, b, d) && ccw(c, d, a) != ccw(c, d, b);
}


int n;
vector<pii> pts;

int ccw(int i, int j, int k) {
    return ccw(pts[i], pts[j], pts[k]);
}

bool intersect(int i, int j, int k, int l) {
    return intersect(pts[i], pts[j], pts[k], pts[l]);
}


int cmp_center;
bool cmp(int i, int j) {
    return ccw(cmp_center, i, j) == 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    pts.resize(n);
    for (auto& it : pts) cin >> it.fi >> it.se;

    vector<pii> edges;
    set<vi> triangles;

    sort(pts.begin(), pts.end());
    vector<bool> on_hull(n);
    int last = 0;
    do {
        on_hull[last] = true;

        int nxt = 0;
        if (last == 0) nxt = 1;

        for (int i = 0; i < n; i++)
            if (ccw(last, nxt, i) == 1)
                nxt = i;

        edges.push_back({last, nxt});
        if (last != 0 && nxt != 0)
            triangles.insert({0, nxt, last});

        last = nxt;
    } while (last != 0);

    for (int i = 0; i < n; i++) {
        if (on_hull[i]) continue;

        vi tr;
        for (auto& it : triangles)
            if (ccw(it[0], it[1], i) == 1 &&
                ccw(it[1], it[2], i) == 1 &&
                ccw(it[2], it[0], i) == 1) {
                tr = it;
                break;
            }

        assert(!tr.empty());
        triangles.erase(tr);
        triangles.insert({tr[0], tr[1], i});
        triangles.insert({tr[1], tr[2], i});
        triangles.insert({tr[2], tr[0], i});

        edges.push_back({i, tr[0]});
        edges.push_back({i, tr[1]});
        edges.push_back({i, tr[2]});
    }

    int sol = 0;
    for (auto& edg : edges) {
        int p = edg.fi, q = edg.se;
        vi a, b;
        for (int i = 0; i < n; i++) {
            if (ccw(p, q, i) == -1) a.push_back(i);
            if (ccw(p, q, i) == +1) b.push_back(i);
        }

        cmp_center = p;
        sort(a.begin(), a.end(), cmp);
        sort(b.begin(), b.end(), cmp);

        vi c = b;
        cmp_center = q;
        sort(c.begin(), c.end(), cmp);
        vi pos(n);
        for (int i = 0; i < (int)c.size(); i++) pos[c[i]] = i;

        bool ok = true;
        int j = 0, k = -1;
        for (int i = 0; i < (int)a.size(); i++) {
            while (j < (int)b.size() && ccw(a[i], p, b[j]) == -1) {
                k = max(k, pos[b[j]]);
                j++;
            }

            if (k != -1)
                ok &= !intersect(p, q, a[i], c[k]);
        }

        if (ok) sol++;
    }

    cout << sol << '\n';

    return 0;
}

