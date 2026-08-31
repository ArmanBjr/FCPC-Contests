// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : D
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>

using namespace std;

int main()
{
	int n,x,y,z;
	cin >> n;
	while (n--) {
		cin >> x >> y >> z;
		if (x > y-z)
			cout << "do not advertise" << endl;
		else if (x == y-z)
			cout << "does not matter" << endl;
		else
			cout << "advertise" << endl;
	}
	return 0;
}
