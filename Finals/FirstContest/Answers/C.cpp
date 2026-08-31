// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 1 (Finals — First Contest)
// Problem : C
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <cstdio>

#define maxk 10001
#define mod 1000000007

int n, k, dp[2][maxk]; 

int main(void) {
   scanf( "%d%d", &n, &k );
	dp[1][0] = 1;
	for( int i = 2; i <= n; i++ ) {
		int tmp = 0;
		for( int j = 0; j <= k; j++ ) {
			tmp = (tmp+dp[(i-1)&1][j])%mod;
			if( j >= i ) tmp = (tmp-dp[(i-1)&1][j-i]+mod)%mod;
			dp[i&1][j] = tmp;
		}
	}
	printf( "%d\n", dp[n&1][k] );
	return 0;
}
