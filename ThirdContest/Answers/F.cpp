// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : F
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

// IFCF - Last Minute Constructions (Problem F) — Steiner-path solution

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K; 
    if (!(cin >> K)) return 0;
    while (K--) {
        int N, M, T; 
        cin >> N >> M >> T;
        int s, t; 
        cin >> s >> t;

        vector<vector<int>> g(N);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<pair<int,int>> tunnels(T);
        for (int i = 0; i < T; ++i) {
            int a, b; cin >> a >> b;
            tunnels[i] = {a,b};
        }

        // Roads must form a tree for this intended solution.
        if (M != N - 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        // Root the tree at 0 and build parent/depth for LCA (binary lifting).
        int root = 0;
        vector<int> parent(N, -1), depth(N, 0);
        parent[root] = root;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (parent[v] == -1) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }

        int LOG = 1;
        while ((1 << LOG) <= N) ++LOG;
        vector<vector<int>> up(LOG, vector<int>(N));
        for (int v = 0; v < N; ++v) up[0][v] = parent[v];
        for (int k = 1; k < LOG; ++k)
            for (int v = 0; v < N; ++v)
                up[k][v] = up[k-1][ up[k-1][v] ];

        auto lca = [&](int a, int b){
            if (depth[a] < depth[b]) swap(a,b);
            int d = depth[a] - depth[b];
            for (int k = 0; d; ++k, d >>= 1)
                if (d & 1) a = up[k][a];
            if (a == b) return a;
            for (int k = LOG-1; k >= 0; --k)
                if (up[k][a] != up[k][b]) {
                    a = up[k][a]; b = up[k][b];
                }
            return parent[a];
        };

        auto dist = [&](int a, int b){
            int L = lca(a,b);
            return depth[a] + depth[b] - 2*depth[L];
        };

        auto on_path = [&](int x, int a, int b)->bool{
            return dist(a,b) == dist(a,x) + dist(x,b);
        };

        // ----- Build Steiner tree of terminals S -----
        vector<char> isTerm(N, 0);
        isTerm[s] = isTerm[t] = 1;
        for (auto &e : tunnels) { isTerm[e.first] = 1; isTerm[e.second] = 1; }

        int termCount = 0;
        for (int i = 0; i < N; ++i) termCount += isTerm[i];

        // Accumulate terminal counts from children to parent
        vector<vector<int>> children(N);
        for (int v = 0; v < N; ++v) if (v != root) children[parent[v]].push_back(v);

        vector<int> val(N, 0);
        for (int i = 0; i < N; ++i) if (isTerm[i]) val[i] = 1;

        function<void(int)> dfsAcc = [&](int u){
            for (int v : children[u]) {
                dfsAcc(v);
                val[u] += val[v];
            }
        };
        dfsAcc(root);

        // An undirected edge (u - v(child)) is in the Steiner tree
        // iff 0 < val[v] < |S|.
        vector<int> deg(N, 0);
        int edgesIn = 0;
        for (int u = 0; u < N; ++u) {
            for (int v : children[u]) {
                if (0 < val[v] && val[v] < termCount) {
                    ++deg[u]; ++deg[v]; ++edgesIn;
                }
            }
        }

        // If the Steiner tree is empty (all terminals coincide), only possible if
        // s==t==that node and every tunnel is a self-loop at that node.
        if (edgesIn == 0) {
            int node = -1;
            for (int i = 0; i < N; ++i) if (isTerm[i]) { node = i; break; }
            bool okZero = (node != -1 && s == t && s == node);
            for (auto &e : tunnels) if (!(e.first == node && e.second == node)) okZero = false;
            cout << (okZero ? "POSSIBLE\n" : "IMPOSSIBLE\n");
            continue;
        }

        // Steiner tree must be a single simple path.
        vector<int> nodes;
        for (int i = 0; i < N; ++i) if (deg[i] > 0) nodes.push_back(i);
        vector<int> ends;
        for (int u : nodes) if (deg[u] == 1) ends.push_back(u);

        bool ok = true;
        if (!(ends.size() == 2 && edgesIn == (int)nodes.size() - 1)) ok = false;

        // Build adjacency of Steiner path and recover linear order
        vector<vector<int>> sg(N);
        if (ok) {
            for (int u = 0; u < N; ++u)
                for (int v : children[u])
                    if (0 < val[v] && val[v] < termCount) {
                        sg[u].push_back(v);
                        sg[v].push_back(u);
                    }

            int u = ends[0], v = ends[1];
            vector<int> prev(N, -2);
            deque<int> dq; dq.push_back(u); prev[u] = -1;
            while (!dq.empty()) {
                int x = dq.front(); dq.pop_front();
                if (x == v) break;
                for (int y : sg[x]) if (prev[y] == -2) {
                    prev[y] = x; dq.push_back(y);
                }
            }
            // Recover order u..v
            vector<int> order;
            for (int x = v; x != -1; x = prev[x]) order.push_back(x);
            reverse(order.begin(), order.end());

            // position map
            vector<int> pos(N, -1);
            for (int i = 0; i < (int)order.size(); ++i) pos[order[i]] = i;

            // All tunnels must go left->right; also s must not come after t.
            for (auto &e : tunnels) {
                int a = e.first, b = e.second;
                if (pos[a] == -1 || pos[b] == -1 || !(pos[a] < pos[b])) { ok = false; break; }
            }
            if (ok) {
                if (pos[s] == -1 || pos[t] == -1 || pos[s] > pos[t]) ok = false;
            }
        }

        cout << (ok ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    }
    return 0;
}
