# -*- coding:utf-8 -*-

def solve():
    A, B, C, K = list(map(int, input().split()))
    S, T = list(map(int, input().split()))

    if (S+T) >= K:
        print(S*(A-C) + T*(B-C))
    else:
        print(S*A + T*B)

if __name__ == "__main__":
    solve()
