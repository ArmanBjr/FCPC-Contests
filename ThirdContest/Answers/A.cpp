// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : A
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    const long long HSEC = 3600;
    const long long MSEC = 60;

    for (int i = 0; i < T; ++i) {
        long long S;
        cin >> S;

        long long H = S / HSEC;
        long long rem = S % HSEC;
        long long M = rem / MSEC;
        long long S2 = rem % MSEC;

        cout << H << ' ' << M << ' ' << S2 << '\n';
    }
    return 0;
}
