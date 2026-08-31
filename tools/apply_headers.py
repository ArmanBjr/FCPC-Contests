#!/usr/bin/env python3
"""Apply standardized FCPC answer headers to all contest solution files."""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPO_URL = "https://github.com/ArmanBjr/FCPC-Contests"
AUTHOR = "Arman Bijari"

CONTEST_META: dict[str, tuple[str, str, str]] = {
    "FirstContest": ("2024", "Season 1", "First Contest"),
    "SecondContest": ("2024", "Season 2", "Second Contest"),
    "ThirdContest": ("2024", "Season 3", "Third Contest"),
    "FourthContest": ("2024", "Season 4", "Fourth Contest"),
    "Finals/FirstContest": ("2024", "Finals Season 1", "Finals — First Contest"),
    "Finals/SecondContest": ("2024", "Finals Season 2", "Finals — Second Contest"),
}

ANSWER_RE = re.compile(r"^[A-J]\.(cpp|py|java|c)$", re.IGNORECASE)
SKIP_NAMES = {
    "compare.cpp",
    "test.cpp",
    "test.py",
    "testduringcontest.cpp",
    "evaluate_i.py",
}

HEADER_PATTERNS = [
    re.compile(r"^\s*//\s*=+\s*$"),
    re.compile(r"^\s*//\s*FCPC\b", re.I),
    re.compile(r"^\s*//\s*Archive solution", re.I),
    re.compile(r"^\s*//\s*Year\s*:", re.I),
    re.compile(r"^\s*//\s*Contest\s*:", re.I),
    re.compile(r"^\s*//\s*Problem\s*:", re.I),
    re.compile(r"^\s*//\s*Author\s*:", re.I),
    re.compile(r"^\s*//\s*Repo\s*:", re.I),
    re.compile(r"^\s*//\s*FCPC\s+S\.", re.I),
    re.compile(r"^\s*//\s*Problem\s+[A-J]\s*$", re.I),
    re.compile(r"^\s*#+\s*$"),
    re.compile(r"^\s*#\s*FCPC\b", re.I),
    re.compile(r"^\s*#\s*Archive solution", re.I),
    re.compile(r"^\s*#\s*Year\s*:", re.I),
    re.compile(r"^\s*#\s*Contest\s*:", re.I),
    re.compile(r"^\s*#\s*Problem\s*:", re.I),
    re.compile(r"^\s*#\s*Author\s*:", re.I),
    re.compile(r"^\s*#\s*Repo\s*:", re.I),
    re.compile(r"^\s*#FCPC\b", re.I),
]


def is_answer_file(path: Path) -> bool:
    if path.suffix.lower() in {".exe", ".zip"}:
        return False
    if path.name.lower() in SKIP_NAMES:
        return False
    if path.name == "H" and path.parent.name == "Answers":
        return False
    return bool(ANSWER_RE.match(path.name))


def strip_old_header(lines: list[str]) -> list[str]:
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.strip() == "":
            i += 1
            continue
        if any(p.match(line) for p in HEADER_PATTERNS):
            i += 1
            continue
        break
    while i < len(lines) and lines[i].strip() == "":
        i += 1
    return lines[i:]


def make_header(ext: str, year: str, contest: str, problem: str) -> str:
    problem_letter = Path(problem).stem.upper()
    if ext == ".py":
        sym = "#"
        bar = "#" * 77
        return (
            f"{bar}\n"
            f"# FCPC — Ferdowsi University Programming Contest\n"
            f"# Archive solution (reference answer)\n"
            f"# Year    : {year}\n"
            f"# Contest : {contest}\n"
            f"# Problem : {problem_letter}\n"
            f"# Author  : {AUTHOR}\n"
            f"# Repo    : {REPO_URL}\n"
            f"{bar}\n"
        )
    return (
        f"// {'=' * 77}\n"
        f"// FCPC — Ferdowsi University Programming Contest\n"
        f"// Archive solution (reference answer)\n"
        f"// Year    : {year}\n"
        f"// Contest : {contest}\n"
        f"// Problem : {problem_letter}\n"
        f"// Author  : {AUTHOR}\n"
        f"// Repo    : {REPO_URL}\n"
        f"// {'=' * 77}\n"
    )


def process_file(path: Path, year: str, contest_label: str, problem: str) -> bool:
    text = path.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines(keepends=True)
    body_lines = strip_old_header(lines)
    header = make_header(path.suffix.lower(), year, contest_label, path.name)
    new_text = header + "\n" + "".join(body_lines)
    if not new_text.endswith("\n"):
        new_text += "\n"
    if new_text == text:
        return False
    path.write_text(new_text, encoding="utf-8", newline="\n")
    return True


def main() -> None:
    changed = 0
    for contest_key, (year, season, label) in CONTEST_META.items():
        answers_dir = ROOT / contest_key / "Answers"
        if not answers_dir.is_dir():
            print(f"skip missing: {answers_dir}")
            continue
        for path in sorted(answers_dir.iterdir()):
            if not path.is_file() or not is_answer_file(path):
                continue
            if process_file(path, year, f"{season} ({label})", path.name):
                changed += 1
                print(f"updated: {path.relative_to(ROOT)}")
    print(f"done — {changed} file(s) updated")


if __name__ == "__main__":
    main()
