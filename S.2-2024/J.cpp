//FCPC S.2 2024 J
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int main() {
	int x; 
	cin >> x;
	ll count = 0;
	while (x > 0) {
		count += (x & 1);
		x >>= 1;
	}
	cout << count;
	return 0;
}
