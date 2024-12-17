//FCPC S.2 2024 D

#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
#define mp make_pair
#define ll long long int
#define pii pair<int  , int>
using namespace std;
ll a , b , c , d;
ll ns[1000005];
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll,null_type,less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
ordered_set x;
int main(){
    cin >> a;
    for(int i = 0; i < a; i++){  
        cin >> ns[i];
    }   
    cin >> b;
    ll zero = 0;
    ll ans = 0;
    for(int i = 0; i < a; i++){
        ll w = ns[i] - b;
        if(w >=  0){
            ans +=1;
        }
        ll finder = -1 * w - zero;
            ans += (x.size() -  x.order_of_key(finder));
        zero = zero + w;
        x.insert((w - zero));
    }
    cout << ans << endl;
    return 0;   
}
