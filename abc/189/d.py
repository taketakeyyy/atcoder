# -*- coding:utf-8 -*-

def f(n):
    """n個のxのうち、少なくとも1つFalseの場合の数
    = 全体 - すべてTrueの場合の数
    """
    return pow(2,n) - 1


def solve():
    N = int(input())
    # dp[i][j] := Y[i]の論理値がjになる場合の数
    dp = [[0 for _ in range(2)] for __ in range(N+1)]
    dp[0][0] = 1
    dp[0][1] = 1
    for i in range(1, N+1):
        s = input()
        if s == "AND":
            dp[i][0] += dp[i-1][0] * 2  # X[i]はTrue,Falseどちらでもよい
            dp[i][0] += dp[i-1][1]      # X[i]はFalse
            dp[i][1] += dp[i-1][1]      # X[i]はTrue
        elif s == "OR":
            dp[i][0] += dp[i-1][0]      # X[i]はFalse
            dp[i][1] += dp[i-1][1] * 2  # X[i]はTrue,Falseどちらでもよい
            dp[i][1] += dp[i-1][0]      # X[i]はTrue
    print(dp[N][1])


if __name__ == "__main__":
    solve()
