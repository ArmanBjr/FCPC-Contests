// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 4 (Fourth Contest)
// Problem : G
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

string str, a, b;

int main(void)
{
    cin >> str;
    int n = str.size();

    for (int k = 1; k < n; ++k)
        if (n % k == 0) {
            a = str.substr(0, k);
            sort(a.begin(), a.end());
            bool confirm = true;

            for (int i = k; i < n; i += k) {
                b = str.substr(i, k);
                sort(b.begin(), b.end());
                if (a != b) {
                    confirm = false;
                    break;
                }
            }

            if (confirm)
            {
                cout << str.substr(0, k) << endl;
                return 0;
            }
        }

    cout << "-1" << endl;

    return 0;
}
