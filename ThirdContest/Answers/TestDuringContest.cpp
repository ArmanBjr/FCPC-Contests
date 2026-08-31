#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

#define ll long long
#define ld long double

const ll INF = 1e9;

// class MyClass{
//     public:
//         int myNum;
//         string myStr;
//         void myMethod(){
//             cout << "HW" << '\n';
//         }
// };

// struct {
//     int myNum;
//     string myStr;
// } myStruct1, myStruct2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n,k;
    cin>>n>>k;
    vector<ll> s(n);
    vector<ld> ps(n+1,0);

    for (ll i = 0; i < n; i++)
    {
        cin>>s[i];
        ps[i+1] = ps[i]+ (double) s[i];
    }
    ll l=0,r=k-1;
    ll ml=l,mr=r;
    ld mavg = 0;

    for(;l<n-k+1;l++){
        r = l+k-1;
        ld navg = (ps[r+1]-ps[l])/(double)k;
        if(navg>mavg){
            mavg = navg;
            ml=l;
            mr=r;
        }
    }

    ll size=k;
    ll lm=ml-1;
    ld navg = mavg;
    while (lm>=0)
    {
        navg = (ps[mr+1]-ps[lm])/(double)(size+ml-lm);
        if(navg>mavg){
            ml = lm;
            size+=(ml-lm);
            mavg = navg;
        }
        lm--;
    }

    ll rm=mr+1;
    while (rm<n)
    {   
        navg = (ps[rm+1]-ps[ml])/(double)(size+rm-mr);
        if( navg>mavg ){
            mr = rm;
            size+=(rm-mr);
            mavg = navg;
        }
        rm++;
    }

    cout<<fixed<<setprecision(8)<<mavg<<'\n';
    
    // MyClass obj;
    // obj.myNum = 0;
    // obj.myStr = "Mani";
    // obj.myMethod();
}