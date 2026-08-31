// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 2 (Finals — Second Contest)
// Problem : A
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
int main() {
	int N, a = 0, b, fail = 0;
	std::cin >> N;
	while( N--> 0 ){
		std::cin >> b;
		fail |= b < a;
		a = b;
	}
	std::cout << ( fail ? "no\n" : "yes\n" );
	return 0;
}
