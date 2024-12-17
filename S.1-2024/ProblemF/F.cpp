//FCPC S.1 2024 F
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, ans;

int main() {
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        int k, c;
        cin >> k >> c;
        if (k <= m && c == 0) ans++;
        if (k > m && c == 1) ans++;
    }
        
    cout << ans;
    return 0;
}
