# -*- coding:utf-8 -*-

def solve():
    S = input()
    MOD = 10**9+7

    N = len(S)

    # dp[i][j] := Sの先頭i文字として考えられるもののうち、13で割ったあまりがjのものの数
    dp = [[0 for _ in range(13)] for __ in range(10**5+1)]
    dp[0][0] = 1  # S[0]において13で割ってあまりが0になるもの(左端が00000は13で割って余りが0)

    for i in range(0, N):
        if S[i] == "?":
            c = -1
        else:
            c = int(S[i])
        
        """ 動画見ろ
        https://youtu.be/brfeRxmzuKw?t=2226
        
        ・DPテーブル間違ってる可能性あり

        1?2?3

         余り | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12
        ------------------------------------------------------------
          0   | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0 
          3   | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0 
         ?3   | 1 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 1 | 0 | 1  | 1  | 0 

        dp[0][0] = 1
        dp[0][1] = 
        """

        for j in range(0, 10):


if __name__ == "__main__":
    solve()