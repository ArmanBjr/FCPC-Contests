// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : H
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

// Build next-occurrence table:
// nextPos[i][c] = smallest index j >= i such that s[j] == ('a' + c),
// or n if no such position.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    const int ALPHA = 26;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";

    // nextPos has size (n+1) x 26; use n as "not found" sentinel.
    vector<array<int, ALPHA>> nextPos(n + 2);
    // Initialize row n: no occurrences after position n-1
    for (int c = 0; c < ALPHA; ++c) {
        nextPos[n][c] = n;
    }

    // Fill from back to front
    for (int i = n - 1; i >= 0; --i) {
        nextPos[i] = nextPos[i + 1];              // copy from next
        nextPos[i][s[i] - 'a'] = i;               // current char occurs at i
    }

    auto is_subsequence = [&](const string &t) -> bool {
        int pos = 0;  // current search position in s
        for (char ch : t) {
            int c = ch - 'a';
            if (pos > n) return false;
            int nxt = nextPos[pos][c];
            if (nxt >= n) return false; // not found
            pos = nxt + 1;
        }
        return true;
    };

    // 1) Try all strings of length 1
    for (char c1 : alphabet) {
        string t(1, c1);
        if (!is_subsequence(t)) {
            cout << t << "\n";
            return 0;
        }
    }

    // 2) Try all strings of length 2
    for (char c1 : alphabet) {
        for (char c2 : alphabet) {
            string t;
            t.push_back(c1);
            t.push_back(c2);
            if (!is_subsequence(t)) {
                cout << t << "\n";
                return 0;
            }
        }
    }

    // 3) Try all strings of length 3
    for (char c1 : alphabet) {
        for (char c2 : alphabet) {
            for (char c3 : alphabet) {
                string t;
                t.push_back(c1);
                t.push_back(c2);
                t.push_back(c3);
                if (!is_subsequence(t)) {
                    cout << t << "\n";
                    return 0;
                }
            }
        }
    }

    // Theoretically, we should always have returned earlier.
    // But for safety:
    cout << "aaaa\n";
    return 0;
}
