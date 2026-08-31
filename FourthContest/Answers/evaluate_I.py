import os
import subprocess
import sys

# PATHS (edit if needed)
BASE = r"E:\University\FCPC\FourthContest\TestCases\I"
IN_DIR = os.path.join(BASE, "in")
OUT_DIR = os.path.join(BASE, "out")  # not used, but kept for compatibility
SOLUTION_CPP = os.path.join(BASE, "solution.cpp")
SOLUTION_EXE = os.path.join(BASE, "solution.exe")  # after compilation

# ----------------------------------------------------
# Helper functions
# ----------------------------------------------------

def compile_solution():
    print("Compiling solution.cpp ...")
    cmd = ["g++", "-O2", "-std=c++17", SOLUTION_CPP, "-o", SOLUTION_EXE]
    proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if proc.returncode != 0:
        print("Compilation failed:")
        print(proc.stderr.decode())
        sys.exit(1)
    print("Compilation successful.\n")


def read_input(path):
    lines = [line.rstrip("\n") for line in open(path, "r")]
    N = int(lines[0])
    grid = [list(lines[i+1]) for i in range(10)]
    return N, grid


def read_intervals(text, N):
    lines = [line.strip() for line in text.splitlines() if line.strip()]
    if not lines:
        return None, "Output empty"

    try:
        P = int(lines[0])
    except:
        return None, "First line must be integer P"

    if P < 0:
        return None, "P < 0"

    if len(lines) != P + 1:
        return None, f"Expected {P} lines but got {len(lines)-1}"

    intervals = []
    steps = N - 1
    last_end = 0

    for i in range(P):
        parts = lines[i+1].split()
        if len(parts) != 2:
            return None, f"Line {i+2}: expected two integers"
        try:
            t = int(parts[0])
            x = int(parts[1])
        except:
            return None, f"Line {i+2}: invalid integers"

        if x <= 0:
            return None, f"Interval {i+2}: x must be > 0"
        if t < 0:
            return None, f"Interval {i+2}: t < 0"
        if t >= steps:
            return None, f"Interval {i+2}: t >= N-1"
        if t < last_end:
            return None, f"Intervals not sorted or overlapping (line {i+2})"
        if t + x > steps:
            return None, f"Interval {i+2}: t+x > N-1"

        last_end = t + x
        intervals.append((t, x))

    return intervals, None


def simulate(N, grid, intervals):
    steps = N - 1
    on = [False] * steps

    for (t, x) in intervals:
        for k in range(x):
            on[t + k] = True

    r, c = 9, 0
    if grid[r][c] == 'X':
        return False, "Start cell blocked"

    for step in range(steps):
        if on[step]:
            if r > 0:
                r -= 1
        else:
            if r < 9:
                r += 1

        c += 1
        if grid[r][c] == 'X':
            return False, f"Hit obstacle at (row={r}, col={c})"

    return True, "OK"


# ----------------------------------------------------
# MAIN
# ----------------------------------------------------

def main():
    compile_solution()

    tests = sorted(os.listdir(IN_DIR))
    results = []

    for fname in tests:
        if not fname.endswith(".txt"):
            continue

        in_path = os.path.join(IN_DIR, fname)
        print(f"Running {fname} ...")

        # Run solution.exe < input
        proc = subprocess.run(
            [SOLUTION_EXE],
            stdin=open(in_path, "rb"),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )

        output = proc.stdout.decode()

        # Parse input
        N, grid = read_input(in_path)

        # Parse output
        intervals, err = read_intervals(output, N)
        if err:
            print(f" ❌ WA — {err}")
            results.append((fname, False))
            continue

        # Simulate
        ok, msg = simulate(N, grid, intervals)
        if ok:
            print(f" ✅ OK")
            results.append((fname, True))
        else:
            print(f" ❌ WA — {msg}")
            results.append((fname, False))

    print("\nSummary:")
    for fname, ok in results:
        print(f"{fname}: {'OK' if ok else 'WA'}")

    print("\nDone.")


if __name__ == "__main__":
    main()
