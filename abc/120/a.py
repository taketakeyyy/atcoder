# -*- coding:utf-8 -*-

def solve():
    A, B ,C = list(map(int, input().split()))

    if A*C <= B:
        print(C)
    else:
        print(B//A)

if __name__ == "__main__":
    solve()
