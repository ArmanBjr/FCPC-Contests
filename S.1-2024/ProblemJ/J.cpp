//FCPC S.1 2024 J
//thanks to Ehsan K. Goharshadi
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
#define mp make_pair
#define ll long long int
#define pii pair<int  , int>
using namespace std;
ll a , b , c , d , t;
bool rrt[5000005][2];
int main(){
    cin >> t >> a >> b;
    rrt[0][0] = true;

    for (int i = 0;i <= t;i++){
        if((i - a) >= 0 && rrt[i - a][0])
            rrt[i][0] = true;
        if((i - b) >= 0 && rrt[i - b][0])
            rrt[i][0] = true;
    }
    int q = 0;
    for(int i = 0;i <= t;i++){
    
        if(i*2 <= t && rrt[i*2][0] ){
            rrt[i][1] = true;
        }
        if((i*2 + 1) <= t && rrt[(i * 2 + 1)][0] ){
            rrt[i][1] = true;
        }
        if(rrt[i][0])
            rrt[i][1] = true;
        if(i - a >= 0 && rrt[i - a][1])
            rrt[i][1] = true;
        if(i - b >= 0 && rrt[i - b][1])
            rrt[i][1] = true;
        if(rrt[i][1])
            q = i;
    }
    cout << q << endl;
    return 0;   
}
