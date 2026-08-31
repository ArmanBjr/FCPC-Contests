// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : F
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<int> N[100000];
int quer[100000];
int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        N[a].push_back(b);
        N[b].push_back(a);
        quer[i] = a;
    }
    queue<int> q;
    bool seen[n];
    for (int i = 0; i < n; i++)
        seen[i] = false;
    int dis[n];

    q.push(quer[0]);
    seen[quer[0]] = true;
    dis[quer[0]] = 0;

    while (!q.empty())
    {
        int i = q.front();
        for (int j : N[i])
            if (!seen[j])
            {
                seen[j] = true;
                dis[j] = dis[i] + 1;
                q.push(j);
            }
        q.pop();
    }
    for (int i = 0; i < n - 1; i++)
        cout << dis[quer[i]] % 2 << endl;
}
