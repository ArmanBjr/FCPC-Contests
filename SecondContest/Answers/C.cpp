// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : C
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

// Among Us: Height Check (float version)
// SUCCESSFUL if non-decreasing; otherwise SUSSYBAKA.
// Reads t test cases; each has n then n floats 0..3 (up to 3 decimals).

#include <bits/stdc++.h>
using namespace std;

// Parse a nonnegative decimal number into thousandths (×1000).
// Examples: "2" -> 2000, "1.5" -> 1500, "0.003" -> 3, "3.000" -> 3000.
static inline long long parse_thousandths(const string& s) {
    long long whole = 0, frac = 0;
    int i = 0, n = (int)s.size();

    // integer part
    while (i < n && isdigit((unsigned char)s[i])) {
        whole = whole * 10 + (s[i] - '0');
        ++i;
    }

    // fractional part (up to 3 digits kept)
    if (i < n && s[i] == '.') {
        ++i;
        int k = 0;
        while (i < n && isdigit((unsigned char)s[i]) && k < 3) {
            frac = frac * 10 + (s[i] - '0');
            ++i; ++k;
        }
        // pad trailing zeros if fewer than 3 fractional digits
        while (k < 3) { frac *= 10; ++k; }
        // skip any extra fractional digits (ignored)
    } else {
        frac = 0; // no decimal part
    }

    return whole * 1000 + frac;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; 
        cin >> n;
        bool ok = true;

        string token;
        long long prev = -1;  // numbers are >= 0, so -1 is safe sentinel

        for (int i = 0; i < n; ++i) {
            cin >> token;
            long long cur = parse_thousandths(token);
            if (i > 0 && cur < prev) ok = false;
            prev = cur;
        }

        cout << (ok ? "SUCCESSFUL" : "SUSSYBAKA") << '\n';
    }
    return 0;
}
