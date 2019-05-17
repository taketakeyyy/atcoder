# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A, B, C = [], [], []
    # dp[i][j] := iからjに行くのにかかる最短コスト
    dp = [[0 for j in range(N)] for i in range(N)]
    for i in range(N):
        a, b, c = list(map(int, input().split()))
        A.append(a-1)
        B.append(b-1)
        C.append(c)
        dp[a-1][b-1] = c
        dp[b-1][a-1] = c
        dp[a-1][a-1] = 0
        dp[b-1][b-1] = 0

    Q, K = list(map(int, input().split()))
    X, Y = [], []
    for j in range(Q):
        x, y = list(map(int, input().split()))
        X.append(x-1)
        Y.append(y-1)



if __name__ == "__main__":
    solve()
