# -*- coding:utf-8 -*-
import itertools


def solve():
    N = int(input())

    if N==1:
        print("a")
        return

    anss = []

    def _dfs(d, _max, ans):
        if d==N:
            anss.append(ans)
            return

        for i in range(ord("a"), _max+2):
            _dfs(d+1, max(_max, i), ans+chr(i))

    _dfs(1, ord("a"), "a")

    anss.sort()

    for ans in anss:
        print(ans)


if __name__ == "__main__":
    solve()
