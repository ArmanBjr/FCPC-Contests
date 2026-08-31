// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 1 (First Contest)
// Problem : H
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

// Multi-test H-index.
// For each test, cap citations at N, count frequencies, then find the largest h
// with at least h papers having >= h citations via a suffix sum.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    vector<int> freq; // reused across tests
    while (T--) {
        int N;
        cin >> N;
        freq.assign(N + 1, 0);

        for (int i = 0; i < N; ++i) {
            long long x; // a_i can be up to 1e9
            cin >> x;
            if (x >= N) ++freq[N];
            else ++freq[(int)x];
        }

        int ans = 0, acc = 0;
        for (int h = N; h >= 1; --h) {
            acc += freq[h];
            if (acc >= h) { ans = h; break; }
        }
        cout << ans << '\n';
    }
    return 0;
}
