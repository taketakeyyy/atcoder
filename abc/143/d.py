# -*- coding:utf-8 -*-
import bisect

def solve():
    N = int(input())
    Ls = list(map(int, input().split()))
    Ls.sort()

    # O(N^2 * logN)の全探索で解く
    ans = 0
    for a in range(N):
        for b in range(a+1, N):
            total = Ls[a]+Ls[b]

            bisect.bisect_left

    print(ans)

if __name__ == "__main__":
    solve()
