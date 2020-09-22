# -*- coding:utf-8 -*-

def solve():
    S = input()  # 1以上S以下の整数
    n = len(S)   # n:整数Sの桁数
    K = int(input())

    # 桁DP
    # dp[i][j][k] := i桁目まで決めて
    #                j個の非ゼロを使って
    #                k:0なら、そこまでの桁はNと一致
    #                k:1なら、そこまでの桁ですでにN以下であることが確定
    #                したときの場合の数
    dp = [[[0 for _ in range(2)] for __ in range(4)] for ___ in range(n+1)]
    dp[0][0][0] = 1  # 何も決めていない状態で、非ゼロを0個使ってるときは1（空集合）

    for i in range(n):
        for j in range(4):
            for k in range(2):
                d = int(S[i]) # 今の桁の値
                for nd in range(10):
                    # 次の桁の値ndを全部試す
                    ni = i + 1
                    nj = j
                    nk = k

                    if nd != 0:
                        # 非ゼロを使ったので
                        nj += 1
                    if nj > K:
                        # 範囲を超えるなら
                        continue
                    if k == 0:
                        # 今の状態がNと一致しているなら
                        if nd > d:
                            # 次の桁が、今の桁の値より大きかったらダメ
                            continue
                        elif nd < d:
                            # 次の桁が、今の桁より小さかったら、「N以下」になることが確定する
                            nk = 1

                    dp[ni][nj][nk] += dp[i][j][k]

    ans = dp[n][K][0] + dp[n][K][1]
    print(ans)


if __name__ == "__main__":
    solve()
