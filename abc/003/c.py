# -*- coding:utf-8 -*-

def solve():
    import sys

    N, K = list(map(int, sys.stdin.readline().split()))
    Rs = list(map(int, sys.stdin.readline().split()))
    Rs.sort()

    ans = 0
    for i in range(N-K, N):
        ans = (ans+Rs[i])/2
    print(ans)


if __name__ == "__main__":
    solve()
