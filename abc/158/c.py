# -*- coding:utf-8 -*-
import math

def solve():
    A, B = list(map(int, input().split()))
    x1 = A*(100/8)
    x2 = B*(10)
    x = min(x1, x2)

    while True:
        a = math.floor(x*0.08)
        b = math.floor(x*0.1)
        if a>A and b>B:
            print(-1)
            return

        if A==a and B==b:
            break
        # print(a, b, x)
        # input()
        x += 1
    print(int(x))

if __name__ == "__main__":
    solve()
