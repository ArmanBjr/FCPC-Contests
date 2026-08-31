// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : D
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

    vector<long long> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // Precompute floor(log2) for 1..N
    vector<int> lg(N + 1);
    lg[1] = 0;
    for (int i = 2; i <= N; ++i) {
        lg[i] = lg[i / 2] + 1;
    }

    int K = lg[N]; // maximum power for N

    // Sparse table: st[k][i] = max on [i, i + 2^k - 1]
    vector<vector<long long>> st(K + 1, vector<long long>(N));
    // Base layer (intervals of length 1)
    for (int i = 0; i < N; ++i) {
        st[0][i] = a[i];
    }

    // Build higher layers
    for (int k = 1; k <= K; ++k) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 0; i + len <= N; ++i) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + half]);
        }
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;
        // Convert to 0-based
        --L; 
        --R;
        int len = R - L + 1;
        int k = lg[len];
        int lenPow = 1 << k;
        long long ans = max(st[k][L], st[k][R - lenPow + 1]);
        cout << ans << "\n";
    }

    return 0;
}
