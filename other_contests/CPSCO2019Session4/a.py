# -*- coding:utf-8 -*-

def solve():
    L, X = map(int, input().split())
    amari = X%L

    if (X//L)%2 == 0:
        print(amari)
    else:
        print(L-amari)


if __name__ == "__main__":
    solve()
