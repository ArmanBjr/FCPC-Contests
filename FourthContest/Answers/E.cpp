// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : E
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)


int snoob(int x) {
  int y = x & -x, z = x + y;
  return z | ((x ^ z) >> 2) / y; }

vi bfs(int s, vvi &g) {
    vi res(g.size(), -1);
    res[s] = 0;
    queue<int> q;
    q.push(s);
    while(q.size() > 0) {
        int cur = q.front();
        q.pop();
        for(int x : g[cur]) {
            if(res[x] != -1) continue;
            res[x] = res[cur] + 1;
            q.push(x);
        }
    }
    return res;
}

struct { vi adj; int val, num, lo; bool done; } V[2*100000+100];
struct TwoSat {
  int n, at = 0; vi S;
  TwoSat(int _n) : n(_n) {
    rep(i,0,2*n+1)
      V[i].adj.clear(),
      V[i].val = V[i].num = -1, V[i].done = false; }
  bool put(int x, int v) {
    return (V[n+x].val &= v) != (V[n-x].val &= 1-v); }
  void add_or(int x, int y) {
    V[n-x].adj.push_back(n+y), V[n-y].adj.push_back(n+x); }
  int dfs(int u) {
    int br = 2, res;
    S.push_back(u), V[u].num = V[u].lo = at++;
    iter(v,V[u].adj) {
      if (V[*v].num == -1) {
        if (!(res = dfs(*v))) return 0;
        br |= res, V[u].lo = min(V[u].lo, V[*v].lo);
      } else if (!V[*v].done)
        V[u].lo = min(V[u].lo, V[*v].num);
      br |= !V[*v].val; }
    res = br - 3;
    if (V[u].num == V[u].lo) rep(i,res+1,2) {
      for (int j = (int)S.size()-1; ; j--) {
        int v = S[j];
        if (i) {
          if (!put(v-n, res)) return 0;
          V[v].done = true, S.pop_back();
        } else res &= V[v].val;
        if (v == u) break; }
      res &= 1; }
    return br | !res; }
  bool sat() {
    rep(i,0,2*n+1)
      if (i != n && V[i].num == -1 && !dfs(i)) return false;
    return true; } };

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, a, b; cin >> n >> m;
    vvi g(n, vi());
    while(m--) {
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vvi dists(n);
    for(int i = 0; i < n; ++i)
        dists[i] = bfs(i, g);
    vvi neighmask(32, vi(n, 0));
    for(int i = 0; i < n; ++i) { 
        neighmask[i / 32][i] |= 1 << (i % 32);
        for(int j : g[i]) {
            neighmask[j / 32][i] |= 1 << (j % 32);
        }
    }
    int ceo = -1, ceomsk = 0;
    for(int i = 0; i < n; ++i) {
        if(g[i].size() > 15) continue;
        int mxd = INT_MIN;
        for(int j = 0; j < n; ++j)
            mxd = max(mxd, dists[i][j]);
        if(mxd > 2) continue;
        if(g[i].size() <= 8) {
            ceo = i;
            ceomsk = (1 << g[i].size()) - 1;
            break;
        }
        int msk = (1 << 8) - 1;
        while(msk < (1 << g[i].size())) {
            int rch = 0;
            for(int j = 0; j < 32; ++j) {
                int curmsk = 0;
                for(int k = 0; k < 16; ++k) {
                    if(msk & (1 << k)) {
                        curmsk |= neighmask[j][g[i][k]];
                    }
                }
                rch += __builtin_popcount(curmsk);
                if(rch == n) {
                    ceo = i;
                    ceomsk = msk;
                    break;
                }
                if(rch % 32 != 0) break;
            }
            msk = snoob(msk);
            if(ceo != -1) break;
        }
        if(ceo != -1) break;
    }
    vi managers;
    for(int i = 0; i < g[ceo].size(); ++i)
        if(ceomsk & (1 << i))
            managers.push_back(g[ceo][i]);
    for(int i = 0; i < (1 << managers.size()); ++i) {
        bool valid = true;
        vi stat(n, 7);
        stat[ceo] = 1;
        queue<int> b1;
        b1.push(ceo);
        for(int j = 0; j < managers.size(); ++j) {
            if(i & (1 << j)) stat[managers[j]] = 2;
            else stat[managers[j]] = 4;
            b1.push(managers[j]);
        }
        while(valid && b1.size() > 0) {
            int cur = b1.front();
            assert(__builtin_popcount(stat[cur]) == 1);
            b1.pop();
            for(int x : g[cur]) {
                int over = stat[x] & stat[cur];
                if(over == 0) continue;
                stat[x] &= ~stat[cur];
                if(stat[x] == 0) { valid = false; break; }
                if(__builtin_popcount(stat[x]) == 1) b1.push(x);
            }
        }
        if(!valid) continue;
        TwoSat ts(n);
        for(int j = 0; j < n; ++j) {
            if(__builtin_popcount(stat[j]) == 1) continue;
            for(int k : g[j]) {
                if(k <= j) continue;
                if(__builtin_popcount(stat[k]) == 1) continue;
                int over = stat[j] & stat[k];
                if(over == 0) continue;
                if(stat[j] == stat[k]) {
                    ts.add_or(k + 1, j + 1);
                    ts.add_or(-k - 1, -j - 1);
                    continue;
                }
                bool is_lo_k = over < (stat[k] ^ over);
                bool is_lo_j = over < (stat[j] ^ over);
                int x = is_lo_k ? k + 1 : -k - 1;
                int y = is_lo_j ? j + 1 : -j - 1;
                ts.add_or(x, y);
            }
        }
        if(!valid) continue;
        if(!ts.sat()) continue;
        for(int i = 0; i < n; ++i) {
            int vl = 0;
            if(__builtin_popcount(stat[i]) == 1) {
                vl = stat[i];
            } else {
                bool is_hi = V[n + i + 1].val == 1;
                int msb = (stat[i] & 4) ? 4 : ((stat[i] & 2) ? 2 : 1);
                vl = is_hi ? msb : stat[i] ^ msb;
            }
            if(vl == 1) cout << "1 ";
            else if(vl == 2) cout << "2 ";
            else if(vl == 4) cout << "3 ";
        }
        cout << '\n';
        exit(0);
    }
    cout << "Impossible\n";
}
