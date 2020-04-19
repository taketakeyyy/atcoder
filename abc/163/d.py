# -*- coding:utf-8 -*-

def solve():
    MOD = 10**9+7
    N, K = list(map(int, input().split()))

    def total(mn, mx):
        """mnからmxまでの和を返す"""
        n = mx-mn+1
        ret = int((mn+mx)*n/2)
        return ret%MOD

    ans = 0
    for k in range(K, N+2):
        ans += total(N-k+1, N) - total(0, k-1) + 1
        ans = ans%MOD

    print(int(ans))


if __name__ == "__main__":
    solve()
