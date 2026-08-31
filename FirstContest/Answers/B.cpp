// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 1 (First Contest)
// Problem : B
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    string best, w;
    int bestLen = -1;
    for (int i = 0; i < N; ++i) {
        cin >> w;
        int L = (int)w.size();
        if (L > bestLen) { bestLen = L; best = w; } // tie -> keep first
    }
    cout << best << '\n';
    return 0;
}
