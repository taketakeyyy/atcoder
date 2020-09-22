# -*- coding:utf-8 -*-

def solve():
    S = input()
    total = 0
    for s in S:
        total += int(s)

    if total%9 == 0:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
