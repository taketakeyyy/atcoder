# -*- coding:utf-8 -*-

def solve():
    import math

    a, b, x = list(map(int, input().split()))

    if x > a*a*b/2:
        s = x/a
        # a*b-s = a*h*(1/2)
        h = (a*b-s)*2/a
        theta = math.atan2(h, a)
        ans = math.degrees(theta)
        print(ans)

    else:
        s = x/a
        h = (s*2)/b
        theta = math.atan2(h, b)
        ans = 180-90-math.degrees(theta)
        print(ans)


if __name__ == "__main__":
    solve()
