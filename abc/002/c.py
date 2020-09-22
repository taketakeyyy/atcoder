# -*- coding:utf-8 -*-

def solve():
    import sys

    xa, ya, xb, yb, xc, yc = list(map(int, sys.stdin.readline().split()))
    # ヘロンの公式
    a = ((xa-xb)**2+(ya-yb)**2)**(1/2)
    b = ((xb-xc)**2+(yb-yc)**2)**(1/2)
    c = ((xc-xa)**2+(yc-ya)**2)**(1/2)
    s = (a+b+c)/2
    S = (s*(s-a)*(s-b)*(s-c))**(1/2)
    print(S)


if __name__ == "__main__":
    solve()
