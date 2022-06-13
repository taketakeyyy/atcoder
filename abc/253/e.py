# -*- coding:utf-8 -*-

MOD = 998244353

def solve():
    N, M, K = list(map(int, input().split()))

    # コーナーケース
    if K == 0:
        ans = pow(M, N, MOD)
        print(ans)
        return

    # dp[i][j] := iまで見たときの、A[i]がjのときの、条件を満たすものの場合の数
    dp = [[0 for _ in range(M+1)] for __ in range(N)]
    for j in range(M+1):
        for k in range(K, M+1):
            if j+k <= M:
                dp[1][j] += 1
            if j-k >= 1:
                dp[1][j] += 1

    for i in range(2, N):
        # 累積和
        ruiseki = [0 for _ in range(M+1)]
        for j in range(1, M+1):
            ruiseki[j] += dp[i-1][j] + ruiseki[j-1]

        for j in range(1, M+1):
            # ここを一気に足したい
            # for k in range(K, M+1):
            #     if j-k >= 1:
            #         dp[i][j] += dp[i-1][j-k]
            #     if j+k <= M:
            #         dp[i][j] += dp[i-1][j+k]
            if j+K-1 <= M:
                dp[i][j] += ruiseki[M] - ruiseki[j+K-1]
                dp[i][j] %= MOD
            if j-K >= 1:
                dp[i][j] += ruiseki[j-K]
                dp[i][j] %= MOD

    # 出力
    ans = 0
    for j in range(1, M+1):
        ans += dp[N-1][j]
        ans %= MOD
    print(ans)

if __name__ == "__main__":
    solve()
