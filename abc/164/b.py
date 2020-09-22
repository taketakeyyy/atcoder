# -*- coding:utf-8 -*-

def solve():
    A, B, C, D = list(map(int, input().split()))

    turn = True
    while A>0 and C>0:
        if turn:
            C -= B
        else:
            A -= D
        turn = not turn

    if A > 0:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
