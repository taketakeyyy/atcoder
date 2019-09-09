# -*- coding:utf-8 -*-

def solve():
    A, B, C, D = list(map(int, input().split()))

    if B/A > D/C:
        print("TAKAHASHI")
    elif B/A < D/C:
        print("AOKI")
    else:
        print("DRAW")

if __name__ == "__main__":
    solve()
