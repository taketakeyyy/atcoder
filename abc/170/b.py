# -*- coding:utf-8 -*-

def solve():
    X, Y = list(map(int, input().split()))

    for kame in range(0, X+1):
        turu = X - kame

        if kame*4 + turu*2 == Y:
            print("Yes")
            return
    print("No")


if __name__ == "__main__":
    solve()
