// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : E
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  int ok = 1;
  int cnt = 1, n;
  char wrd[10];
  scanf("%d",&n);
  while (n--) {
    scanf("%s",wrd);
    if (strcmp(wrd,"mumble"))
        ok &= cnt == atoi(wrd);
    cnt++;
  }
  if (ok) printf("makes sense\n"); else printf("something is fishy\n");
}
