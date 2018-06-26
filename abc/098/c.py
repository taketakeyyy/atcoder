# -*- coding:utf-8 -*-

def solve(N, S):
    # TLE
    dp = [[0 for i in range(N+1)] for j in range(N+1)]
    # dp[left][right] := 正しい方向の数
    # まずはdp[0][N]を考える
    for s in S:
        if s == "W":
            dp[0][N] += 1
    maxv = dp[0][N]
    # dpを埋める
    # dp[1][N-1], dp[2][N-2], ...
    for i in range(1, N+1):
        if S[i-1] == "E":
            diff = 1
        else:
            diff = -1
        dp[i][N-i] = dp[i-1][N-i+1] + diff
        if dp[i][N-i] >= maxv:
            maxv = dp[i][N-i]
    print(N - maxv)

def solve2(N, S):
    # AC
    # solveをdpじゃなくしただけ
    good = 0
    for s in S:
        if s == "W":
            good += 1
    maxv = good

    nowv = maxv
    for i in range(1, N+1):
        if S[i-1] == "E":
            diff = 1
        else:
            diff = -1
        nowv = nowv + diff
        if nowv >= maxv:
            maxv = nowv
    print(N - maxv)

if __name__ == "__main__":
    N = int(input())
    S = input()
    solve2(N, S)
