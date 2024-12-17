//FCPC S.1 2024 B
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	int n, prev, now;
	cin >> n;
	cin >> prev;
	for (int i = 1; i < n; i++) {
		cin >> now;
		if (now > prev) {
			cout << i + 1;
			return 0;
		}
		prev = now;
	}
	cout << -1;
	return 0;
}
