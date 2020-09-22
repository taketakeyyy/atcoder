# -*- coding:utf-8 -*-
import sys

def solve():
    N, K = list(map(int, sys.stdin.readline().split()))
    hs = list(map(int, sys.stdin.readline().split()))

    ans = 0
    for h in hs:
        if h >= K:
            ans += 1

    print(ans)

if __name__ == "__main__":
    solve()
