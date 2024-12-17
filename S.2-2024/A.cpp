//FCPC S.2 2024 A

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ll n;
	cin >> n;
	int ans[n];
	for (ll i = 0; i < n; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		if (a + b > c) ans[i] = 1;
		else ans[i] = 0;
	}
	for (ll i = 0; i < n; i++) {
		if (ans[i]) {
			cout << "Emad\n";
		} else {
			cout << "Amin\n";
		}
	}
}
