# -*- coding:utf-8 -*-

def solve():
    S, T = input().split()
    A, B = list(map(int, input().split()))
    U = input()

    if S == U:
        A -= 1
    else:
        B -= 1

    print(A, B)


if __name__ == "__main__":
    solve()
