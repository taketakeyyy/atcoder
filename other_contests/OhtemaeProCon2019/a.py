# -*- coding:utf-8 -*-

def solve():
    A, B = map(int, input().split())
    if A+0.5 < B:
        print(0)
    else:
        print(1)


if __name__ == "__main__":
    solve()
