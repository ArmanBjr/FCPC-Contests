// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : I
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

/*
   FCPC S.4 – Tunnel Maintenance Drone (Jetpack-like task)

   Grid: 10 x N
   rows: 0 (top) .. 9 (bottom)
   cols: 0 .. N-1
   Start: (9, 0), engine initially OFF.

   Each second (step) you move from column c to c+1:

     - engine OFF → down-right: row -> min(9, row+1)
     - engine ON  → up-right  : row -> max(0, row-1)

   (If you are already at floor/ceiling, you stay in that row and just move right.)

   We store, for each reachable cell (r,c), from which (row,mode) we came.
   Then we backtrack from some reachable cell in the last column, get the
   ON/OFF mode per step, and compress consecutive ON steps into intervals.

   Time parameter t in the output is 0-based, exactly like in the original
   official solution (i.e., t is the index of the step where you start
   moving up).
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    const int R = 10;
    vector<string> g(R);
    for (int i = 0; i < R; ++i) {
        cin >> g[i];
    }

    // reachable[r][c] = can we stand at (r, c)?
    vector<vector<char>> reachable(R, vector<char>(N, 0));
    vector<vector<int>>  pre_row(R, vector<int>(N, -1));  // previous row
    vector<vector<int>>  pre_mode(R, vector<int>(N, -1)); // 0 = OFF, 1 = ON

    // Start cell must be free; problem statement guarantees it, but be safe.
    if (g[9][0] != '.') {
        cout << 0 << "\n";
        return 0;
    }
    reachable[9][0] = 1;

    // DP across columns: c -> c+1
    for (int c = 0; c < N - 1; ++c) {
        for (int r = 0; r < R; ++r) {
            if (!reachable[r][c]) continue;
            int nc = c + 1;

            // Engine OFF: down-right (or stay at floor)
            {
                int nr = (r < R - 1) ? r + 1 : r;
                if (g[nr][nc] == '.' && !reachable[nr][nc]) {
                    reachable[nr][nc] = 1;
                    pre_row[nr][nc] = r;
                    pre_mode[nr][nc] = 0;
                }
            }

            // Engine ON: up-right (or stay at ceiling)
            {
                int nr = (r > 0) ? r - 1 : r;
                if (g[nr][nc] == '.' && !reachable[nr][nc]) {
                    reachable[nr][nc] = 1;
                    pre_row[nr][nc] = r;
                    pre_mode[nr][nc] = 1;
                }
            }
        }
    }

    // Find any reachable cell in the last column.
    int end_row = -1;
    for (int r = 0; r < R; ++r) {
        if (reachable[r][N - 1]) {
            end_row = r;
            break;
        }
    }

    // Problem guarantees a solution exists, but be defensive.
    if (end_row == -1) {
        cout << 0 << "\n";
        return 0;
    }

    // Backtrack modes for steps 0..N-2 (each step is col -> col+1).
    int steps = N - 1;
    vector<int> mode(steps, 0); // 0 = OFF, 1 = ON

    int r = end_row;
    int c = N - 1;
    while (c > 0) {
        int m  = pre_mode[r][c];
        int pr = pre_row[r][c];
        mode[c - 1] = m;   // step (c-1) → c used mode m
        r = pr;
        --c;
    }

    // Compress consecutive ON-steps into (t, x) intervals.
    vector<pair<int,int>> ans;
    int k = 0;
    while (k < steps) {
        if (mode[k] == 1) {
            int start = k;
            while (k < steps && mode[k] == 1) ++k;
            int len = k - start;
            ans.push_back({start, len}); // t is 0-based
        } else {
            ++k;
        }
    }

    cout << ans.size() << "\n";
    for (auto &p : ans) {
        cout << p.first << ' ' << p.second << "\n";
    }
    return 0;
}
