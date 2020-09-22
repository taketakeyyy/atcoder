# -*- coding:utf-8 -*-
import math

def solve():
    A, B = list(map(int, input().split()))
    if B == 1:
        print(0)
    else:
        total = 1
        ans = 0
        while True:
            ans += 1
            total += (A-1)
            if total >= B:
                break
        print(ans)


if __name__ == "__main__":
    solve()
