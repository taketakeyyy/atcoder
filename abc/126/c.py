# -*- coding:utf-8 -*-
import math

def solve():
    N, K = list(map(int, input().split()))

    ans = 0
    for i in range(1, N+1):
        if i >= K:
            ans += (1/N)
            continue
        # a*2^n >= K より
        # n >= log2(K/a)
        n = math.ceil(math.log2(K/i))
        ans += (1/N) * (1/2)**n

    print(ans)


if __name__ == "__main__":
    solve()
