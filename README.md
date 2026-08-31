# FCPC-Contests

Archive of **official solutions** for the **FCPC** (Ferdowsi University Programming Contest) — a competitive programming contest series at Ferdowsi University of Mashhad.

This repository is a **solution bank** (مخزن): reference implementations for contest problems, organized by season and round.

## Repository layout

```
FirstContest/Answers/       → 2024 Season 1
SecondContest/Answers/      → 2024 Season 2
ThirdContest/Answers/       → 2024 Season 3
FourthContest/Answers/      → 2024 Season 4
Finals/FirstContest/Answers/  → 2024 Finals — Round 1
Finals/SecondContest/Answers/ → 2024 Finals — Round 2
```

Each answer file is named by problem letter (`A.cpp`, `B.cpp`, …, `I.cpp`, or `E.py` where Python was used).

## File header convention

Every solution starts with a standard header block:

```cpp
// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 1 (First Contest)
// Problem : A
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================
```

## Build & run (C++)

Solutions use competitive-programming style and typically require a C++17 compiler with `bits/stdc++.h` (GCC/MinGW):

```bash
g++ -std=c++17 -O2 A.cpp -o A
./A < input.txt
```

Python solutions run directly:

```bash
python E.py < input.txt
```

## Related

- Older layout (`S.1-2024/`, `S.2-2024/`) was merged into the season folders above.
- Local admin materials (registration, reports, expenses) are kept outside this repo.

## Author

**Arman Bijari** — [GitHub](https://github.com/ArmanBjr)

## License

Solutions are provided for educational reference. Contest problem statements remain property of FCPC / FUM.
