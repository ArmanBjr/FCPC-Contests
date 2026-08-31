// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : B
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>
using namespace std;

using u64 = unsigned long long;
using i64 = long long;

// Integer floor sqrt for non-negative 64-bit values
static inline u64 isqrt_u64(u64 x) {
    u64 r = (u64)floor(sqrt((long double)x));
    while ((r + 1) * (r + 1) <= x) ++r;
    while (r * r > x) --r;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        long long L, F, D;
        cin >> L >> F >> D;

        if (L == 0 || F == 0) {         // no days or zero base fee
            cout << 0 << '\n';
            continue;
        }
        if (D == 0) {                   // constant fee each day
            // Max: 1e6 * 1e9 = 1e15 (fits in signed 64-bit)
            long long ans = L * F;
            cout << ans << '\n';
            continue;
        }
        if (F <= D) {                   // day 1 already zero or negative
            cout << 0 << '\n';
            continue;
        }

        // Positive days satisfy: F - D*k^2 > 0  <=>  k^2 < F/D
        // Let q = (F - 1) / D; k_max = floor(sqrt(q))
        u64 q = (u64)((F - 1) / D);
        u64 kmax_pos = isqrt_u64(q);
        if (kmax_pos == 0) {
            cout << 0 << '\n';
            continue;
        }

        u64 K = min<u64>(kmax_pos, (u64)L);

        // Sum_{k=1..K} (F - D*k^2) = K*F - D * (K*(K+1)*(2K+1)/6)
        // With constraints (F<=1e9, D<=1e6, L<=1e6), both terms fit safely in 64-bit.
        unsigned long long sum_k2 = K * (K + 1) * (2 * K + 1) / 6ULL;
        unsigned long long part1  = K * (unsigned long long)F;
        unsigned long long part2  = (unsigned long long)D * sum_k2;

        unsigned long long ans64 = (part1 >= part2) ? (part1 - part2) : 0ULL;
        cout << (long long)ans64 << '\n';
    }
    return 0;
}
