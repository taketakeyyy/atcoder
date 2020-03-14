# -*- coding:utf-8 -*-
import math

def solve():
    H, W = list(map(int, input().split()))

    if H==1 or W==1:
        print(1)
        return

    odd = math.ceil(H/2)
    even = H//2

    ans = odd*math.ceil(W/2) + even*(W//2)
    print(ans)


if __name__ == "__main__":
    solve()
