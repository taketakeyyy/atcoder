# -*- coding:utf-8 -*-

def solve():
    import sys

    S = sys.stdin.readline().rstrip()
    strs = list("abcdefghijklmnopqrstuvwxyz")

    for s in S:
        if s in strs:
            print("error")
            return

    print(int(S)*2)


if __name__ == "__main__":
    solve()
