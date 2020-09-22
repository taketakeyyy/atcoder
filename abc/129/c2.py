# -*- coding:utf-8 -*-

def solve():
    MOD = 1000000007
    N, M = list(map(int, input().split()))
    dp = [0 for i in range(0, N+1)]
    A = set()
    for i in range(M):
        A.add(int(input()))
    
    dp[0] = 1
    dp[1] = 0 if 1 in A else 1

    for i in range(2, N+1):
        if i in A:
            continue
        dp[i] = (dp[i-1]%MOD + dp[i-2]%MOD)%MOD
    
    print(dp[N])


if __name__ == "__main__":
    solve()
