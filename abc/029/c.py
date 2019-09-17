# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(1000)

def solve():
    N = int(input())
    s = ("a","b","c")

    def _dfs(depth, s):
        if depth == N:
            return s

        ans1 = _dfs(depth+1, s+"a")
        ans2 = _dfs(depth+1, s+"b")
        ans3 = _dfs(depth+1, s+"c")

        if ans1 is not None:
            print(ans1)
        if ans2 is not None:
            print(ans2)
        if ans3 is not None:
            print(ans3)

    _dfs(0, "")



if __name__ == "__main__":
    solve()
