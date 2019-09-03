# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    Vs = list(map(int, input().split()))

    """方針
    Dequeueから宝石をとる。最後に好きなだけ宝石を戻す。
    dp[i][j] := 左からi個、右からj個取ったときの最大値
    """
    dp = [[0 for _ in range(K+1)] for __ in range(K+1)]
    dp[0][0] = 0  # dpを使ってなくて草

    ans = -float("inf")
    for i in range(0, K+1):
        for j in range(0, K+1):
            if i+j > K: break
            if i+j > N: break
            if i==0 and j==0:
                ans = 0
                continue

            hasVs = Vs[0:i] + Vs[N-j:N]
            hasVs.sort(reverse=True)

            restK = K - (i+j)
            while restK > 0:
                restK -= 1
                if hasVs == []:
                    break
                if hasVs[-1] < 0:
                    hasVs.pop(-1)
                    continue
                break

            ans = max(ans, sum(hasVs))

    print(ans)



if __name__ == "__main__":
    solve()
