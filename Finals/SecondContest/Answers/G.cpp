// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Finals Season 2 (Finals — Second Contest)
// Problem : G
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

vector<int> countAtoms(const string &s) {
    vector<int> cnt(26, 0);
    int i = 0;
    int n = (int)s.size();

    while (i < n) {
        // ضریب پیشِ‌روی مولکول
        int coef = 1;
        if (i < n && isdigit(s[i])) {
            coef = s[i] - '0';
            i++;
        }

        // تا قبل از '+' یا انتهای رشته، فرمول همین مولکول را می‌خوانیم
        while (i < n && s[i] != '+') {
            char atom = s[i];  // باید حرف بزرگ باشد
            i++;

            int atomCount = 1;
            if (i < n && isdigit(s[i])) {
                atomCount = s[i] - '0';
                i++;
            }

            if (atom >= 'A' && atom <= 'Z') {
                cnt[atom - 'A'] += coef * atomCount;
            }
            // اگر طبق صورت مسئله فقط حروف بزرگ داریم، نیازی به else نیست
        }

        // اگر '+' دیدیم، ردش کن و برو سر مولکول بعدی
        if (i < n && s[i] == '+') {
            i++;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    while (n--) {
        string eq;
        cin >> eq;  // طبق صورت مسئله، معادله بدون فاصله است

        // پیدا کردن "->"
        size_t pos = eq.find("->");
        if (pos == string::npos) {
            // ورودی خراب؛ ولی در صورت مسئله نباید رخ دهد
            cout << "NE\n";
            continue;
        }

        string left = eq.substr(0, pos);
        string right = eq.substr(pos + 2);

        vector<int> L = countAtoms(left);
        vector<int> R = countAtoms(right);

        if (L == R) {
            cout << "DA\n";
        } else {
            cout << "NE\n";
        }
    }

    return 0;
}
