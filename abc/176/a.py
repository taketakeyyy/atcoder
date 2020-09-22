# -*- coding:utf-8 -*-

def solve():
    import math

    N, X, T = list(map(int, input().split()))
    ans = math.ceil(N/X)*T
    print(ans)


if __name__ == "__main__":
    solve()
