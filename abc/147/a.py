# -*- coding:utf-8 -*-

def solve():
    A1, A2, A3 = map(int, input().split())
    if A1+A2+A3 >= 22:
        print("bust")
    else:
        print("win")

if __name__ == "__main__":
    solve()
