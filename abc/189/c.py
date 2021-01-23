# -*- coding:utf-8 -*-

def solve():
    """PyPy3なら通る"""
    N = int(input())
    As = list(map(int, input().split()))

    ans = 0
    for l in range(N):
        mn = As[l]
        ans = max(ans, mn)
        for r in range(l+1, N):
            mn = min(mn, As[r])
            ans = max(ans, mn*(r-l+1))
    print(ans)


if __name__ == "__main__":
    solve()
