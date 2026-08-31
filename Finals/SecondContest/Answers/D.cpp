// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 2 (Finals — Second Contest)
// Problem : D
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <algorithm>
using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " = " << x << endl

int main() {
  int n;
  scanf("%d", &n);
  REP(i, n) {
    int a, b;
    scanf("%d %d", &a, &b);
    int rj = 2 * min(a, b) - 2;
    printf("%d\n", rj);
  }
  return 0;
}
