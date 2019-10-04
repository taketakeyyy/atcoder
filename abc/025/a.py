# -*- coding:utf-8 -*-

def solve():
    S = input()
    N = int(input())

    T = S
    cands = []
    for s in S:
        for t in T:
            cands.append(s+t)
    cands.sort()

    print(cands[N-1])


if __name__ == "__main__":
    solve()
