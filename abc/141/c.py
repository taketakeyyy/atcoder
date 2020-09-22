# -*- coding:utf-8 -*-
import sys

def solve():
    N, K, Q = list(map(int, sys.stdin.readline().split()))
    ans = [0] * N
    for i in range(Q):
        a = int(sys.stdin.readline())
        ans[a-1] += 1

    for i in range(N):
        if K - (Q-ans[i]) > 0:
            print("Yes")
        else:
            print("No")


if __name__ == "__main__":
    solve()
