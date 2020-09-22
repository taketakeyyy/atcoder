# -*- coding:utf-8 -*-

def solve():
    N, Q = list(map(int, input().split()))
    S = input()

    dp = [0]*(N)
    dp[0] = 0
    for i in range(0, N-1):
        if S[i]=="A" and S[i+1]=="C":
            dp[i+1] = dp[i] + 1
        else:
            dp[i+1] = dp[i]
    
    for i in range(Q):
        l, r = list(map(int, input().split()))
        print(dp[r-1] - dp[l-1])
    


if __name__ == "__main__":
    solve()
