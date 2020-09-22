# -*- coding:utf-8 -*-

def solve():
    import sys

    txa, tya, txb, tyb, T, V = list(map(int, sys.stdin.readline().split()))
    N = int(sys.stdin.readline())

    for _ in range(N):
        x, y = list(map(int, sys.stdin.readline().split()))

        d1 = ((txa-x)**2+(tya-y)**2)**(1/2)
        d2 = ((txb-x)**2+(tyb-y)**2)**(1/2)
        t = (d1+d2)/V
        if t <= T:
            print("YES")
            return
    print("NO")


if __name__ == "__main__":
    solve()
