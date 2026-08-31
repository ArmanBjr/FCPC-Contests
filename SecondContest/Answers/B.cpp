// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : B
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

// Champion in this knockout format is the unique team that wins 4 matches.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        unordered_map<string,int> wins;
        wins.reserve(128); wins.max_load_factor(0.7f);

        for (int i = 0; i < 16; ++i) {
            string a, b; int g1, g2;
            cin >> a >> b >> g1 >> g2;
            if (g1 > g2) ++wins[a];
            else         ++wins[b];
        }

        // Champion is the one with exactly 4 wins.
        string champ;
        for (auto &kv : wins) {
            if (kv.second == 4) { champ = kv.first; break; }
        }
        // Safety: if malformed input, fall back to max wins (shouldn't happen per statement).
        if (champ.empty()) {
            champ = max_element(wins.begin(), wins.end(),
                                [](const auto& x, const auto& y){ return x.second < y.second; })->first;
        }
        cout << champ << '\n';
    }
    return 0;
}
