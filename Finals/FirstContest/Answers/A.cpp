// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 1 (Finals — First Contest)
// Problem : A
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    if (!(cin >> N >> Q)) return 0;

    vector<int> A(N + 1), px(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        px[i] = px[i - 1] ^ A[i];
    }
    for (int i = 0; i < Q; ++i) {
        int L, R;
        cin >> L >> R;
        cout << (px[R] ^ px[L - 1]) << '\n';
    }
    return 0;
}
