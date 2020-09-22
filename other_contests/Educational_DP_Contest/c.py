# -*- coding:utf-8 -*-
"""
問題
https://atcoder.jp/contests/dp/tasks/dp_c

解説
https://qiita.com/drken/items/dc53c683d6de8aeacf5a#c-%E5%95%8F%E9%A1%8C---vacation
"""
def solve():
    N = int(input())
    A, B, C = [0], [0], [0]
    for i in range(N):
        a, b, c = list(map(int, input().split()))
        A.append(a)
        B.append(b)
        C.append(c)
    
    # dp[i][j] := i日目にjを選んだときの、幸福度の最大値
    # j := 0(A), 1(B), 2(C)
    dp = [[j for j in range(3)] for i in range(N+1)]
    dp[0][0] = 0
    dp[0][1] = 0
    dp[0][2] = 0

    for i in range(1, N+1):
        dp[i][0] = max(dp[i-1][1]+B[i], dp[i-1][2]+C[i])
        dp[i][1] = max(dp[i-1][0]+A[i], dp[i-1][2]+C[i])
        dp[i][2] = max(dp[i-1][0]+A[i], dp[i-1][1]+B[i])
    
    ans = max(dp[N][0], dp[N][1], dp[N][2])
    print(ans)



if __name__ == "__main__":
    solve()
