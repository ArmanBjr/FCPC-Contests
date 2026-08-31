// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : I
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 100100;

int N;
char A[MAXN];
int taken[MAXN];

char mirko[MAXN];
char slavko[MAXN];

char *pm = mirko;
char *ps = slavko;

queue< int > Q[26];

int main(void) 
{
  scanf("%d %s", &N, A);

  for (int i = N - 1; i >= 0; --i) 
    Q[A[i] - 'a'].push(i);

  int m = N - 1, s = 0;

  for (int i = 0; i < N; ++i) {
    if (i & 1) {
      while (true) {
        while (Q[s].empty()) ++s;
        if (taken[Q[s].front()]) {
          Q[s].pop();
          continue;
        }
        break;
      }
      *ps++ = 'a' + s;
      taken[Q[s].front()] = 1; 
    } else {
      while (taken[m]) --m;
      *pm++ = A[m];
      taken[m] = 1;
    }
  }

  if (strcmp(slavko, mirko) < 0) 
    puts("Emad will win!"); 
  else 
    puts("Amin is the true winner");

  puts(slavko);

  return 0;
}
