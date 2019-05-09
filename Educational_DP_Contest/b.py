# -*- coding:utf-8 -*-

def solve():
    """ dp[i+k]を求める方法（配るDP）
    Python: TLE
    PyPy: AC
    (´･_･`)
    """
    N,K = list(map(int,input().split()))
    A = list(map(int,input().split()))
    
    INF = float("inf")
    
    dp = [INF]*N
    dp[0] = 0
    
    for i in range(0, N-1):
        for k in range(1, K+1):
            if i+k <= N-1:
                dp[i+k]=min(dp[i+k], dp[i]+abs(A[i]-A[i+k]))
            else:
                break
    print(dp[N-1])


def solve2():
    """ dp[i]を求める方法（貰うDP）
    Python: TLE
    PyPy: AC
    (´･_･`)
    """
    N,K = list(map(int,input().split()))
    A = list(map(int,input().split()))
    
    INF = float("inf")
    
    dp = [INF]*N
    dp[0] = 0
    for i in range(1, N):
        for k in range(1, K+1):
            if i-k >= 0:
                dp[i] = min(dp[i], dp[i-k]+abs(A[i]-A[i-k]))
            else:
                break
    print(dp[N-1])


if __name__ == "__main__":
    solve()
