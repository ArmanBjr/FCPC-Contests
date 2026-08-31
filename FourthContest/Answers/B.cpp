// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : B
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
#include <math.h>
#define ll long long
using namespace std;

int main()
{
    long long int n, x, sum = 0, steps=0, temp;
    cin >> n;
    ll A[n];

    for (long long int i = 0; i < n; i++)
    {
        cin >> x;
        A[i] = x;
        sum += x;
    }
    ll avg = sum/n;
    for (long long int i = 0; i < n; i++)
    {
        temp = avg>=A[i] ? avg-A[i] : A[i]-avg;
        steps += temp;
    }

    cout << steps/2;
    return 0;
}
