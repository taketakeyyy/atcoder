# -*- coding:utf-8 -*-
import sys


def solve():
    N, X = list(map(int, sys.stdin.readline().split()))

    As = [1]  # レベルiバーガーの厚さ（層の総数）（必ず奇数）
    Ps = [1]  # レベルiバーガーのパティの総数

    for i in range(N):
        As.append(As[i]*2 + 3)  # レベルが1上がると、総数は2倍+3になる
        Ps.append(Ps[i]*2 + 1)  # レベルが1上がると、パティの数は2倍+1になる

    # dp[i][x] := レベルiバーガーの下からx層に含まれているパティの総数
    dp = [[0]*(X+1) for _ in range(2)]
    dp[0][0] = 0
    for i in range(1, X+1):
        dp[0][i] = 1

    # 漸化式を解く
    for i in range(1, 2):
        median = (As[i]+1)//2
        for x in range(X+1):
            if x < median:
                dp[i&1][x] = dp[i-1][x-1]
            elif x == median:
                dp[i][x] = Ps[i-1] + 1
            else:
                dp[i][x] = Ps[i-1] + 1 + dp[i-1][x-median]

    print(dp[N][X])



if __name__ == "__main__":
    solve()