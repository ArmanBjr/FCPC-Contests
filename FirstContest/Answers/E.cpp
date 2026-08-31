// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 1 (First Contest)
// Problem : E
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r, pr; // pr[x] = parity to parent (0 same, 1 different)
    DSU(int n=0): n(n), p(n+1), r(n+1,0), pr(n+1,0) { iota(p.begin(), p.end(), 0); }
    pair<int,int> findp(int x){
        if(p[x]==x) return {x,0};
        auto t = findp(p[x]);
        pr[x] ^= t.second;
        p[x] = t.first;
        return {p[x], pr[x]};
    }
    bool unite(int a, int b, int rel){ // rel: 0 ally, 1 enemy
        auto [ra, pa] = findp(a);
        auto [rb, pb] = findp(b);
        if(ra==rb) return ((pa ^ pb) == rel);
        if(r[ra] < r[rb]) { swap(ra,rb); swap(pa,pb); }
        p[rb] = ra;
        pr[rb] = pa ^ pb ^ rel;
        if(r[ra]==r[rb]) r[ra]++;
        return true;
    }
    int relation(int a, int b){
        auto [ra, pa] = findp(a);
        auto [rb, pb] = findp(b);
        if(ra!=rb) return -1;
        return (pa ^ pb); // 0 ally, 1 enemy
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q;
    if(!(cin>>N>>Q)) return 0;
    DSU dsu(N);
    for(int i=0;i<Q;++i){
        int t,u,v; cin>>t>>u>>v;
        if(t==1){
            if(dsu.unite(u,v,0)) cout<<"OK\n";
            else cout<<"CONTRADICTION\n";
        }else if(t==2){
            if(dsu.unite(u,v,1)) cout<<"OK\n";
            else cout<<"CONTRADICTION\n";
        }else{
            int r = dsu.relation(u,v);
            if(r==-1) cout<<"UNKNOWN\n";
            else if(r==0) cout<<"ALLY\n";
            else cout<<"ENEMY\n";
        }
    }
    return 0;
}
