//FCPC S.1 2024 E
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
	ll n;
	ll sum = 0;
	ll number;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> number;
		sum += number;
	}	
	cout << sum;
}
