# -*- coding:utf-8 -*-

def solve():
    S = input()
    ans = 0
    if "RRR" in S:
        print(3)
    elif "RR" in S:
        print(2)
    elif "R" in S:
        print(1)
    else:
        print(0)


if __name__ == "__main__":
    solve()
