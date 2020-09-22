# -*- coding:utf-8 -*-

def solve():
    A = int(input())
    B = int(input())
    if A > B:
        print("GREATER")
    elif A < B:
        print("LESS")
    else:
        print("EQUAL")


if __name__ == "__main__":
    solve()
