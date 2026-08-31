// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
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

    while (T--) {
        string s;
        cin >> s;
        int n = (int)s.size();
        int k = n / 2;

        int left_sum = 0, right_sum = 0;
        for (int i = 0; i < k; ++i) {
            left_sum += s[i] - '0';
        }
        for (int i = k; i < n; ++i) {
            right_sum += s[i] - '0';
        }

        if (left_sum == right_sum) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
