# -*- coding:utf-8 -*-

def solve():
    import sys
    N = int(sys.stdin.readline())

    set_ = set()
    for _ in range(N):
        S = sys.stdin.readline().rstrip()
        set_.add(S)

    print(len(set_))


if __name__ == "__main__":
    solve()
