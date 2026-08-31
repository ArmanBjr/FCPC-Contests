#############################################################################
# FCPC — Ferdowsi University Programming Contest
# Archive solution (reference answer)
# Year    : 2024
# Contest : Season 4 (Fourth Contest)
# Problem : I
# Author  : Arman Bijari
# Repo    : https://github.com/ArmanBjr/FCPC-Contests
#############################################################################

def solve():
    N = int(input().strip())
    grid = [list(input().strip()) for _ in range(10)]

    R = 10

    # reachable[r][c] = can we reach cell (r,c)?
    reachable = [[False]*N for _ in range(R)]
    pre_row   = [[-1]*N for _ in range(R)]
    pre_mode  = [[-1]*N for _ in range(R)]  # 0 = OFF, 1 = ON

    # start at (row=9, col=0)
    if grid[9][0] != '.':
        print(0)
        return

    reachable[9][0] = True

    # DP over columns
    for c in range(N-1):
        for r in range(R):
            if not reachable[r][c]:
                continue

            nc = c + 1

            # engine OFF → down-right (or stay at floor)
            nr = r + 1 if r < 9 else 9
            if grid[nr][nc] == '.' and not reachable[nr][nc]:
                reachable[nr][nc] = True
                pre_row[nr][nc] = r
                pre_mode[nr][nc] = 0

            # engine ON → up-right (or stay at ceiling)
            nr = r - 1 if r > 0 else 0
            if grid[nr][nc] == '.' and not reachable[nr][nc]:
                reachable[nr][nc] = True
                pre_row[nr][nc] = r
                pre_mode[nr][nc] = 1

    # find any reachable cell in last column
    end_r = -1
    for r in range(R):
        if reachable[r][N-1]:
            end_r = r
            break

    if end_r == -1:
        print(0)
        return

    # backtrack path
    steps = N - 1
    mode = [0]*steps  # step i: OFF (0) or ON (1)
    r = end_r
    c = N - 1

    while c > 0:
        m = pre_mode[r][c]
        pr = pre_row[r][c]
        mode[c-1] = m
        r = pr
        c -= 1

    # compress ON intervals
    intervals = []
    i = 0
    while i < steps:
        if mode[i] == 1:
            start = i
            while i < steps and mode[i] == 1:
                i += 1
            intervals.append((start, i - start))
        else:
            i += 1

    print(len(intervals))
    for t, length in intervals:
        print(t, length)

solve()
