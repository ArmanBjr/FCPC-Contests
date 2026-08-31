// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : A
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

// FUM Cup Draw: Fair or Fixed?  — reference solution
// g ≤ 8, m ≤ 4.  Per-pot subset-DP O(g * 2^g).  Overall easily fast.
//
// Model:
//  - Seeds: group 0 has host 0; groups 1..g-1 have given seeds (in order).
//  - Remaining m-1 positions are m-1 "pots", each with exactly g teams.
//  - Faculties with ≤ g teams: no two in the same group. Given guarantee:
//    all unseeded teams of such a faculty are in the same pot, so inter-pot
//    constraints disappear; within a pot we only forbid placing a team into
//    a group whose seed is from the same faculty.
//  - Faculties with > g teams: ignore the restriction.
//
// For each pot independently, build allowed edges team→group and count:
//    TOTAL  = # perfect matchings
//    FIX[u][k] = # perfect matchings with team u forced to group k
// Probabilities: P(u→k) = FIX[u][k] / TOTAL.
// Expected opponent sum:
//
//  If t is a seed in group k0:
//     E = sum_{p} sum_{u in pot p} S[u] * P_p(u→k0)
//  If t is in pot p0:
//     C[k] = S[seed[k]] + sum_{p != p0} sum_{u in pot p} S[u] * P_p(u→k)
//     E = sum_{k} P_{p0}(t→k) * C[k]
//
// Print with 3 decimals.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Count perfect matchings with allowed[i] being bitmask of allowed groups for team i.
// Teams are processed in order 0..g-1 (level DP).
static ll count_matchings(const vector<int>& allowed) {
    int g = (int)allowed.size();
    int FULL = (1 << g) - 1;
    vector<long long> dp(1 << g, 0), ndp(1 << g, 0);
    dp[0] = 1;
    for (int i = 0; i < g; ++i) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int mask = 0; mask <= FULL; ++mask) {
            if (dp[mask] == 0) continue;
            if (__builtin_popcount((unsigned)mask) != i) continue; // level i
            int avail = allowed[i] & (~mask);
            for (int k = 0; k < g; ++k) if (avail & (1 << k)) {
                ndp[mask | (1 << k)] += dp[mask];
            }
        }
        dp.swap(ndp);
    }
    return dp[FULL];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    cout.setf(std::ios::fixed);
    cout << setprecision(3);

    while (T--) {
        int g, m;
        cin >> g >> m;
        const int TOT = g * m;

        // strengths
        vector<int> S(TOT);
        for (int i = 0; i < TOT; ++i) cin >> S[i];

        // seeds: group 0 has host 0; then g-1 seeds for groups 1..g-1
        vector<int> seed(g);
        seed[0] = 0;
        for (int k = 1; k < g; ++k) cin >> seed[k];

        // pots: m-1 lines, each with g indices
        vector<vector<int>> pots(m - 1, vector<int>(g));
        vector<int> teamPot(TOT, -1); // map team -> which pot (0..m-2), or -1 if seeded
        for (int p = 0; p < m - 1; ++p) {
            for (int j = 0; j < g; ++j) {
                cin >> pots[p][j];
                teamPot[pots[p][j]] = p;
            }
        }

        // faculties
        int c; cin >> c;
        vector<int> teamFaculty(TOT, -1);
        vector<int> facultySize;
        facultySize.reserve(c);
        for (int f = 0; f < c; ++f) {
            int ni; cin >> ni;
            facultySize.push_back(ni);
            for (int j = 0; j < ni; ++j) {
                int idx; cin >> idx;
                teamFaculty[idx] = f;
            }
        }

        // queried team
        int t; cin >> t;

        // faculty of seeds (for quick comparison)
        vector<int> seedFaculty(g);
        for (int k = 0; k < g; ++k) seedFaculty[k] = teamFaculty[seed[k]];

        // For each pot, build allowed masks team->groups
        // prob[p][team][k]
        vector<unordered_map<int, vector<long double>>> prob(m - 1);

        for (int p = 0; p < m - 1; ++p) {
            // order teams as in pots[p], size g
            vector<int> teams = pots[p];
            vector<int> allowed(g, 0);
            for (int i = 0; i < g; ++i) {
                int u = teams[i];
                int fu = teamFaculty[u];
                if (fu >= 0 && facultySize[fu] <= g) {
                    int mask = 0;
                    for (int k = 0; k < g; ++k)
                        if (seedFaculty[k] != fu) mask |= (1 << k);
                    allowed[i] = mask;
                } else {
                    allowed[i] = (1 << g) - 1; // unrestricted
                }
            }

            ll total = count_matchings(allowed);
            // Assuming inputs guarantee at least one valid draw
            // but we still handle total==0 gracefully (all probabilities 0).
            unordered_map<int, vector<long double>> potProb;
            potProb.reserve(g * 2);

            for (int i = 0; i < g; ++i) {
                int u = teams[i];
                vector<long double> pu(g, 0.0L);
                if (total > 0) {
                    for (int k = 0; k < g; ++k) {
                        if (allowed[i] & (1 << k)) {
                            vector<int> forced = allowed;
                            forced[i] = (1 << k); // force u->k
                            ll ways = count_matchings(forced);
                            pu[k] = (long double)ways / (long double)total;
                        } else {
                            pu[k] = 0.0L;
                        }
                    }
                }
                potProb[u] = std::move(pu);
            }
            prob[p] = std::move(potProb);
        }

        // Helper to know if t is seed and which group
        auto findSeedGroup = [&](int team)->int {
            for (int k = 0; k < g; ++k) if (seed[k] == team) return k;
            return -1;
        };
        int tSeedGroup = findSeedGroup(t);

        long double answer = 0.0L;

        if (tSeedGroup != -1) {
            // t is a seed in fixed group
            int k0 = tSeedGroup;
            for (int p = 0; p < m - 1; ++p) {
                for (int u : pots[p]) {
                    answer += (long double)S[u] * prob[p][u][k0];
                }
            }
        } else {
            // t is in some pot p0
            int p0 = teamPot[t];
            // Precompute C[k] = seed[k] + contributions from pots != p0
            vector<long double> C(g, 0.0L);
            for (int k = 0; k < g; ++k) {
                C[k] += (long double)S[seed[k]];
                for (int p = 0; p < m - 1; ++p) if (p != p0) {
                    for (int u : pots[p]) {
                        C[k] += (long double)S[u] * prob[p][u][k];
                    }
                }
            }
            // Mix by t's own distribution
            for (int k = 0; k < g; ++k) {
                answer += prob[p0][t][k] * C[k];
            }
        }

        cout << (double)answer << "\n";
    }

    return 0;
}
