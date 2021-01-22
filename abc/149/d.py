# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    R, S, P = list(map(int, input().split()))
    T = input()

    # dp[i] := i回目のじゃんけんの得点
    # ops[i] := i回目のじゃんけんで高橋が出した手
    dp = [0 for _ in range(N)]
    ops = ["" for _ in range(N)]
    for i in range(0, N):
        t = T[i]
        if t == "r":
            if i-K>=0 and ops[i-K]=="p":
                dp[i] = dp[i-1]
                ops[i] = "*"  # "r" or "s"好きな方でいいので、なんでも良い
            else:
                dp[i] = dp[i-1] + P
                ops[i] = "p"
        elif t == "s":
            if i-K>=0 and  ops[i-K]=="r":
                dp[i] = dp[i-1]
                ops[i] = "*"
            else:
                dp[i] = dp[i-1] + R
                ops[i] = "r"
        elif t == "p":
            if i-K>=0 and  ops[i-K]=="s":
                dp[i] = dp[i-1]
                ops[i] = "*"
            else:
                dp[i] = dp[i-1] + S
                ops[i] = "s"

    print(dp[N-1])


if __name__ == "__main__":
    solve()
