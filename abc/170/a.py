# -*- coding:utf-8 -*-

def solve():
    Xs = list(map(int, input().split()))

    for i, x in enumerate(Xs):
        if x == 0:
            print(i+1)
            return

if __name__ == "__main__":
    solve()
