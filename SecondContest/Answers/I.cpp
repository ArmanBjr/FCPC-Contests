// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : I
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

static inline bool is_digits(const string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s) if (!isdigit(c)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        char C; 
        string tok;
        cin >> C >> tok;

        bool startWhite = (C == 'W' || C == 'w');

        // Determine number of steps parity:
        bool odd;
        if (is_digits(tok)) {
            // Only parity matters; use last digit
            odd = ((tok.back() - '0') & 1);
        } else {
            // Treat token as move string; only its length parity matters
            odd = (tok.size() & 1);
        }

        bool finalWhite = startWhite ^ odd;
        cout << (finalWhite ? "SAFE" : "OHNO") << '\n';
    }
    return 0;
}
