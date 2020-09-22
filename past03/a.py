# -*- coding:utf-8 -*-

def solve():
    S = input()
    T = input()

    if S == T:
        print("same")
        return

    if S.lower() == T.lower():
        print("case-insensitive")
        return

    print("different")


if __name__ == "__main__":
    solve()
