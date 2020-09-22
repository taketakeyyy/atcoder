# -*- coding:utf-8 -*-
import sys


def solve():
    N, A = list(map(int, sys.stdin.readline().split()))
    Xs = list(map(int, sys.stdin.readline().split()))
    # dp[i][j][k] := 左からi枚目までに、j枚を選んで、選んだカードの総和がk  (iは0-origin)
    dp = [[[0]*(N*50+1) for _ in range(0, N+1)] for __ in range(0, N)]
    dp[0][0][0] = 1
    dp[0][1][Xs[0]] = 1

    for i in range(1, N):
        for j in range(0, N):
            for k in range(N*50+1):
                dp[i][j][k] += dp[i-1][j][k]
                if k+Xs[i] < N*50+1:
                    dp[i][j+1][k+Xs[i]] += dp[i-1][j][k]

    ans = 0
    for j in range(1, N+1):
        ans += dp[N-1][j][A*j]

    print(ans)


if __name__ == "__main__":
    solve()
