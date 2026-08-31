// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 1 (Finals — First Contest)
// Problem : I
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    int A, E, V;
    long long D;
    cin >> A >> E >> V >> D;

    vector<vector<int>> adj(N + 1);
    adj.reserve(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const long long INF = (long long)1e18;

    // 1) BFS from Vecna to compute distances
    vector<long long> distV(N + 1, INF);
    queue<int> q;

    distV[V] = 0;
    q.push(V);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (distV[u] == D) continue;  // no need to go beyond distance D

        for (int v : adj[u]) {
            if (distV[v] == INF) {
                distV[v] = distV[u] + 1;
                if (distV[v] <= D) {
                    q.push(v);
                }
            }
        }
    }

    // 2) Mark blocked nodes
    vector<bool> blocked(N + 1, false);
    for (int i = 1; i <= N; ++i) {
        if (distV[i] <= D) blocked[i] = true;
    }

    // If Amin or Emad is blocked, impossible
    if (blocked[A] || blocked[E]) {
        cout << "NO\n";
        return 0;
    }

    // 3) BFS from Amin avoiding blocked nodes
    vector<bool> vis(N + 1, false);
    queue<int> q2;

    vis[A] = true;
    q2.push(A);

    bool canReach = false;

    while (!q2.empty()) {
        int u = q2.front();
        q2.pop();

        if (u == E) {
            canReach = true;
            break;
        }

        for (int v : adj[u]) {
            if (!blocked[v] && !vis[v]) {
                vis[v] = true;
                q2.push(v);
            }
        }
    }

    cout << (canReach ? "YES\n" : "NO\n");

    return 0;
}
