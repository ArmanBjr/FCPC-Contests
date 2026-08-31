// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : C
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int d(char ch) { return ch - '0'; }
char D(int v) {
    if (v > '9') v -= 10;
    if (v < '0') v += 10;
    return v;
}

string sol(string a, string b) {
    int at = -1;
    string na = a;
    rep(i,0,sz(a)) {
        int tsum = d(a[i]) + d(b[i]);
        if (at == i) tsum++;
        if (tsum >= 10) at = i + 1;
    }
    rep(i,0,at) {
        while (d(na[i]) != 0) {
            na[i] = D(na[i] + 1);
            b[i] = D(b[i] - 1);
        }
    }
    if (at != -1) na[at]++;
    string ans(sz(na), '0');
    rep(i,0,sz(a)) {
        ans[i] = na[i] - a[i] + '0';
        if (ans[i] < '0') {
            na[i + 1]--;
            ans[i] += 10;
        }
    }
    return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

    string A, B;
    cin >> A >> B;
    reverse(all(A));
    reverse(all(B));
    while (sz(A) < sz(B)) A.push_back('0');
    while (sz(A) > sz(B)) B.push_back('0');
    A.push_back('0');
    B.push_back('0');

    string asol = sol(A, B);
    string bsol = sol(B, A);
    reverse(all(asol));
    reverse(all(bsol));

    string ans = min(asol, bsol);
    reverse(all(ans));
    while (ans.back() == '0' && sz(ans) > 1) ans.pop_back();
    reverse(all(ans));
    cout << ans << endl;
}
