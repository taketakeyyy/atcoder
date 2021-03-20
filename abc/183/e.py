# -*- coding:utf-8 -*-

def solve():
    MOD = 10**9+7
    H, W = list(map(int, input().split()))
    S = []
    for _ in range(H):
        S.append(input())

    # dp[h][w] := h行w列の行き方
    dp = [[0 for _ in range(W)] for __ in range(H)]
    dp[0][0] = 1
    X = [[0 for _ in range(W+1)] for __ in range(H+1)]  # X軸方向の累積和
    Y = [[0 for _ in range(W+1)] for __ in range(H+1)]  # Y軸方向の累積和
    Z = [[0 for _ in range(W+1)] for __ in range(H+1)]  # ナナメ軸方向の累積和

    # もらうDPで考えると累積和が使える
    for h in range(H):
        for w in range(W):
            if S[h][w]=="#":
                X[h+1][w+1] = Y[h+1][w+1] = Z[h+1][w+1] = 0
            else:
                dp[h][w] += X[h+1][w]
                dp[h][w] %= MOD
                dp[h][w] += Y[h][w+1]
                dp[h][w] %= MOD
                dp[h][w] += Z[h][w]
                dp[h][w] %= MOD

                X[h+1][w+1] = X[h+1][w] + dp[h][w]
                Y[h+1][w+1] = Y[h][w+1] + dp[h][w]
                Z[h+1][w+1] = Z[h][w] + dp[h][w]

    print(dp[H-1][W-1])


if __name__ == "__main__":
    solve()
