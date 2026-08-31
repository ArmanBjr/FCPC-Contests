// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : E
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

/* 
 Algorithm: straight forward simulation
 */ 
#include <cassert>
#include <cstdio>

char *ds = "WSEN";
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};

void solve() {
  int A, B, n, m;
  int x[200], y[200], dir[200];
  scanf("%d%d%d%d", &A, &B, &n, &m);
  for (int i = 1; i <= n; ++i) {
    char facing[30];
    scanf("%d%d%s", x+i, y+i, facing);
    dir[i] = 0;
    while (ds[dir[i]] != *facing) ++dir[i];
  }
  bool coll = false;
  for (int i = 0; i < m; ++i) {
    char act[30];
    int id, rep;
    scanf("%d%s%d", &id, act, &rep);
    if (*act != 'F') rep %= 4;
    while (!coll && rep--) {
      switch (*act) {
      case 'F': x[id] += dx[dir[id]]; y[id] += dy[dir[id]]; break;
      case 'L': (++dir[id]) %= 4; break;
      case 'R': (dir[id] += 3) %= 4; break;
      default: assert(0);
      }
      for (int j = 1; j <= n; ++j)
	if (j != id && x[j] == x[id] && y[j] == y[id]) {
	  printf("Robot %d crashes into robot %d\n", id, j);
	  coll = true;
	}
      if (x[id] < 1 || x[id] > A || y[id] < 1 || y[id] > B) {
	printf("Robot %d crashes into the wall\n", id);
	coll = true;
      }
    }
  }
  if (!coll) printf("OK\n");
}

int main() {
  int k;
  scanf("%d", &k);
  while (k--) solve();
  return 0;
}
