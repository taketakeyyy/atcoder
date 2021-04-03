# -*- coding:utf-8 -*-

def solve():
    H, N = list(map(int, input().split()))
    magic = []
    for _ in range(N):
        a, b = list(map(int, input().split()))
        magic.append((a,b))

    # dp[h] := 体力をhにするのに必要な最小魔力
    dp = [float("inf") for _ in range(H+1)]
    dp[H] = 0
    for h in range(H, -1, -1):
        for a, b in magic:
            nh = max(0, h-a)
            dp[nh] = min(dp[nh], dp[h]+b)
    print(dp[0])

if __name__ == "__main__":
    solve()
