// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 3 (Third Contest)
// Problem : C
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    std::string line;
    std::getline(std::cin, line); // consume the trailing newline after T

    while (T--) {
        std::string s;
        std::getline(std::cin, s);

        // Collect all digits
        std::vector<char> digits;
        digits.reserve(s.size());
        for (char ch : s) {
            if (std::isdigit(static_cast<unsigned char>(ch))) {
                digits.push_back(ch);
            }
        }

        // Rebuild string: replace digit positions from the end of collected digits
        std::string res;
        res.reserve(s.size());
        int di = static_cast<int>(digits.size()) - 1;
        for (char ch : s) {
            if (std::isdigit(static_cast<unsigned char>(ch))) {
                res.push_back(digits[di--]);  // put next reversed digit
            } else {
                res.push_back(ch);            // keep non-digit as is
            }
        }

        std::cout << res << '\n';
    }
    return 0;
}
