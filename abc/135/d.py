# -*- coding:utf-8 -*-
"""解説
dp

dp[i][j] := Sの先頭i文字として考えられるもののうち、13で割ったあまりがjであるものの数

1?2?3 を分解すると、
10000 ≡ 3
 A000 ≡ A*(10**3) % MOD ≡ A*12
  200 ≡ 5
   B0 ≡ B*(10**1) % MOD
    3 ≡ 3
    -----
        11 + ? ≡ 11 + A*12 + B*10

"""


def solve():
    """ PyPyでAC """
    S = input()
    MOD = 10**9+7

    N = len(S)
    dp = [[0 for i in range(13)] for j in range(10**5+1)]
    dp[0][0] = 1

    for i in range(0, N):
        if S[i] == "?":
            c = -1
        else:
            c = int(S[i])
        
        for j in range(0, 10):
            if c != -1 and c != j: continue
            
            for ki in range(0, 13):
                dp[i+1][(ki* 10 + j)%13] += dp[i][ki]
        
        for j in range(0, 13):
            dp[i+1][j] %= MOD

    res = dp[N][5]
    print(res)


if __name__ == "__main__":
    solve()
