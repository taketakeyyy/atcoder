# -*- coding:utf-8 -*-

def solve():
    N = int(input())

    turn = 0
    while N:
        if turn%2 == 0:
            N //= 2
        else:
            N = (N-1) // 2
        turn += 1

    if turn%2 == 0:
        print("Takahashi")
    else:
        print("Aoki")


if __name__ == "__main__":
    solve()
