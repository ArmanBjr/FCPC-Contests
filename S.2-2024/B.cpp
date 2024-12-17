//FCPC S.2 2024 B
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ll n;
	cin >> n;
	ll k;
	cin >> k;
	ll sum = 0;
	
	while (n--) {
		ll adad;
		cin >> adad;
		if (adad % k == 0) {
			sum += adad;
		}	
	}	
	cout << sum << endl;
	return 0;
}
